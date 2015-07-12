#ifndef FBOX_BEHAVIOR_H
#define FBOX_BEHAVIOR_H

namespace fbox
{

	class FBOXAPI Behavior : public Component
	{
	public:

		inline Behavior() : Component("Behavior") {}
		inline ~Behavior() {}

		void bind();

	};

}

#endif