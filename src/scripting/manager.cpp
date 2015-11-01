
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace js
	{

		v8::Isolate* Manager::Isolate = 0;
		v8::Persistent<v8::Context> Manager::Context;

		static void FatalErrorCallback(const char* location, const char* message)
		{
			printf(" ERROR: %s %s\n", location, message);
		}

		static void CallbackInfoPrint(const v8::Arguments& args)
		{
			int length = args.Length();
			for (int i = 0; i < length; i++)
			{
				if (i > 0)
				{
					printf(", ");
				}

				printf("%s", *v8::String::Utf8Value(args[i]));
			}

			printf("\n");
		}

		static v8::Handle<v8::Value> DebugLogCallback(const v8::Arguments& args)
		{
			printf("LOG: ");
			CallbackInfoPrint(args);
			return v8::Undefined();
			
		}
		static v8::Handle<v8::Value> DebugWarningCallback(const v8::Arguments& args)
		{
			printf("WARNING: ");
			CallbackInfoPrint(args);
			return v8::Undefined();
		}
		static v8::Handle<v8::Value> DebugErrorCallback(const v8::Arguments& args)
		{
			printf("ERROR: ");
			CallbackInfoPrint(args);
			return v8::Undefined();
		}

		FBOXAPI void Manager::Initialize()
		{
			//v8::V8::InitializeICU();
			v8::V8::Initialize();
			v8::V8::SetFatalErrorHandler(FatalErrorCallback);
			Isolate = v8::Isolate::New();

			static v8::Isolate::Scope IsolateScope(Isolate);
			static v8::HandleScope ScopeHandle;

			Context = v8::Context::New();

			static v8::Context::Scope ContextScope(Context);

			v8::Local<v8::Object> debug = v8::Object::New();
			debug->Set(v8::String::New("Log"), v8::FunctionTemplate::New(DebugLogCallback)->GetFunction());
			debug->Set(v8::String::New("Warning"), v8::FunctionTemplate::New(DebugWarningCallback)->GetFunction());
			debug->Set(v8::String::New("Error"), v8::FunctionTemplate::New(DebugErrorCallback)->GetFunction());
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