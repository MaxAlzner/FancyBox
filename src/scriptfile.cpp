
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void ScriptFile::dispose()
	{
		if (this->_script != 0)
		{
			this->_script->Clear();
			delete this->_script;
			this->_script = 0;
		}
	}

	FBOXAPI void ScriptFile::read(String filepath)
	{
		File* file = new File;
		file->read(filepath);
		if (ScriptManager::Started() && !file->isEmpty())
		{
			v8::Local<v8::String> source = v8::String::NewFromUtf8(ScriptManager::Isolate, file->raw());
			if (!source.IsEmpty())
			{
				this->_script = new v8::Handle<v8::Script>;
				*this->_script = v8::Script::Compile(source);
			}
		}

		file->release();
		delete file;
	}
	FBOXAPI void ScriptFile::read(const char* blob, unsigned int bytes)
	{
		if (ScriptManager::Started() && blob != 0 && bytes > 0)
		{
			v8::Local<v8::String> source = v8::String::NewFromUtf8(ScriptManager::Isolate, blob);
			if (!source.IsEmpty())
			{
				this->_script = new v8::Handle<v8::Script>;
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