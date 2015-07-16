#ifndef FBOX_SCRIPTMANAGER_H
#define FBOX_SCRIPTMANAGER_H
	
namespace fbox
{

	class FBOXAPI ScriptManager
	{
	public:

		friend class ScriptFile;

		static void Initialize();
		static void Dispose();

		static ScriptObject Global();

		static void Run();
		static ScriptFile* Register(String filepath);
		static void Execute(String command);

		static bool Started();

		static v8::Isolate* Isolate;

	protected:

		static v8::Local<v8::Context> Context;
		static List<ScriptFile*> Files;

	};

}

#endif