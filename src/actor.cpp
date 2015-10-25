
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Actor::dispose()
	{
		for (std::list<Component*>::reverse_iterator i = this->components.rbegin(); i != this->components.rend(); i++)
		{
			Component* component = *i;
			if (component != 0)
			{
				delete component;
			}
		}

		this->components.clear();
		this->texturefilters.clear();
		this->behaviors.clear();
		this->transform = 0;
		this->meshfilter = 0;
		this->material = 0;
		this->camera = 0;
		this->light = 0;
	}

	FBOXAPI bool Actor::empty() const
	{
		return this->transform == 0 && this->material == 0 && this->components.size() < 1;
	}

	FBOXAPI void Actor::start()
	{
		for (std::list<Behavior*>::iterator i = this->behaviors.begin(); i != this->behaviors.end(); i++)
		{
			Behavior* behavior = *i;
			if (behavior != 0)
			{
				behavior->start();
			}
		}
	}
	FBOXAPI void Actor::update()
	{
		this->transform->recalculate();
		for (std::list<Behavior*>::iterator i = this->behaviors.begin(); i != this->behaviors.end(); i++)
		{
			Behavior* behavior = *i;
			if (behavior != 0)
			{
				behavior->update();
			}
		}
	}
	FBOXAPI void Actor::render()
	{
		Renderer::GetUniform(UNIFORM_FLAG_UV_OFFSET)->bind2f(glm::vec2(0.0f));
		Renderer::GetUniform(UNIFORM_FLAG_UV_REPEAT)->bind2f(glm::vec2(1.0f));
		for (std::list<Component*>::iterator i = this->components.begin(); i != this->components.end(); i++)
		{
			Component* component = *i;
			if (component != 0)
			{
				component->bind();
			}
		}

		if (this->meshfilter != 0 && this->meshfilter->vao != 0)
		{
			this->meshfilter->vao->draw();
		}
	}

	FBOXAPI void Actor::add(Component* component)
	{
		if (component != 0)
		{
			component->object = this;
			this->components.push_back(component);
			if (component->componentType == "Transform")
			{
				this->transform = (Transform*)component;
			}
			else if (component->componentType == "MeshFilter")
			{
				this->meshfilter = (MeshFilter*)component;
			}
			else if (component->componentType == "TextureFilter")
			{
				this->texturefilters.push_back((TextureFilter*)component);
			}
			else if (component->componentType == "Material")
			{
				this->material = (Material*)component;
			}
			else if (component->componentType == "Behavior")
			{
				this->behaviors.push_back((Behavior*)component);
			}
			else if (component->componentType == "Camera")
			{
				this->camera = (Camera*)component;
			}
			else if (component->componentType == "Light")
			{
				this->light = (Light*)component;
			}
		}
	}

	FBOXAPI Component* Actor::findComponent(string& type)
	{
		for (std::list<Component*>::iterator i = this->components.begin(); i != this->components.end(); i++)
		{
			Component* component = *i;
			if (component != 0 && component->componentType == type)
			{
				return component;
			}
		}

		return 0;
	}
	FBOXAPI Component* Actor::findComponent(const char* type)
	{
		return this->findComponent(string(type));
	}

}