
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI InputState Input;

	FBOXAPI gl::Shader* VertexProgram = 0;
	FBOXAPI gl::Shader* FragmentProgram = 0;
	FBOXAPI gl::Program* MainProgram = 0;
	FBOXAPI std::vector<gl::Uniform*> Uniforms;
	FBOXAPI std::vector<gl::UniformBlock*> UniformBlocks;
	FBOXAPI std::vector<gl::VertexArray*> VertexArrays;
	FBOXAPI std::vector<gl::Texture*> Textures;

	//FBOXAPI std::vector<Media*> Assets;
	FBOXAPI std::list<TextureAsset> TextureAssets;
	FBOXAPI std::list<MeshAsset> MeshAssets;
	//FBOXAPI std::list<AudioAsset> AudioAssets;
	//FBOXAPI std::list<ScriptAsset> ScriptAssets;

	FBOXAPI Camera* MainCamera = 0;
	FBOXAPI Scene* MainScene = 0;

	FBOXAPI void ReleaseAssets()
	{
		for (std::list<TextureAsset>::reverse_iterator i = TextureAssets.rbegin(); i != TextureAssets.rend(); i++)
		{
			TextureAsset asset = *i;
			if (asset.Surface != 0)
			{
				FreeImage_Unload(asset.Surface);
			}
		}

		for (std::list<MeshAsset>::reverse_iterator i = MeshAssets.rbegin(); i != MeshAssets.rend(); i++)
		{
			MeshAsset asset = *i;
			if (asset.Shape != 0)
			{
				asset.Shape->clear();
				delete asset.Shape;
			}
		}

		TextureAssets.clear();
		MeshAssets.clear();
	}

	FBOXAPI void GrabUniforms()
	{
		int uniforms = 0;
		glGetProgramiv(MainProgram->handle(), GL_ACTIVE_UNIFORMS, &uniforms);
		if (uniforms < 1)
		{
			printf("No uniforms could be found\n");
			return;
		}

		char* name = new char[64];
		for (int i = 0; i < uniforms; i++)
		{
			int length;
			memset(name, 0, 64);
			glGetActiveUniformName(MainProgram->handle(), i, 64, &length, name);
			UNIFORM_FLAG flag = GetUniformFlag(string(name));
			if (flag != UNIFORM_FLAG_INVALID)
			{
				gl::Uniform* uniform = new gl::Uniform(MainProgram, string(name));
				uniform->grab();
				Uniforms[(int)flag - 1] = uniform;
			}
		}

		delete[] name;
		printf("Program Uniforms\n");
		for (int i = 0; i < Uniforms.size(); i++)
		{
			gl::Uniform* uniform = Uniforms[i];
			printf("  %d ). ", i + 1);
			if (uniform != 0)
			{
				printf("%s : %d\n", uniform->name().data(), uniform->handle());
			}
			else
			{
				printf("Not found\n");
			}
		}

		int blocks = 0;
		glGetProgramiv(MainProgram->handle(), GL_ACTIVE_UNIFORM_BLOCKS, &blocks);
		if (blocks < 1)
		{
			printf("No uniform blocks could be found\n");
			return;
		}

		name = new char[64];
		for (int i = 0; i < blocks; i++)
		{
			int length;
			memset(name, 0, 64);
			glGetActiveUniformBlockName(MainProgram->handle(), i, 64, &length, name);
			UNIFORM_BLOCK flag = GetUniformBlockFlag(string(name));
			if (flag != UNIFORM_BLOCK_INVALID)
			{
				gl::UniformBlock* block = new gl::UniformBlock(MainProgram, string(name));
				block->grab();
				UniformBlocks[(int)flag - 1] = block;
			}
		}

		delete[] name;
		printf("Program Uniform Blocks\n");
		for (int i = 0; i < UniformBlocks.size(); i++)
		{
			gl::UniformBlock* block = UniformBlocks[i];
			printf("  %d ). ", i + 1);
			if (block != 0)
			{
				printf("%s : %d\n", block->name().data(), block->handle());
			}
			else
			{
				printf("Not found\n");
			}
		}
	}

	FBOXAPI UNIFORM_FLAG GetUniformFlag(string& name)
	{
		if (name == "os_to_ws") return UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD;
		else if (name == "ws_to_cs") return UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA;
		else if (name == "ws_to_ls") return UNIFORM_FLAG_MATRIX_WORLD_TO_LIGHT;
		else if (name == "projection") return UNIFORM_FLAG_MATRIX_PROJECTION;
		else if (name == "directionalLight_forward_ws") return UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR;
		else if (name == "directionalLight_color") return UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR;
		else if (name == "directionalLight_intensity") return UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY;
		//else if (name == "pointLight_pos_ws") return UNIFORM_FLAG_LIGHT_POINT_POSITION;
		//else if (name == "pointLight_color") return UNIFORM_FLAG_LIGHT_POINT_COLOR;
		//else if (name == "pointLight_intensity") return UNIFORM_FLAG_LIGHT_POINT_INTENSITY;
		//else if (name == "pointLight_range") return UNIFORM_FLAG_LIGHT_POINT_RANGE;
		else if (name == "numOfPointLights") return UNIFORM_FLAG_LIGHT_POINT_NUM;
		//else if (name == "spotLight_pos_ws") return UNIFORM_FLAG_LIGHT_SPOT_POSITION;
		//else if (name == "spotLight_forward_ws") return UNIFORM_FLAG_LIGHT_SPOT_VECTOR;
		//else if (name == "spotLight_color") return UNIFORM_FLAG_LIGHT_SPOT_COLOR;
		//else if (name == "spotLight_intensity") return UNIFORM_FLAG_LIGHT_SPOT_INTENSITY;
		//else if (name == "spotLight_range") return UNIFORM_FLAG_LIGHT_SPOT_RANGE;
		else if (name == "numOfSpotLights") return UNIFORM_FLAG_LIGHT_SPOT_NUM;
		else if (name == "overlay") return UNIFORM_FLAG_COLOR_OVERLAY;
		else if (name == "highlight") return UNIFORM_FLAG_COLOR_HIGHLIGHT;
		else if (name == "roughness") return UNIFORM_FLAG_BRDF_ROUGHNESS;
		else if (name == "refractionIndex") return UNIFORM_FLAG_BRDF_REFRACTION_INDEX;
		else if (name == "uvRepeat") return UNIFORM_FLAG_UV_REPEAT;
		else if (name == "uvOffset") return UNIFORM_FLAG_UV_OFFSET;
		else if (name == "screenSize") return UNIFORM_FLAG_SIZE_SCREEN;
		else if (name == "mapSize") return UNIFORM_FLAG_SIZE_MAP;
		else if (name == "randomFilter") return UNIFORM_FLAG_FILTER_RANDOM;
		else if (name == "gamma") return UNIFORM_FLAG_GAMMA;
		else if (name == "colorMap") return UNIFORM_FLAG_MAP_COLOR;
		else if (name == "normalMap") return UNIFORM_FLAG_MAP_NORMAL;
		else if (name == "specularMap") return UNIFORM_FLAG_MAP_SPECULAR;
		else if (name == "state") return UNIFORM_FLAG_STATE;
		else return UNIFORM_FLAG_INVALID;
	}
	FBOXAPI UNIFORM_BLOCK GetUniformBlockFlag(string& name)
	{
		if (name == "PointLight[0]") return UNIFORM_BLOCK_LIGHT_POINT1;
		else if (name == "PointLight[1]") return UNIFORM_BLOCK_LIGHT_POINT2;
		else if (name == "PointLight[2]") return UNIFORM_BLOCK_LIGHT_POINT3;
		else if (name == "PointLight[3]") return UNIFORM_BLOCK_LIGHT_POINT4;
		else if (name == "SpotLight[0]") return UNIFORM_BLOCK_LIGHT_SPOT1;
		else if (name == "SpotLight[1]") return UNIFORM_BLOCK_LIGHT_SPOT2;
		else if (name == "SpotLight[2]") return UNIFORM_BLOCK_LIGHT_SPOT3;
		else if (name == "SpotLight[3]") return UNIFORM_BLOCK_LIGHT_SPOT4;
		else return UNIFORM_BLOCK_INVALID;
	}

	FBOXAPI gl::Uniform* GetUniform(UNIFORM_FLAG flag)
	{
		if (flag != UNIFORM_FLAG_INVALID)
		{
			return Uniforms[(int)flag - 1];
		}

		return 0;
	}
	FBOXAPI gl::UniformBlock* GetUniformBlock(UNIFORM_BLOCK block)
	{
		if (block != UNIFORM_BLOCK_INVALID)
		{
			return UniformBlocks[(int)block - 1];
		}

		return 0;
	}

	FBOXAPI Frame::frameValue Frame::Count = 0;
	FBOXAPI Frame::frameValue Frame::Current = 0;
	FBOXAPI Frame::frameValue Frame::Rate = 0;

	FBOXAPI Frame::timeValue Frame::FixedTime = 0.0f;
	FBOXAPI Frame::timeValue Frame::DeltaTime = 0.0f;

	FBOXAPI Frame::clockValue Frame::Ping = 0;
	FBOXAPI Frame::clockValue Frame::LastFrameTicks = 0;
	FBOXAPI Frame::clockValue Frame::LastSecond = 0;

	FBOXAPI Frame::frameValue Frame::FramesPerSecond = 60;
	FBOXAPI Frame::clockValue Frame::TicksPerSecond = CLOCKS_PER_SEC;
	FBOXAPI Frame::clockValue Frame::TicksPerFrame = Frame::TicksPerSecond / Frame::FramesPerSecond;

	FBOXAPI void Frame::SetFramesPerSecond(frameValue fps)
	{
		FramesPerSecond = fps;
		TicksPerSecond = CLOCKS_PER_SEC;
		TicksPerFrame = TicksPerSecond / clockValue(fps);
	}

	FBOXAPI void Frame::Start()
	{
		clockValue NewPing = clock();
		clockValue ThisSecond = NewPing / TicksPerSecond;

		Current++;
		if (LastSecond != ThisSecond)
		{
			Rate = Current;
			Current = 0;
			LastSecond = ThisSecond;
		}

		Ping = NewPing;
	}
	FBOXAPI void Frame::Finish()
	{
		clockValue NewPing = clock();
		LastFrameTicks = NewPing > Ping ? NewPing - Ping : 0;
		FixedTime = float(Ping) / float(TicksPerSecond);
		DeltaTime = float(LastFrameTicks) / float(TicksPerSecond);

		Count++;
	}

	FBOXAPI void Import::Read(string& filename)
	{
		FILE* file = fopen(filename.data(), "r");
		if (file != 0)
		{
			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			char* raw = new char[size + 1];
			memset(raw, 0, size + 1);
			fseek(file, 0, SEEK_SET);
			fread(raw, 1, size, file);

			XmlDocument document;
			document.parse<0>(raw);
			XmlNode* root = document.first_node();
			if (root != 0)
			{
				string type = root->name();
				if (type == "scene")
				{
					Import::ParseScene(root);
				}
				else if (type == "actor")
				{
					Import::ParseActor(root);
				}
			}

			document.clear();
			delete[] raw;
			fclose(file);
		}
	}

	FBOXAPI void Import::Register(string& filename, gl::Texture** outTexture)
	{
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename.data());
		if (format == FIF_UNKNOWN)
		{
			return;
		}

		surface* surface = FreeImage_ConvertTo32Bits(FreeImage_Load(format, filename.data()));

		gl::Texture* texture = new gl::Texture;
		texture->create(surface);
		if (outTexture != 0)
		{
			*outTexture = texture;
		}

		TextureAsset asset;
		asset.Filename = filename;
		asset.Surface = surface;
		asset.Texture = texture;
		//Assets.push_back(surface);
		Textures.push_back(texture);
		TextureAssets.push_back(asset);
	}
	FBOXAPI void Import::Register(string& filename, gl::VertexArray** outVertexArray)
	{
		shape* shape = new ::shape;
		FILE* file = fopen(filename.data(), "r");
		if (file != 0)
		{
			shape->read(file);
			fclose(file);
		}

		gl::VertexArray* vao = new gl::VertexArray(MainProgram);
		vao->create(shape);
		if (outVertexArray != 0)
		{
			*outVertexArray = vao;
		}

		MeshAsset asset;
		asset.Filename = filename;
		asset.Shape = shape;
		asset.VertexArrayObject = vao;
		//Assets.push_back(shape);
		VertexArrays.push_back(vao);
		MeshAssets.push_back(asset);
	}

	FBOXAPI void Import::ParseScript(XmlNode* node)
	{
		string src = Value(node->last_attribute("src"));
		js::Manager::Register(src);
	}
	FBOXAPI void Import::ParseScene(XmlNode* node)
	{
		node = node->first_node();
		while (node != 0)
		{
			string type = node->name();
			if (type == "actor")
			{
				Import::ParseActor(node);
			}
			else if (type == "script")
			{
				Import::ParseScript(node);
			}

			node = node->next_sibling();
		}
	}
	FBOXAPI void Import::ParseActor(XmlNode* node)
	{
		Actor* actor = new Actor;
		actor->name = Value(node->last_attribute("name"));
		node = node->first_node();
		while (node != 0)
		{
			string type = node->name();
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
			else if (type == "behavior")
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
				string name = node->name();
				float v = ParseFloat(node, 0.0f);
				float x = ParseFloat(node->last_attribute("x"), 0.0f);
				float y = ParseFloat(node->last_attribute("y"), 0.0f);
				float z = ParseFloat(node->last_attribute("z"), 0.0f);
				if (name == "translate")
				{
					transform->position += glm::vec3(x, y, z) + v;
				}
				else if (name == "rotate")
				{
					transform->rotation += glm::vec3(x, y, z) + v;
				}
				else if (name == "scale")
				{
					v = v == 0.0f ? 1.0f : v;
					x = x == 0.0f ? 1.0f : x;
					y = y == 0.0f ? 1.0f : y;
					z = z == 0.0f ? 1.0f : z;
					transform->scale *= glm::vec3(x, y, z) * v;
				}

				node = node->next_sibling();
			}
		}
	}
	FBOXAPI MeshFilter* Import::ParseMesh(XmlNode* node)
	{
		string src = Value(node->last_attribute("src"));
		gl::VertexArray* vao = 0;
		Register(src, &vao);
		return new MeshFilter(vao);
	}
	FBOXAPI TextureFilter* Import::ParseTexture(XmlNode* node)
	{
		string src = Value(node->last_attribute("src"));
		string type = Value(node->last_attribute("type"));
		gl::Texture* texture = 0;
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
		string name = Value(node->last_attribute("name"));
		return new Behavior(name);
	}
	FBOXAPI Camera* Import::ParseCamera(XmlNode* node)
	{
		float x = ParseFloat(node->last_attribute("x"), 4.0f);
		float y = ParseFloat(node->last_attribute("y"), 3.0f);
		float nearZ = ParseFloat(node->last_attribute("near"), 0.1f);
		float farZ = ParseFloat(node->last_attribute("far"), 100.0f);
		float fov = ParseFloat(node->last_attribute("fov"), 60.0f);
		return new Camera(glm::vec2(x, y), glm::vec2(nearZ, farZ), fov);
	}
	FBOXAPI Light* Import::ParseLight(XmlNode* node)
	{
		string type = Value(node->last_attribute("type"));
		glm::vec4 color = ParseColor(node->last_attribute("color"));
		float intensity = ParseFloat(node->last_attribute("intensity"), 1.0f);
		float range = ParseFloat(node->last_attribute("range"), 5.0f);
		if (type == "point")
		{
			return new Light(Light::LIGHT_POINT, color, intensity);
		}
		else if (type == "spot")
		{
			return new Light(Light::LIGHT_SPOT, color, intensity, range);
		}
		else if (type == "directional")
		{
			return new Light(Light::LIGHT_DIRECTIONAL, color, intensity, range);
		}

		return new Light;
	}

	FBOXAPI int Import::ParseInt(XmlNode* node, int defaultValue)
	{
		if (node == 0) return defaultValue;
		char* value = node->value();
		if (value == 0) return defaultValue;

		return atoi(value);
	}
	FBOXAPI int Import::ParseInt(XmlAttribute* attr, int defaultValue)
	{
		if (attr == 0) return defaultValue;
		char* value = attr->value();
		if (value == 0) return defaultValue;

		return atoi(value);
	}
	FBOXAPI float Import::ParseFloat(XmlNode* node, float defaultValue)
	{
		if (node == 0) return defaultValue;
		char* value = node->value();
		if (value == 0) return defaultValue;

		return (float)atof(value);
	}
	FBOXAPI float Import::ParseFloat(XmlAttribute* attr, float defaultValue)
	{
		if (attr == 0) return defaultValue;
		char* value = attr->value();
		if (value == 0) return defaultValue;

		return (float)atof(value);
	}
	FBOXAPI bool Import::ParseBool(XmlNode* node, bool defaultValue)
	{
		if (node == 0) return defaultValue;
		char* value = node->value();
		if (value == 0) return defaultValue;

		if (strstr(value, "true") != 0) return true;
		return false;
	}
	FBOXAPI bool Import::ParseBool(XmlAttribute* attr, bool defaultValue)
	{
		if (attr == 0) return defaultValue;
		char* value = attr->value();
		if (value == 0) return defaultValue;

		if (strstr(value, "true") != 0) return true;
		return false;
	}

	FBOXAPI glm::vec4 Import::ParseColor(XmlNode* node)
	{
		glm::vec4 c(1.0f);
		if (node == 0)
		{
			return c;
		}

		XmlNode* child = 0;
		child = node->first_node("red");
		if (child != 0) c.r = ParseFloat(child, 1.0f);
		child = node->first_node("green");
		if (child != 0) c.g = ParseFloat(child, 1.0f);
		child = node->first_node("blue");
		if (child != 0) c.b = ParseFloat(child, 1.0f);

		return c;
	}
	FBOXAPI glm::vec4 Import::ParseColor(XmlAttribute* attr)
	{
		glm::vec4 c(1.0f);
		if (attr != 0)
		{
			int r, g, b;
			sscanf_s(attr->value(), "rgba(%d, %d, %d, %f)", &r, &g, &b, &c.a);
			c.r = float(r) / 255.0f;
			c.g = float(g) / 255.0f;
			c.b = float(b) / 255.0f;
		}

		return c;
	}
	FBOXAPI string Import::Value(XmlAttribute* attr)
	{
		return attr != 0 ? string(attr->value()) : string();
	}

}