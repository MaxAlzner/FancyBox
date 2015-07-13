#ifndef FBOX_SCRIPTMANAGER_H
#define FBOX_SCRIPTMANAGER_H
	
namespace fbox
{

	class FBOXAPI ScriptManager
	{
	public:

		inline ScriptManager() : isolate(0) {}
		inline ~ScriptManager() {}

		friend class ScriptFile;

		void build();
		void release();

		ScriptObject global();

		void execute(String command);

		bool isEmpty() const;

		String lastError() const;

		v8::Isolate* isolate;
		v8::Local<v8::Context>* context;

	protected:

		List<ScriptFile*> _files;

	};

}

#endif