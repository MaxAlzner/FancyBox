
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	
	FBOXAPI void OnLoad()
	{
		VertexProgram = new GlShader(GlShader::TYPE_VERTEX);
		FragmentProgram = new GlShader(GlShader::TYPE_FRAGMENT);
		MainProgram = new GlProgram;
		MainProgram->vertex(VertexProgram);
		MainProgram->fragment(FragmentProgram);
		VertexProgram->read("base.vert");
		FragmentProgram->read("base.frag");

		MainScriptManager = new ScriptManager;
		MainScriptManager->build();

		Import::Read("scratch.scene");
	}
	FBOXAPI void OnUnload()
	{
		MainScriptManager->release();
		delete MainScriptManager;
		MainProgram->release();
		delete MainProgram;
		VertexProgram->release();
		delete VertexProgram;
		FragmentProgram->release();
		delete FragmentProgram;
	}
	FBOXAPI void OnStart()
	{
		Uniforms.resize(64);
		UniformBlocks.resize(16);
		VertexArrays.resize(64);
		Textures.resize(64);
		VertexProgram->compile();
		FragmentProgram->compile();
		MainProgram->link();
		GrabUniforms();

		const int filterSize = 32 * 2;
		float* randoms = new float[filterSize];
		for (int i = 0; i < filterSize; i += 2)
		{
			float theta = random::scalar() * PI * 2.0f;
			float r = random::scalar();
			randoms[i + 0] = cos(theta) * r;
			randoms[i + 1] = sin(theta) * r;
		}
		GetUniform(UNIFORM_FLAG_RANDOM_FILTER)->bind2fv((const vec2*)randoms, filterSize / 2);
		delete[] randoms;

		Actors.resize(64);
	}
	FBOXAPI void OnEnd()
	{
		for (int i = 0; i < Actors.count(); i++)
		{
			Actor* actor = Actors[i];
			if (actor != 0)
			{
				actor->dispose();
				delete actor;
			}
		}

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

		Actors.clear();
		Textures.clear();
		VertexArrays.clear();
		UniformBlocks.clear();
		Uniforms.clear();
	}

	FBOXAPI void OnReshape(int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	FBOXAPI void OnUpdate()
	{

	}
	FBOXAPI void OnDraw()
	{
		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}