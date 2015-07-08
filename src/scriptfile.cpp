
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void ScriptFile::release()
	{
		if (this->_script != 0)
		{
			this->_script->Clear();
			delete this->_script;
			this->_script = 0;
		}

		this->_manager = 0;
	}

	FBOXAPI void ScriptFile::read(String filepath)
	{
		File* file = new File;
		file->read(filepath);
		if (this->_manager != 0 && !this->_manager->isEmpty() && !file->isEmpty())
		{
			v8::Local<v8::String> source = v8::String::NewFromUtf8(this->_manager->isolate, (const char*)file);
			if (!source.IsEmpty())
			{
				this->_script = new v8::Handle < v8::Script > ;
				*this->_script = v8::Script::Compile(source);
			}
		}

		file->release();
		delete file;
	}
	FBOXAPI void ScriptFile::read(const char* blob, unsigned int bytes)
	{
		if (this->_manager != 0 && !this->_manager->isEmpty() && blob != 0 && bytes > 0)
		{
			v8::Local<v8::String> source = v8::String::NewFromUtf8(this->_manager->isolate, blob);
			if (!source.IsEmpty())
			{
				this->_script = new v8::Handle < v8::Script > ;
				*this->_script = v8::Script::Compile(source);
			}
		}
	}

	FBOXAPI void ScriptFile::run()
	{
		if (this->_script != 0 && !this->_script->IsEmpty())
		{
			(*this->_script)->Run();
		}
	}

}