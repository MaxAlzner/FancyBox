
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	v8::Isolate* ScriptManager::Isolate = 0;
	v8::Local<v8::Context> ScriptManager::Context;
	List<ScriptFile*> ScriptManager::Files;

	static void FatalErrorCallback(const char* location, const char* message)
	{
		printf(" ERROR: %s %s\n", location, message);
	}

	static void DebugLogCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
	{
		int length = info.Length();
		printf("LOG: ");
		for (int i = 0; i < length; i++)
		{
			if (i > 0)
			{
				printf(", ");
			}

			printf("%s", *v8::String::Utf8Value(info[i]));
		}

		printf("\n");
	}

	FBOXAPI void ScriptManager::Initialize()
	{
		v8::V8::InitializeICU();
		v8::V8::Initialize();
		v8::V8::SetFatalErrorHandler(FatalErrorCallback);
		Isolate = v8::Isolate::New();

		static v8::Isolate::Scope IsolateScope(Isolate);
		static v8::HandleScope ScopeHandle(Isolate);

		Context = v8::Context::New(Isolate);

		static v8::Context::Scope ContextScope(Context);

		v8::Local<v8::Object> debug = v8::Object::New(Isolate);
		debug->Set(v8::String::NewFromUtf8(Isolate, "Log"), v8::FunctionTemplate::New(Isolate, DebugLogCallback)->GetFunction());
		debug->Set(v8::String::NewFromUtf8(Isolate, "Warning"), v8::FunctionTemplate::New(Isolate, DebugLogCallback)->GetFunction());
		debug->Set(v8::String::NewFromUtf8(Isolate, "Error"), v8::FunctionTemplate::New(Isolate, DebugLogCallback)->GetFunction());
		Context->Global()->Set(v8::String::NewFromUtf8(Isolate, "Debug"), debug);
	}
	FBOXAPI void ScriptManager::Dispose()
	{
		for (List<ScriptFile*>::Iterator i = Files.iterator(); i.inside(); i.next())
		{
			ScriptFile* script = i.current();
			if (script != 0)
			{
				script->dispose();
				delete script;
			}
		}
		
		v8::V8::TerminateExecution(Isolate);
		if (Isolate != 0)
		{
			Isolate->Dispose();
			Isolate = 0;
		}

		v8::V8::Dispose();
	}

	FBOXAPI ScriptObject ScriptManager::Global()
	{
		if (!Context.IsEmpty())
		{
			return ScriptObject(Context->Global());
		}

		return ScriptObject();
	}

	FBOXAPI ScriptFile* ScriptManager::Register(String filepath)
	{
		ScriptFile* file = new ScriptFile;
		file->read(filepath);
		file->run();
		return file;
	}
	FBOXAPI void ScriptManager::Execute(String command)
	{
		v8::Local<v8::String> source = v8::String::NewFromUtf8(Isolate, command);
		if (!source.IsEmpty())
		{
			v8::Local<v8::Script> script = v8::Script::Compile(source);
			if (!script.IsEmpty())
			{
				script->Run();
			}
		}
	}

	FBOXAPI bool ScriptManager::Started()
	{
		return Isolate != 0;
	}

}