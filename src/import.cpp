
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	using namespace Image;
	using namespace Mesh;
	using namespace Sound;

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

	FBOXAPI void Import::Register(String filepath, GlTexture** outTexture)
	{
		Surface* surface = new Surface;
		surface->read(filepath);
		GlTexture* texture = new GlTexture;
		texture->create(surface);
		if (outTexture != 0)
		{
			*outTexture = texture;
		}

		TextureAsset asset;
		asset.Filepath = filepath;
		asset.Surface = surface;
		asset.Texture = texture;
		Assets.add(surface);
		Textures.add(texture);
		TextureAssets.add(asset);
	}
	FBOXAPI void Import::Register(String filepath, GlVertexArray** outVertexArray)
	{
		Shape* shape = new Shape;
		shape->read(filepath);
		GlVertexArray* vao = new GlVertexArray(MainProgram);
		vao->create(shape);
		if (outVertexArray != 0)
		{
			*outVertexArray = vao;
		}

		MeshAsset asset;
		asset.Filepath = filepath;
		asset.Shape = shape;
		asset.VertexArrayObject = vao;
		Assets.add(shape);
		VertexArrays.add(vao);
		MeshAssets.add(asset);
	}
	FBOXAPI void Import::Register(String filepath, ScriptFile** outScriptFile)
	{
		ScriptFile* script = new ScriptFile(MainScriptManager);
		script->read(filepath);
		if (outScriptFile != 0)
		{
			*outScriptFile = script;
		}

		ScriptAsset asset;
		asset.Filepath = filepath;
		asset.Script = script;
		ScriptAssets.add(asset);
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
		actor->name = XmlFile::Value(node->last_attribute("name"));
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
				actor->add(Import::ParseTexture(node));
			}
			else if (type == "script")
			{
				actor->add(Import::ParseBehavior(node));
			}
			else if (type == "camera")
			{
				actor->add(Import::ParseCamera(node));
			}
			else if (type == "light")
			{
				actor->add(Import::ParseLight(node));
			}

			node = node->next_sibling();
		}

		MainScene->add(actor);
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
		GlVertexArray* vao = 0;
		Register(src, &vao);
		return new MeshFilter(vao);
	}
	FBOXAPI TextureFilter* Import::ParseTexture(XmlNode* node)
	{
		String src = XmlFile::Value(node->last_attribute("src"));
		String type = XmlFile::Value(node->last_attribute("type"));
		GlTexture* texture = 0;
		Register(src, &texture);
		if (type == "diffuse")
		{
			return new TextureFilter(TextureFilter::TEXTURE_COLOR, texture);
		}
		else if (type == "normal")
		{
			return new TextureFilter(TextureFilter::TEXTURE_NORMAL, texture);
		}
		else if (type == "specular")
		{
			return new TextureFilter(TextureFilter::TEXTURE_SPECULAR, texture);
		}

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
		ScriptFile* script = 0;
		Register(src, &script);
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
			return new Light(Light::LIGHT_POINT, intensity);
		}
		else if (type == "spot")
		{
			return new Light(Light::LIGHT_SPOT, intensity);
		}
		else if (type == "directional")
		{
			return new Light(Light::LIGHT_DIRECTIONAL, intensity);
		}

		return new Light;
	}

}