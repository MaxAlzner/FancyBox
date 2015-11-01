
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace js
	{

		v8::Isolate* Manager::Isolate = 0;
		v8::Local<v8::Context> Manager::Context;

		static void FatalErrorCallback(const char* location, const char* message)
		{
			printf(" ERROR: %s %s\n", location, message);
		}

		static void CallbackInfoPrint(const v8::FunctionCallbackInfo<v8::Value>& info)
		{
			int length = info.Length();
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

		static void DebugLogCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
		{
			printf("LOG: ");
			CallbackInfoPrint(info);
			
		}
		static void DebugWarningCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
		{
			printf("WARNING: ");
			CallbackInfoPrint(info);
		}
		static void DebugErrorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
		{
			printf("ERROR: ");
			CallbackInfoPrint(info);
		}

		FBOXAPI void Manager::Initialize()
		{
			v8::V8::InitializeICU();
			v8::V8::Initialize();
			v8::V8::SetFatalErrorHandler(FatalErrorCallback);
			Isolate = v8::Isolate::New();

			static v8::Isolate::Scope IsolateScope(Isolate);
			static v8::HandleScope ScopeHandle(Isolate);

			Context = v8::Context::New(Isolate);

			static v8::Context::Scope ContextScope(Context);

			v8::Local<v8::Object> debug = v8::Object::New();
			debug->Set(v8::String::New("Log"), v8::FunctionTemplate::New(Isolate, DebugLogCallback)->GetFunction());
			debug->Set(v8::String::New("Warning"), v8::FunctionTemplate::New(Isolate, DebugWarningCallback)->GetFunction());
			debug->Set(v8::String::New("Error"), v8::FunctionTemplate::New(Isolate, DebugErrorCallback)->GetFunction());
			Context->Global()->Set(v8::String::New("Debug"), debug);
		}
		FBOXAPI void Manager::Dispose()
		{
			v8::V8::TerminateExecution(Isolate);
			if (Isolate != 0)
			{
				Isolate->Dispose();
				Isolate = 0;
			}

			v8::V8::Dispose();
		}

		FBOXAPI Object Manager::Global()
		{
			if (!Context.IsEmpty())
			{
				return Object(Context->Global());
			}

			return Object();
		}

		FBOXAPI void Manager::Register(const std::string& filename)
		{
			if (Started())
			{
				char* raw = 0;
				if (Import::Read(filename, &raw) > 0)
				{
					v8::Local<v8::String> source = v8::String::New(raw);
					if (!source.IsEmpty())
					{
						v8::Handle<v8::Script> script = v8::Script::Compile(source);
						script->Run();
					}
				}

				delete[] raw;

			}
		}
		FBOXAPI void Manager::Execute(const std::string& command)
		{
			v8::Local<v8::String> source = v8::String::New(command.data());
			if (!source.IsEmpty())
			{
				v8::Local<v8::Script> script = v8::Script::Compile(source);
				if (!script.IsEmpty())
				{
					script->Run();
				}
			}
		}

		FBOXAPI bool Manager::Started()
		{
			return Isolate != 0;
		}

	}
}