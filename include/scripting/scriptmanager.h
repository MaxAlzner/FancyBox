#ifndef FBOX_SCRIPTMANAGER_H
#define FBOX_SCRIPTMANAGER_H
	
namespace fbox
{

	class FBOXAPI ScriptManager
	{
	public:

		inline ScriptManager() : isolate(0), context(0), _scope(0) {}
		inline ~ScriptManager() {}

		void build();
		void release();

		ScriptObject global();

		void execute(String command);

		bool isEmpty() const;

		String lastError() const;

		v8::Isolate* isolate;
		v8::Local<v8::Context>* context;

	protected:

		v8::Context::Scope* _scope;

	};

}

#endif