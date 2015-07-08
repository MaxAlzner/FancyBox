#ifndef FBOX_SCRIPTENTITY_H
#define FBOX_SCRIPTENTITY_H
	
namespace fbox
{

	class FBOXAPI ScriptEntity
	{
	public:

		inline ScriptEntity() : _manager(0) {}
		inline ScriptEntity(ScriptManager* manager) : _manager(manager) {}
		inline ~ScriptEntity() {}

	protected:

		ScriptManager* _manager;

	};

}

#endif