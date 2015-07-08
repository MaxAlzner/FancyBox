
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Actor::build()
	{
		this->transform = new Transform;
		this->add(this->transform);
	}
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
		this->transform = 0;
		this->material = 0;
		this->camera = 0;
		this->light = 0;
	}

	FBOXAPI bool Actor::isEmpty() const
	{
		return this->transform == 0 && this->material == 0 && this->components.count() < 1;
	}

	FBOXAPI void Actor::add(Component* component)
	{
		if (component != 0)
		{
			component->object = this;
			this->components.add(component);

			if (component->componentType == "Material")
			{
				this->material = (Material*)component;
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

	FBOXAPI void Actor::attach(Mesh::Shape* shape)
	{
		if (shape != 0)
		{
			this->add(new MeshFilter(shape));
		}
	}
	FBOXAPI void Actor::attach(Image::Surface* surface, TextureFilter::TEXTURETYPE type)
	{
		if (surface != 0 && type != TextureFilter::TEXTURE_NONE && this->material != 0)
		{
			this->add(new TextureFilter(surface, type));
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