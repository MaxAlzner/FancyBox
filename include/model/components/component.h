#ifndef FBOX_COMPONENT_H
#define FBOX_COMPONENT_H

namespace fbox
{

	class FBOXAPI Component
	{
	public:

		inline Component() {}
		inline Component(String type) : componentType(type) {}
		inline ~Component() {}

		virtual void bind() = 0;

		Actor* object;
		String componentType;

	};

}

#endif