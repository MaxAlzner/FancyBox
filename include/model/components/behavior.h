#ifndef FBOX_BEHAVIOR_H
#define FBOX_BEHAVIOR_H

namespace fbox
{

	class FBOXAPI Behavior : public Component
	{
	public:

		inline Behavior() : Component("Behavior") {}
		inline Behavior(String name) : Component("Behavior"), name(name) {}
		inline ~Behavior() {}

		void bind();

		void start();
		void update();

		String name;
		ScriptObject state;

	};

}

#endif