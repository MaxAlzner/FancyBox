
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Scene::dispose()
	{
		for (std::list<Actor*>::reverse_iterator i = this->actors.rbegin(); i != this->actors.rend(); i++)
		{
			Actor* actor = *i;
			if (actor != 0)
			{
				actor->dispose();
				delete actor;
			}
		}

		this->actors.clear();
	}

	FBOXAPI bool Scene::empty() const
	{
		return this->actors.size() < 1;
	}

	FBOXAPI void Scene::start()
	{
		for (std::list<Actor*>::iterator i = this->actors.begin(); i != this->actors.end(); i++)
		{
			Actor* actor = *i;
			if (actor != 0)
			{
				actor->start();
			}
		}
	}
	FBOXAPI void Scene::update()
	{
		for (std::list<Actor*>::iterator i = this->actors.begin(); i != this->actors.end(); i++)
		{
			Actor* actor = *i;
			if (actor != 0)
			{
				actor->update();
			}
		}
	}
	FBOXAPI void Scene::render()
	{
		for (std::list<Actor*>::iterator i = this->actors.begin(); i != this->actors.end(); i++)
		{
			Actor* actor = *i;
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

		for (std::list<Actor*>::iterator i = this->actors.begin(); i != this->actors.end(); i++)
		{
			Actor* actor = *i;
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
			this->actors.push_back(actor);
		}
	}

	FBOXAPI Actor* Scene::findActor(const std::string& name)
	{
		for (std::list<Actor*>::iterator i = this->actors.begin(); i != this->actors.end(); i++)
		{
			Actor* actor = *i;
			if (actor != 0 && actor->name == name)
			{
				return actor;
			}
		}

		return 0;
	}
	FBOXAPI Actor* Scene::findActor(const char* name)
	{
		return this->findActor(std::string(name));
	}

}