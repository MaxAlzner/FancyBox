
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	
	FBOXAPI void OnLoad()
	{
		Uniforms.resize(64);
		UniformBlocks.resize(16);
		VertexArrays.resize(64);
		Textures.resize(64);
		Assets.resize(64);

		VertexProgram = new GlShader(GlShader::TYPE_VERTEX);
		FragmentProgram = new GlShader(GlShader::TYPE_FRAGMENT);
		MainProgram = new GlProgram;
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
		Textures.clear();
		VertexArrays.clear();
		UniformBlocks.clear();
		Uniforms.clear();
		MainProgram->release();
		delete MainProgram;
		VertexProgram->release();
		delete VertexProgram;
		FragmentProgram->release();
		delete FragmentProgram;
		Assets.clear();
	}
	FBOXAPI void OnStart()
	{
		ScriptManager::Initialize();

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
	FBOXAPI void OnEnd()
	{
		ScriptManager::Dispose();

		for (int i = 0; i < Textures.count(); i++)
		{
			GlTexture* texture = Textures[i];
			if (texture != 0)
			{
				texture->release();
				delete texture;
			}
		}

		for (int i = 0; i < VertexArrays.count(); i++)
		{
			GlVertexArray* vao = VertexArrays[i];
			if (vao != 0)
			{
				vao->release();
				delete vao;
			}
		}

		for (int i = 0; i < UniformBlocks.count(); i++)
		{
			GlUniformBlock* uniform = UniformBlocks[i];
			if (uniform != 0)
			{
				uniform->release();
				delete uniform;
			}
		}

		for (int i = 0; i < Uniforms.count(); i++)
		{
			GlUniform* uniform = Uniforms[i];
			if (uniform != 0)
			{
				delete uniform;
			}
		}

		for (int i = 0; i < Assets.count(); i++)
		{
			Media* asset = Assets[i];
			if (asset != 0)
			{
				asset->release();
				delete asset;
			}
		}
	}

	FBOXAPI void OnReshape(int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	FBOXAPI void OnUpdate()
	{
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