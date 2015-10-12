
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	
	FBOXAPI void OnLoad()
	{
		Uniforms.resize(32);
		UniformBlocks.resize(16);
		VertexArrays.resize(64);
		Textures.resize(64);

		VertexProgram = new gl::Shader(gl::Shader::TYPE_VERTEX);
		FragmentProgram = new gl::Shader(gl::Shader::TYPE_FRAGMENT);
		MainProgram = new gl::Program;
		MainProgram->vertex(VertexProgram);
		MainProgram->fragment(FragmentProgram);
		VertexProgram->read("base.vert");
		FragmentProgram->read("base.frag");

		MainScene = new Scene;
	}
	FBOXAPI void OnUnload()
	{
		MainScene->dispose();
		delete MainScene;
		MainScene = 0;
		MainProgram->release();
		delete MainProgram;
		MainProgram = 0;
		FragmentProgram->release();
		delete FragmentProgram;
		FragmentProgram = 0;
		VertexProgram->release();
		delete VertexProgram;
		VertexProgram = 0;

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
			gl::UniformBlock* uniform = UniformBlocks[i];
			if (uniform != 0)
			{
				uniform->release();
				delete uniform;
			}
		}

		for (uint i = 0; i < Uniforms.size(); i++)
		{
			gl::Uniform* uniform = Uniforms[i];
			if (uniform != 0)
			{
				delete uniform;
			}
		}

		Textures.clear();
		VertexArrays.clear();
		UniformBlocks.clear();
		Uniforms.clear();
	}

	FBOXAPI void OnInitialize()
	{
		js::Manager::Initialize();
		FreeImage_Initialise();

		if (glewInit() != GLEW_OK)
		{
			exit(1);
		}

		if (!GLEW_VERSION_3_0)
		{
			exit(1);
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);

		VertexProgram->compile();
		FragmentProgram->compile();
		MainProgram->link();
		MainProgram->activate();
		GrabUniforms();

#if 0
		const int filterSize = 32 * 2;
		float* randoms = new float[filterSize];
		for (int i = 0; i < filterSize; i += 2)
		{
			float theta = random::scalar() * PI * 2.0f;
			float r = random::scalar();
			randoms[i + 0] = cos(theta) * r;
			randoms[i + 1] = sin(theta) * r;
		}
		GetUniform(UNIFORM_FLAG_FILTER_RANDOM)->bind2fv((const vec2*)randoms, filterSize / 2);
		delete[] randoms;
#endif
	}
	FBOXAPI void OnDispose()
	{
		ReleaseAssets();
		FreeImage_DeInitialise();
		js::Manager::Dispose();
	}

	FBOXAPI void OnReshape(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	FBOXAPI void OnStart()
	{
#if 1
		js::Object global = js::Manager::Global();
		js::Array globals = global.properties();
		for (int i = 0; i < globals.count(); i++)
		{
			printf(" %d ). %s : %s\n", i + 1, (const char*)globals.gets(i).data(), (const char*)global.typeof(globals.gets(i)).data());
			js::Object property = global.get(globals.gets(i).data());
			js::Array props = property.properties();
			for (int k = 0; k < props.count(); k++)
			{
				printf("   %d ). %s : %s\n", k + 1, (const char*)props.gets(k).data(), (const char*)property.typeof(props.gets(k)).data());
			}
		}

#endif
		if (MainScene != 0)
		{
			MainScene->start();
		}
	}
	FBOXAPI void OnUpdate()
	{
		if (Input.Key[KEY_Q])
		{
			MainCamera->object->transform->rotation.y += 5.0f;
		}

		if (Input.Key[KEY_E])
		{
			MainCamera->object->transform->rotation.y -= 5.0f;
		}

		if (Input.Key[KEY_Z])
		{
			MainCamera->object->transform->rotation.x += 5.0f;
		}

		if (Input.Key[KEY_C])
		{
			MainCamera->object->transform->rotation.x -= 5.0f;
		}

		if (Input.Key[KEY_W])
		{
			MainCamera->object->transform->position += MainCamera->object->transform->forward * 0.1f;
		}

		if (Input.Key[KEY_S])
		{
			MainCamera->object->transform->position -= MainCamera->object->transform->forward * 0.1f;
		}

		if (Input.Key[KEY_A])
		{
			MainCamera->object->transform->position += MainCamera->object->transform->right * 0.1f;
		}

		if (Input.Key[KEY_D])
		{
			MainCamera->object->transform->position -= MainCamera->object->transform->right * 0.1f;
		}

		//MainScene->findActor("PointLight1")->transform->position.y = sin((float(Frame::Current()) / 60.0f) * M_PI) + 0.5f;

		if (MainScene != 0)
		{
			MainScene->update();
		}
	}
	FBOXAPI void OnDraw()
	{
		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (MainScene != 0)
		{
			MainScene->render();
		}
	}

}