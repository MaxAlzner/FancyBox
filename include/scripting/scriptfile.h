#ifndef FBOX_SCRIPTFILE_H
#define FBOX_SCRIPTFILE_H
	
namespace fbox
{

	class FBOXAPI ScriptFile
	{
	public:

		inline ScriptFile() : _script(0) { ScriptManager::Files.add(this); }
		inline ~ScriptFile() {}

		virtual void dispose();

		virtual void read(String filepath);
		virtual void read(const char* blob, unsigned int bytes);

		virtual void run();

	protected:

		v8::Handle<v8::Script>* _script;

	};

}

#endif