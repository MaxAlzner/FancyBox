
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Actor::dispose()
	{
		for (List<Component*>::Iterator i = this->components.iteratorAtEnd(); i.inside(); i.previous())
		{
			Component* component = i.current();
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

	FBOXAPI bool Actor::isEmpty() const
	{
		return this->transform == 0 && this->material == 0 && this->components.count() < 1;
	}

	FBOXAPI void Actor::update()
	{
		this->transform->recalculate();
	}
	FBOXAPI void Actor::render()
	{
		GetUniform(UNIFORM_FLAG_UV_OFFSET)->bind2f(vec2(0.0f));
		GetUniform(UNIFORM_FLAG_UV_REPEAT)->bind2f(vec2(1.0f));
		for (List<Component*>::Iterator i = this->components.iterator(); i.inside(); i.next())
		{
			Component* component = i.current();
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
			this->components.add(component);
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
				this->texturefilters.add((TextureFilter*)component);
			}
			else if (component->componentType == "Material")
			{
				this->material = (Material*)component;
			}
			else if (component->componentType == "Behavior")
			{
				this->behaviors.add((Behavior*)component);
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

	FBOXAPI Component* Actor::findComponent(String type)
	{
		for (List<Component*>::Iterator i = this->components.iterator(); i.inside(); i.next())
		{
			Component* component = i.current();
			if (component != 0 && component->componentType == type)
			{
				return component;
			}
		}

		return 0;
	}

}