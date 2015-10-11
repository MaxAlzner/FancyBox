#ifndef FBOX_SCENE_H
#define FBOX_SCENE_H

namespace fbox
{

	class FBOXAPI Scene
	{
	public:

		inline Scene() {}
		inline ~Scene() {}

		void dispose();

		bool empty() const;

		void start();
		void update();
		void render();

		void add(Actor* actor);

		Actor* findActor(string& name);
		Actor* findActor(const char* name);

		string name;
		std::list<Actor*> actors;

	};

}

#endif