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

		bool isEmpty() const;

		void start();
		void update();
		void render();

		void add(Actor* actor);

		Actor* findActor(String name);

		String name;
		List<Actor*> actors;

	};

}

#endif