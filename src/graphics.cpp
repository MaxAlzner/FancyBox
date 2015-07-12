
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

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
			UNIFORM_FLAG flag = GetUniformFlag(String(name));
			if (flag != UNIFORM_FLAG_INVALID)
			{
				GlUniform* uniform = new GlUniform(MainProgram, name);
				uniform->grab();
				Uniforms[(int)flag - 1] = uniform;
			}
		}

		delete[] name;
		printf("Program Uniforms\n");
		for (int i = 0; i < Uniforms.count(); i++)
		{
			GlUniform* uniform = Uniforms[i];
			printf("  %d ). ", i + 1);
			if (uniform != 0)
			{
				printf("%s : %d\n", (const char*)uniform->name(), uniform->handle());
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
			UNIFORM_BLOCK flag = GetUniformBlockFlag(String(name));
			if (flag != UNIFORM_BLOCK_INVALID)
			{
				GlUniformBlock* block = new GlUniformBlock(MainProgram, name);
				block->grab();
				UniformBlocks[(int)flag - 1] = block;
			}
		}

		delete[] name;
		printf("Program Uniform Blocks\n");
		for (int i = 0; i < UniformBlocks.count(); i++)
		{
			GlUniformBlock* block = UniformBlocks[i];
			printf("  %d ). ", i + 1);
			if (block != 0)
			{
				printf("%s : %d\n", (const char*)block->name(), block->handle());
			}
			else
			{
				printf("Not found\n");
			}
		}
	}

	FBOXAPI UNIFORM_FLAG GetUniformFlag(String name)
	{
		if (name == "os_to_ws") return UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD;
		else if (name == "ws_to_cs") return UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA;
		else if (name == "ws_to_ls") return UNIFORM_FLAG_MATRIX_WORLD_TO_LIGHT;
		else if (name == "projection") return UNIFORM_FLAG_MATRIX_PROJECTION;
		else if (name == "directionalLight_forward_ws") return UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR;
		else if (name == "directionalLight_color") return UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR;
		else if (name == "directionalLight_intensity") return UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY;
		//else if (name == "spotLight_pos_ws") return UNIFORM_FLAG_LIGHT_SPOT_POSITION;
		//else if (name == "spotLight_forward_ws") return UNIFORM_FLAG_LIGHT_SPOT_VECTOR;
		//else if (name == "spotLight_color") return UNIFORM_FLAG_LIGHT_SPOT_COLOR;
		//else if (name == "spotLight_intensity") return UNIFORM_FLAG_LIGHT_SPOT_INTENSITY;
		//else if (name == "spotLight_range") return UNIFORM_FLAG_LIGHT_SPOT_RANGE;
		//else if (name == "pointLight_pos_ws") return UNIFORM_FLAG_LIGHT_POINT_POSITION;
		//else if (name == "pointLight_color") return UNIFORM_FLAG_LIGHT_POINT_COLOR;
		//else if (name == "pointLight_intensity") return UNIFORM_FLAG_LIGHT_POINT_INTENSITY;
		//else if (name == "pointLight_range") return UNIFORM_FLAG_LIGHT_POINT_RANGE;
		else if (name == "overlay") return UNIFORM_FLAG_COLOR_OVERLAY;
		else if (name == "highlight") return UNIFORM_FLAG_COLOR_HIGHLIGHT;
		else if (name == "roughness") return UNIFORM_FLAG_BRDF_ROUGHNESS;
		else if (name == "refractionIndex") return UNIFORM_FLAG_BRDF_REFRACTION_INDEX;
		else if (name == "uvRepeat") return UNIFORM_FLAG_UV_REPEAT;
		else if (name == "uvOffset") return UNIFORM_FLAG_UV_OFFSET;
		else if (name == "screenSize") return UNIFORM_FLAG_SIZE_SCREEN;
		else if (name == "mapSize") return UNIFORM_FLAG_SIZE_MAP;
		else if (name == "randomFilter") return UNIFORM_FLAG_RANDOM_FILTER;
		else if (name == "gamma") return UNIFORM_FLAG_GAMMA;
		else if (name == "colorMap") return UNIFORM_FLAG_COLOR_MAP;
		else if (name == "normalMap") return UNIFORM_FLAG_NORMAL_MAP;
		else if (name == "specularMap") return UNIFORM_FLAG_SPECULAR_MAP;
		else if (name == "state") return UNIFORM_FLAG_STATE;
		else return UNIFORM_FLAG_INVALID;
	}
	FBOXAPI UNIFORM_BLOCK GetUniformBlockFlag(String name)
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

	FBOXAPI GlUniform* GetUniform(UNIFORM_FLAG flag)
	{
		if (flag != UNIFORM_FLAG_INVALID)
		{
			return Uniforms[(int)flag - 1];
		}

		return 0;
	}
	FBOXAPI GlUniformBlock* GetUniformBlock(UNIFORM_BLOCK block)
	{
		if (block != UNIFORM_BLOCK_INVALID)
		{
			return UniformBlocks[(int)block - 1];
		}

		return 0;
	}

}