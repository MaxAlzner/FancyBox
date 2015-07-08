#ifndef FBOX_SCRIPTFILE_H
#define FBOX_SCRIPTFILE_H
	
namespace fbox
{

	class FBOXAPI ScriptFile : public ScriptEntity
	{
	public:

		inline ScriptFile() : ScriptEntity(), _script(0) {}
		inline ScriptFile(ScriptManager* manager) : ScriptEntity(manager), _script(0) {}
		inline ~ScriptFile() {}

		virtual void release();

		virtual void read(String filepath);
		virtual void read(const char* blob, unsigned int bytes);

		virtual void run();

	protected:

		v8::Handle<v8::Script>* _script;

	};

}

#endif