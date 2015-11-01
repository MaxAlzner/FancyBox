
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI MouseState Input::Mouse;
	FBOXAPI KeyboardState Input::Key;
	FBOXAPI GamepadState Input::Gamepad;

	FBOXAPI Scene* Stage::CurrentScene = 0;

	FBOXAPI std::list<Scene*> Stage::Scenes;
	FBOXAPI std::list<Schema*> Stage::Schemas;

	FBOXAPI glm::ivec2 Renderer::Screen(480, 320);
	FBOXAPI glm::ivec2 Renderer::MainRender(800, 600);
	FBOXAPI Camera* Renderer::MainCamera = 0;

	FBOXAPI gl::Shader* Renderer::VertexProgram = 0;
	FBOXAPI gl::Shader* Renderer::FragmentProgram = 0;
	FBOXAPI gl::Program* Renderer::MainProgram = 0;
	FBOXAPI gl::Framebuffer* Renderer::MainFramebuffer = 0;
	FBOXAPI std::vector<gl::Uniform> Renderer::Uniforms;
	FBOXAPI std::vector<gl::UniformBlock> Renderer::UniformBlocks;
	FBOXAPI std::vector<gl::VertexArray*> Renderer::VertexArrays;
	FBOXAPI std::vector<gl::Texture*> Renderer::Textures;

	FBOXAPI std::list<TextureAsset> Renderer::TextureAssets;
	FBOXAPI std::list<MeshAsset> Renderer::MeshAssets;

	FBOXAPI void Stage::ReleaseScenes()
	{
		for (std::list<Scene*>::reverse_iterator i = Scenes.rbegin(); i != Scenes.rend(); i++)
		{
			Scene* scene = *i;
			if (scene != 0)
			{
				scene->dispose();
				delete scene;
			}
		}

		Scenes.clear();
		CurrentScene = 0;
	}
	FBOXAPI void Stage::ReleaseSchemas()
	{
		for (std::list<Schema*>::reverse_iterator i = Schemas.rbegin(); i != Schemas.rend(); i++)
		{
			Schema* schema = *i;
			if (schema != 0)
			{
				schema->release();
				delete schema;
			}
		}

		Schemas.clear();
	}

	FBOXAPI void Stage::Build()
	{
		Stage::ReleaseScenes();
		Stage::CurrentScene = new Scene;
		Stage::Scenes.push_back(Stage::CurrentScene);
		for (std::list<Schema*>::iterator i = Schemas.begin(); i != Schemas.end(); i++)
		{
			Schema* schema = *i;
			if (schema != 0)
			{
				schema->apply(CurrentScene);
			}
		}
	}

	FBOXAPI void Renderer::Initialize()
	{
		//Uniforms.resize(32);
		//UniformBlocks.resize(16);
		VertexArrays.resize(64);
		Textures.resize(64);

		MainFramebuffer = new gl::Framebuffer(gl::Framebuffer::TYPE_DRAW, MainRender);
		gl::Framebuffer::screen(Screen);

		VertexProgram = new gl::Shader(gl::Shader::TYPE_VERTEX);
		FragmentProgram = new gl::Shader(gl::Shader::TYPE_FRAGMENT);
		MainProgram = new gl::Program;
		MainProgram->vertex(VertexProgram);
		MainProgram->fragment(FragmentProgram);
	}
	FBOXAPI void Renderer::Dispose()
	{
		Renderer::ReleaseAssets();
		MainProgram->release();
		delete MainProgram;
		MainProgram = 0;
		FragmentProgram->release();
		delete FragmentProgram;
		FragmentProgram = 0;
		VertexProgram->release();
		delete VertexProgram;
		VertexProgram = 0;
		MainFramebuffer->release();
		delete MainFramebuffer;
		MainFramebuffer = 0;
	}
	
	FBOXAPI void Renderer::ReleaseAssets()
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

		for (uint i = 0; i < Textures.size(); i++)
		{
			gl::Texture* texture = Textures[i];
			if (texture != 0)
			{
				texture->release();
				delete texture;
			}
		}

		for (uint i = 0; i < VertexArrays.size(); i++)
		{
			gl::VertexArray* vao = VertexArrays[i];
			if (vao != 0)
			{
				vao->release();
				delete vao;
			}
		}

		for (uint i = 0; i < UniformBlocks.size(); i++)
		{
			UniformBlocks[i].release();
		}

		Textures.clear();
		VertexArrays.clear();
		UniformBlocks.clear();
		Uniforms.clear();
		MainCamera = 0;
	}

	FBOXAPI void Renderer::GrabUniforms()
	{
		int uniforms = 0;
		glGetProgramiv(MainProgram->handle(), GL_ACTIVE_UNIFORMS, &uniforms);
		if (uniforms < 1)
		{
			printf("No uniforms could be found\n");
			return;
		}

		char* name = new char[64];
		Uniforms.resize(uniforms);
		for (int i = 0; i < uniforms; i++)
		{
			int length;
			memset(name, 0, 64);
			glGetActiveUniformName(MainProgram->handle(), i, 64, &length, name);
			UNIFORM_FLAG flag = GetUniformFlag(std::string(name));
			if (flag != UNIFORM_FLAG_INVALID)
			{
				Uniforms[(int)flag - 1] = gl::Uniform(MainProgram, std::string(name));
			}
		}

		printf("Program Uniforms\n");
		for (size_t i = 0; i < Uniforms.size(); i++)
		{
			gl::Uniform* uniform = &Uniforms[i];
			uniform->grab();
			printf("  %d ). ", i + 1);
			if (uniform->valid())
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
			delete[] name;
			printf("No uniform blocks could be found\n");
			return;
		}

		UniformBlocks.resize(blocks);
		for (int i = 0; i < blocks; i++)
		{
			int length;
			memset(name, 0, 64);
			glGetActiveUniformBlockName(MainProgram->handle(), i, 64, &length, name);
			UNIFORM_BLOCK flag = GetUniformBlockFlag(std::string(name));
			if (flag != UNIFORM_BLOCK_INVALID)
			{
				UniformBlocks[(int)flag - 1] = gl::UniformBlock(MainProgram, std::string(name));
			}
		}

		delete[] name;
		printf("Program Uniform Blocks\n");
		for (size_t i = 0; i < UniformBlocks.size(); i++)
		{
			gl::UniformBlock* block = &UniformBlocks[i];
			block->grab();
			printf("  %d ). ", i + 1);
			if (block->valid())
			{
				printf("%s : %d\n", block->name().data(), block->handle());
			}
			else
			{
				printf("Not found\n");
			}
		}
	}
	FBOXAPI void Renderer::CreateFramebuffers()
	{
		Renderer::MainFramebuffer->create();
	}
	FBOXAPI void Renderer::CompileProgram()
	{
		Renderer::VertexProgram->compile(Import::VertexShader);
		Renderer::FragmentProgram->compile(Import::FragmentShader);
		Renderer::MainProgram->link();
		Renderer::MainProgram->activate();
	}

	FBOXAPI UNIFORM_FLAG Renderer::GetUniformFlag(const std::string& name)
	{
		if (name == "os_to_ws") { return UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD; }
		else if (name == "ws_to_cs") { return UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA; }
		else if (name == "ws_to_ls") { return UNIFORM_FLAG_MATRIX_WORLD_TO_LIGHT; }
		else if (name == "projection") { return UNIFORM_FLAG_MATRIX_PROJECTION; }
		else if (name == "directionalLight_forward_ws") { return UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR; }
		else if (name == "directionalLight_color") { return UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR; }
		else if (name == "directionalLight_intensity") { return UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY; }
		else if (name == "numOfPointLights") { return UNIFORM_FLAG_LIGHT_POINT_NUM; }
		else if (name == "numOfSpotLights") { return UNIFORM_FLAG_LIGHT_SPOT_NUM; }
		else if (name == "overlay") { return UNIFORM_FLAG_COLOR_OVERLAY; }
		else if (name == "highlight") { return UNIFORM_FLAG_COLOR_HIGHLIGHT; }
		else if (name == "roughness") { return UNIFORM_FLAG_BRDF_ROUGHNESS; }
		else if (name == "refractionIndex") { return UNIFORM_FLAG_BRDF_REFRACTION_INDEX; }
		else if (name == "uvRepeat") { return UNIFORM_FLAG_UV_REPEAT; }
		else if (name == "uvOffset") { return UNIFORM_FLAG_UV_OFFSET; }
		else if (name == "screenSize") { return UNIFORM_FLAG_SIZE_SCREEN; }
		else if (name == "mapSize") { return UNIFORM_FLAG_SIZE_MAP; }
		else if (name == "randomFilter") { return UNIFORM_FLAG_FILTER_RANDOM; }
		else if (name == "gamma") { return UNIFORM_FLAG_GAMMA; }
		else if (name == "colorMap") { return UNIFORM_FLAG_MAP_COLOR; }
		else if (name == "normalMap") { return UNIFORM_FLAG_MAP_NORMAL; }
		else if (name == "specularMap") { return UNIFORM_FLAG_MAP_SPECULAR; }
		else if (name == "state") { return UNIFORM_FLAG_STATE; }
		else { return UNIFORM_FLAG_INVALID; }
	}
	FBOXAPI UNIFORM_BLOCK Renderer::GetUniformBlockFlag(const std::string& name)
	{
		if (name == "PointLight[0]") { return UNIFORM_BLOCK_LIGHT_POINT1; }
		else if (name == "PointLight[1]") { return UNIFORM_BLOCK_LIGHT_POINT2; }
		else if (name == "PointLight[2]") { return UNIFORM_BLOCK_LIGHT_POINT3; }
		else if (name == "PointLight[3]") { return UNIFORM_BLOCK_LIGHT_POINT4; }
		else if (name == "SpotLight[0]") { return UNIFORM_BLOCK_LIGHT_SPOT1; }
		else if (name == "SpotLight[1]") { return UNIFORM_BLOCK_LIGHT_SPOT2; }
		else if (name == "SpotLight[2]") { return UNIFORM_BLOCK_LIGHT_SPOT3; }
		else if (name == "SpotLight[3]") { return UNIFORM_BLOCK_LIGHT_SPOT4; }
		else { return UNIFORM_BLOCK_INVALID; }
	}

	FBOXAPI gl::Uniform* Renderer::GetUniform(UNIFORM_FLAG flag)
	{
		if (flag != UNIFORM_FLAG_INVALID)
		{
			return &Uniforms[(int)flag - 1];
		}

		return 0;
	}
	FBOXAPI gl::UniformBlock* Renderer::GetUniformBlock(UNIFORM_BLOCK block)
	{
		if (block != UNIFORM_BLOCK_INVALID)
		{
			return &UniformBlocks[(int)block - 1];
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
		FixedTime = Frame::timeValue(Ping) / Frame::timeValue(TicksPerSecond);
		DeltaTime = Frame::timeValue(LastFrameTicks) / Frame::timeValue(TicksPerSecond);

		Count++;
	}

	FBOXAPI std::string Import::VertexShader;
	FBOXAPI std::string Import::FragmentShader;

	FBOXAPI int Import::Read(const std::string& filename, char** outRaw)
	{
		FILE* file = fopen(filename.data(), "r");
		if (file != 0)
		{
			fseek(file, 0, SEEK_SET);
			int bytes = 0;
			while (fgetc(file) != EOF)
			{
				bytes++;
				if (feof(file) != 0)
				{
					break;
				}
			}

			char* raw = new char[bytes + 1];
			memset(raw, 0, bytes + 1);
			fseek(file, 0, SEEK_SET);
			fread(raw, 1, bytes, file);
			fclose(file);
			if (outRaw != 0)
			{
				*outRaw = raw;
			}
			
			return bytes;
		}

		return -1;
	}

	FBOXAPI void Import::Config(const std::string& filename)
	{
		std::ifstream file(filename.c_str());
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				if (!line.empty() && line[0] != '#')
				{
					size_t seperator = line.find_first_of('=');
					std::string key = trim(line.substr(0, seperator));
					std::string value = trim(line.substr(seperator + 1));
					printf("%s = %s\n", key.c_str(), value.c_str());
					if (key == "width")
					{
						Renderer::Screen.x = atoi(value.c_str());
					}
					else if (key == "height")
					{
						Renderer::Screen.y = atoi(value.c_str());
					}
					else if (key == "main_width")
					{
						Renderer::MainRender.x = atoi(value.c_str());
					}
					else if (key == "main_height")
					{
						Renderer::MainRender.y = atoi(value.c_str());
					}
					else if (key == "shader_vert")
					{
						Import::VertexShader = value;
					}
					else if (key == "shader_frag")
					{
						Import::FragmentShader = value;
					}
				}
			}
		}
		else
		{
			printf("Failed to open: %s\n", filename.c_str());
		}

		file.close();
	}
	FBOXAPI void Import::Config(const char* filename)
	{
		Config(std::string(filename));
	}

	FBOXAPI void Import::Load(const std::string& filename)
	{
		std::ifstream file(filename.c_str());
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				if (!line.empty())
				{
					printf("schema: %s\n", line.c_str());
					Model(line);
				}
			}
		}
		else
		{
			printf("Failed to open: %s\n", filename.c_str());
		}

		file.close();
	}
	FBOXAPI void Import::Load(const char* filename)
	{
		Load(std::string(filename));
	}

	FBOXAPI void Import::Model(const std::string& filename)
	{
		Schema* schema = new Schema;
		Stage::Schemas.push_back(schema);
		schema->parse(filename);
	}

	FBOXAPI void Import::Register(const std::string& filename, gl::Texture** outTexture)
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
		Renderer::Textures.push_back(texture);
		Renderer::TextureAssets.push_back(asset);
	}
	FBOXAPI void Import::Register(const std::string& filename, gl::VertexArray** outVertexArray)
	{
		shape* shape = new ::shape;
		FILE* file = fopen(filename.data(), "r");
		if (file != 0)
		{
			shape->read(file);
			fclose(file);
		}

		gl::VertexArray* vao = new gl::VertexArray(Renderer::MainProgram);
		vao->create(shape);
		if (outVertexArray != 0)
		{
			*outVertexArray = vao;
		}

		MeshAsset asset;
		asset.Filename = filename;
		asset.Shape = shape;
		asset.VertexArrayObject = vao;
		Renderer::VertexArrays.push_back(vao);
		Renderer::MeshAssets.push_back(asset);
	}

}