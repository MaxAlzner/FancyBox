
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void ScriptManager::build()
	{
		this->isolate = v8::Isolate::New();

		static v8::Isolate::Scope IsolateScope(this->isolate);
		static v8::HandleScope ScopeHandle(this->isolate);

		this->context = new v8::Local < v8::Context > ;
		*this->context = v8::Context::New(this->isolate);

		static v8::Context::Scope ContextScope(*this->context);
	}
	FBOXAPI void ScriptManager::release()
	{
		for (List<ScriptFile*>::Iterator i = this->_files.iterator(); i.inside(); i.next())
		{
			ScriptFile* script = i.current();
			if (script != 0)
			{
				script->release();
				delete script;
			}
		}

		//if (this->_scope != 0)
		//{
		//	delete this->_scope;
		//	this->_scope = 0;
		//}

		if (this->context != 0)
		{
			this->context->Clear();
			delete this->context;
			this->context = 0;
		}

		if (this->isolate != 0)
		{
			v8::V8::TerminateExecution(this->isolate);
			this->isolate->Dispose();
			this->isolate = 0;
		}
	}

	FBOXAPI ScriptObject ScriptManager::global()
	{
		if (this->context != 0 && !this->context->IsEmpty())
		{
			return ScriptObject(this, (*this->context)->Global());
		}

		return ScriptObject();
	}

	FBOXAPI void ScriptManager::execute(String command)
	{
		v8::Local<v8::String> source = v8::String::NewFromUtf8(this->isolate, command);
		if (!source.IsEmpty())
		{
			v8::Local<v8::Script> script = v8::Script::Compile(source);
			if (!script.IsEmpty())
			{
				script->Run();
			}
		}
	}

	FBOXAPI bool ScriptManager::isEmpty() const
	{
		return this->isolate == 0 || this->context == 0 || this->context->IsEmpty();
	}

	FBOXAPI String ScriptManager::lastError() const
	{
		v8::Local<v8::StackTrace> trace = v8::StackTrace::CurrentStackTrace(10, v8::StackTrace::StackTraceOptions::kOverview);
		if (!trace.IsEmpty())
		{
			int count = trace->GetFrameCount();
			for (int i = 0; i < count; i++)
			{
				v8::Local<v8::StackFrame> frame = trace->GetFrame(i);
				if (!frame.IsEmpty())
				{
					v8::String::Utf8Value funcName(frame->GetFunctionName());
					v8::String::Utf8Value scriptName(frame->GetScriptName());
				}
			}
		}

		return String::Empty();
	}

}