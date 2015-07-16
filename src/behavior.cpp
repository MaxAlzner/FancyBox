
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Behavior::bind()
	{

	}

	FBOXAPI void Behavior::start()
	{
		if (!name.isEmpty())
		{
			this->state = ScriptManager::Global().construct(this->name);
		}

		ScriptArray props = this->state.properties();
		for (ScriptArray::Iterator i = props.begin(); i < props.count(); i++)
		{
			printf(" %d ). %s : %s\n", i.index() + 1, (const char*)i.gets(), (const char*)this->state.typeof(i.gets()));
		}
	}
	FBOXAPI void Behavior::update()
	{

	}

}