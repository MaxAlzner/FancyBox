
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Import::Read(String filepath)
	{
		XmlFile* file = new XmlFile;
		file->read(filepath);
		if (file->root != 0)
		{
			if (filepath.endsWith(".scene"))
			{
				Import::ParseScene(file->root);
			}
			else if (filepath.endsWith(".actor"))
			{
				Import::ParseActor(file->root);
			}
		}

		file->release();
		delete file;
	}

	FBOXAPI void Import::ParseScene(XmlNode* node)
	{
		node = node->first_node();
		while (node != 0)
		{
			String type = node->name();
			if (type == "actor")
			{
				Import::ParseActor(node);
			}

			node = node->next_sibling();
		}
	}
	FBOXAPI void Import::ParseActor(XmlNode* node)
	{
		Actor* actor = new Actor;
		String name = XmlFile::Value(node->last_attribute("name"));
		node = node->first_node();
		while (node != 0)
		{
			String type = node->name();
			if (type == "transform")
			{
				Import::ParseTransform(node, actor->transform);
			}
			else if (type == "material")
			{
				actor->add(Import::ParseMaterial(node));
			}
			else if (type == "mesh")
			{
				actor->add(Import::ParseMesh(node));
			}
			else if (type == "texture")
			{
				actor->add(Import::ParseMaterial(node));
			}
			else if (type == "script")
			{
				actor->add(Import::ParseBehavior(node));
			}
			else if (type == "camera")
			{
				actor->add(Import::ParseMaterial(node));
			}
			else if (type == "light")
			{
				actor->add(Import::ParseMaterial(node));
			}

			node = node->next_sibling();
		}
	}

	FBOXAPI void Import::ParseTransform(XmlNode* node, Transform* transform)
	{
		if (node != 0 && transform != 0)
		{
			node = node->first_node();
			while (node != 0)
			{
				String name = node->name();
				float v = XmlFile::ParseFloat(node, 0.0f);
				float x = XmlFile::ParseFloat(node->last_attribute("x"), 0.0f);
				float y = XmlFile::ParseFloat(node->last_attribute("y"), 0.0f);
				float z = XmlFile::ParseFloat(node->last_attribute("z"), 0.0f);
				if (name == "translate")
				{
					transform->position += vec3(x, y, z) + v;
				}
				else if (name == "rotate")
				{
					transform->rotation += vec3(x, y, z) + v;
				}
				else if (name == "scale")
				{
					v = v == 0.0f ? 1.0f : v;
					x = x == 0.0f ? 1.0f : x;
					y = y == 0.0f ? 1.0f : y;
					z = z == 0.0f ? 1.0f : z;
					transform->scale *= vec3(x, y, z) * v;
				}

				node = node->next_sibling();
			}
		}
	}
	FBOXAPI MeshFilter* Import::ParseMesh(XmlNode* node)
	{
		String src = XmlFile::Value(node->last_attribute("src"));
		return new MeshFilter;
	}
	FBOXAPI TextureFilter* Import::ParseTexture(XmlNode* node)
	{
		String src = XmlFile::Value(node->last_attribute("src"));
		return new TextureFilter;
	}
	FBOXAPI Material* Import::ParseMaterial(XmlNode* node)
	{
		Material* component = new Material;

		return component;
	}
	FBOXAPI Behavior* Import::ParseBehavior(XmlNode* node)
	{
		String src = XmlFile::Value(node->last_attribute("src"));
		return new Behavior;
	}
	FBOXAPI Camera* Import::ParseCamera(XmlNode* node)
	{
		float x = XmlFile::ParseFloat(node->last_attribute("x"), 4.0f);
		float y = XmlFile::ParseFloat(node->last_attribute("y"), 3.0f);
		float nearZ = XmlFile::ParseFloat(node->last_attribute("near"), 0.1f);
		float farZ = XmlFile::ParseFloat(node->last_attribute("far"), 100.0f);
		float fov = XmlFile::ParseFloat(node->last_attribute("fov"), 60.0f);
		return new Camera(vec2(x, y), vec2(nearZ, farZ), fov);
	}
	FBOXAPI Light* Import::ParseLight(XmlNode* node)
	{
		String type = XmlFile::Value(node->last_attribute("type"));
		float intensity = XmlFile::ParseFloat(node->last_attribute("intensity"));
		if (type == "point")
		{
			return new Light(Light::POINT, intensity);
		}
		else if (type == "spot")
		{
			return new Light(Light::SPOT, intensity);
		}
		else if (type == "directional")
		{
			return new Light(Light::DIRECTIONAL, intensity);
		}

		return new Light;
	}

}