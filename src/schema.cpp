
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Schema::release()
	{
		this->scripts.clear();

		for (std::list<ActorModel*>::reverse_iterator i = this->actors.rbegin(); i != this->actors.rend(); i++)
		{
			ActorModel* actor = *i;
			if (actor != 0)
			{
				for (std::list<ComponentModel*>::reverse_iterator i = actor->transforms.rbegin(); i != actor->transforms.rend(); i++)
				{
					ComponentModel* transform = *i;
					if (transform != 0)
					{
						transform->attributes.clear();
						delete transform;
					}
				}

				for (std::list<ComponentModel*>::reverse_iterator i = actor->components.rbegin(); i != actor->components.rend(); i++)
				{
					ComponentModel* component = *i;
					if (component != 0)
					{
						delete component;
					}
				}

				actor->transforms.clear();
				actor->components.clear();
				delete actor;
			}
		}

		this->actors.clear();
	}

	FBOXAPI void Schema::parse(string& filename)
	{
		char* raw = 0;
		if (Import::Read(filename, &raw) > 0)
		{
			XmlDocument document;
			document.parse<0>(raw);
			XmlNode* root = document.first_node();
			if (root != 0)
			{
				this->parse(root);
			}

			document.clear();
			delete[] raw;
		}
	}
	FBOXAPI void Schema::parse(XmlNode* node)
	{
		if (node != 0)
		{
			string type = node->name();
			if (type == "scene")
			{
				XmlNode* child = node->first_node();
				while (child != 0)
				{
					this->parse(child);
					child = child->next_sibling();
				}
			}
			else if (type == "script")
			{
				string src = Schema::value(node->last_attribute("src"));
				this->scripts.push_back(src);
			}
			else if (type == "actor")
			{
				ActorModel* actor = new ActorModel;
				this->parse(node, actor);
				this->actors.push_back(actor);
			}
		}
	}
	FBOXAPI void Schema::parse(XmlNode* node, ActorModel* actor)
	{
		if (node != 0 && actor != 0)
		{
			actor->name = Schema::value(node->last_attribute("name"));
			XmlNode* child = node->first_node();
			while (child != 0)
			{
				string type = child->name();
				if (type == "transform")
				{
					XmlNode* transformation = child->first_node();
					while (transformation != 0)
					{
						ComponentModel* transform = new ComponentModel;
						this->parse(transformation, transform);
						actor->transforms.push_back(transform);
						transformation = transformation->next_sibling();
					}
				}
				else
				{
					ComponentModel* component = new ComponentModel;
					this->parse(child, component);
					actor->components.push_back(component);
				}

				child = child->next_sibling();
			}
		}
	}
	FBOXAPI void Schema::parse(XmlNode* node, ComponentModel* component)
	{
		if (node != 0 && component != 0)
		{
			*component = ComponentModel();
			component->type = node->name();
			XmlAttribute* attribute = node->first_attribute();
			while (attribute != 0)
			{
				string name = attribute->name();
				string value = attribute->value();
				component->attributes.insert(std::pair<string, string>(name, value));
				attribute = attribute->next_attribute();
			}
		}
	}

	FBOXAPI void Schema::apply(Scene* scene)
	{
		if (scene != 0)
		{
			for (std::list<string>::iterator i = this->scripts.begin(); i != this->scripts.end(); i++)
			{
				js::Manager::Register(*i);
			}

			for (std::list<ActorModel*>::iterator i = this->actors.begin(); i != this->actors.end(); i++)
			{
				ActorModel* model = *i;
				if (model != 0)
				{
					Actor* actor = new Actor;
					actor->name = model->name;
					for (std::list<ComponentModel*>::iterator i = model->transforms.begin(); i != model->transforms.end(); i++)
					{
						ComponentModel* transform = *i;
						if (transform != 0)
						{
							float x = (float)atof(transform->attributes["x"].c_str());
							float y = (float)atof(transform->attributes["y"].c_str());
							float z = (float)atof(transform->attributes["z"].c_str());
							if (transform->type == "translate")
							{
								actor->transform->position += glm::vec3(x, y, z);
							}
							else if (transform->type == "rotate")
							{
								actor->transform->rotation += glm::vec3(x, y, z);
							}
							else if (transform->type == "scale")
							{
								actor->transform->scale *= glm::vec3(x == 0.0f ? 1.0f : x, y == 0.0f ? 1.0f : y, z == 0.0f ? 1.0f : z);
							}
						}
					}

					for (std::list<ComponentModel*>::iterator i = model->components.begin(); i != model->components.end(); i++)
					{
						ComponentModel* component = *i;
						if (component != 0)
						{
							if (component->type == "mesh")
							{
								string src = component->attributes["src"];
								gl::VertexArray* vao = 0;
								Import::Register(src, &vao);
								actor->add(new MeshFilter(vao));
							}
							else if (component->type == "texture")
							{
								string src = component->attributes["src"];
								string type = component->attributes["type"];
								gl::Texture* texture = 0;
								Import::Register(src, &texture);
								if (type == "diffuse")
								{
									actor->add(new TextureFilter(TextureFilter::TEXTURE_COLOR, texture));
								}
								else if (type == "normal")
								{
									actor->add(new TextureFilter(TextureFilter::TEXTURE_NORMAL, texture));
								}
								else if (type == "specular")
								{
									actor->add(new TextureFilter(TextureFilter::TEXTURE_SPECULAR, texture));
								}
							}
							else if (component->type == "material")
							{
								Material* material = new Material;
								actor->add(material);
							}
							else if (component->type == "behavior")
							{
								string name = component->attributes["name"];
								actor->add(new Behavior(name));
							}
							else if (component->type == "camera")
							{
								float x = fvalue(component->attributes["x"] , 4.0f);
								float y = fvalue(component->attributes["y"], 3.0f);
								float nearZ = fvalue(component->attributes["near"], 0.1f);
								float farZ = fvalue(component->attributes["far"], 100.0f);
								float fov = fvalue(component->attributes["fov"], 60.0f);
								actor->add(new Camera(glm::vec2(x, y), glm::vec2(nearZ, farZ), fov));
							}
							else if (component->type == "light")
							{
								string type = component->attributes["type"];
								Light* light = 0;
								if (type == "point")
								{
									light = new Light(Light::LIGHT_POINT);
								}
								else if (type == "spot")
								{
									light = new Light(Light::LIGHT_SPOT);
								}
								else if (type == "directional")
								{
									light = new Light(Light::LIGHT_DIRECTIONAL);
								}
								else
								{
									light = new Light;
								}

								light->color = Schema::color(component->attributes["color"]);
								light->intensity = fvalue(component->attributes["intensity"], 1.0f);
								light->range = fvalue(component->attributes["range"], 5.0f);
								light->angle = fvalue(component->attributes["angle"], 60.0f);
								actor->add(light);
							}
						}
					}

					scene->add(actor);
				}
			}
		}
	}

	FBOXAPI string Schema::value(XmlAttribute* attribute)
	{
		return attribute != 0 ? attribute->value() : "";
	}
	FBOXAPI float Schema::fvalue(string& str, float def)
	{
		return str.empty() ? def : (float)atof(str.c_str());
	}
	FBOXAPI int Schema::ivalue(string& str, int def)
	{
		return str.empty() ? def : atoi(str.c_str());
	}
	FBOXAPI bool Schema::bvalue(string& str, bool def)
	{
		return str == "true";
	}
	FBOXAPI glm::vec4 Schema::color(string& str)
	{
		glm::vec4 c(1.0f);
		if (!str.empty())
		{
			int r, g, b;
			sscanf_s(str.c_str(), "rgba(%d, %d, %d, %f)", &r, &g, &b, &c.a);
			c.r = float(r) / 255.0f;
			c.g = float(g) / 255.0f;
			c.b = float(b) / 255.0f;
		}

		return c;
	}

}