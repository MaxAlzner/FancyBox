
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Scene::dispose()
	{
		for (List<Actor*>::Iterator i = this->actors.iteratorAtEnd(); i.inside(); i.previous())
		{
			Actor* actor = i.current();
			if (actor != 0)
			{
				actor->dispose();
				delete actor;
			}
		}

		this->actors.clear();
	}

	FBOXAPI bool Scene::isEmpty() const
	{
		return this->actors.count() < 1;
	}

	FBOXAPI void Scene::update()
	{
		for (List<Actor*>::Iterator i = this->actors.iterator(); i.inside(); i.next())
		{
			Actor* actor = i.current();
			if (actor != 0)
			{
				actor->update();
			}
		}
	}
	FBOXAPI void Scene::render()
	{
		for (List<Actor*>::Iterator i = this->actors.iterator(); i.inside(); i.next())
		{
			Actor* actor = i.current();
			if (actor != 0)
			{
				if (actor->camera != 0)
				{
					actor->camera->bind();
				}

				if (actor->light != 0)
				{
					actor->light->bind();
				}
			}
		}

		for (List<Actor*>::Iterator i = this->actors.iterator(); i.inside(); i.next())
		{
			Actor* actor = i.current();
			if (actor != 0)
			{
				actor->render();
			}
		}
	}

	FBOXAPI void Scene::add(Actor* actor)
	{
		if (actor != 0)
		{
			this->actors.add(actor);
		}
	}

	FBOXAPI Actor* Scene::findActor(String name)
	{
		for (List<Actor*>::Iterator i = this->actors.iterator(); i.inside(); i.next())
		{
			Actor* actor = i.current();
			if (actor != 0 && actor->name == name)
			{
				return actor;
			}
		}

		return 0;
	}

}