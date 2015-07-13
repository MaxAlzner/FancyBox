#ifndef FBOX_GRAPHICS_H
#define FBOX_GRAPHICS_H

namespace fbox
{

	typedef enum UNIFORM_FLAG
	{

		UNIFORM_FLAG_INVALID,

		UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD,
		UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA,
		UNIFORM_FLAG_MATRIX_WORLD_TO_LIGHT,
		UNIFORM_FLAG_MATRIX_PROJECTION,

		UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR,
		UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR,
		UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY,
		//UNIFORM_FLAG_LIGHT_SPOT_POSITION,
		//UNIFORM_FLAG_LIGHT_SPOT_VECTOR,
		//UNIFORM_FLAG_LIGHT_SPOT_COLOR,
		//UNIFORM_FLAG_LIGHT_SPOT_INTENSITY,
		//UNIFORM_FLAG_LIGHT_SPOT_RANGE,
		//UNIFORM_FLAG_LIGHT_POINT_POSITION,
		//UNIFORM_FLAG_LIGHT_POINT_COLOR,
		//UNIFORM_FLAG_LIGHT_POINT_INTENSITY,
		//UNIFORM_FLAG_LIGHT_POINT_RANGE,

		UNIFORM_FLAG_COLOR_OVERLAY,
		UNIFORM_FLAG_COLOR_HIGHLIGHT,
		UNIFORM_FLAG_BRDF_ROUGHNESS,
		UNIFORM_FLAG_BRDF_REFRACTION_INDEX,
		UNIFORM_FLAG_UV_REPEAT,
		UNIFORM_FLAG_UV_OFFSET,

		UNIFORM_FLAG_SIZE_SCREEN,
		UNIFORM_FLAG_SIZE_MAP,
		UNIFORM_FLAG_FILTER_RANDOM,
		UNIFORM_FLAG_GAMMA,

		UNIFORM_FLAG_MAP_COLOR,
		UNIFORM_FLAG_MAP_NORMAL,
		UNIFORM_FLAG_MAP_SPECULAR,

		UNIFORM_FLAG_STATE,

	} UNIFORM_FLAG;

	typedef enum UNIFORM_BLOCK
	{

		UNIFORM_BLOCK_INVALID,

		UNIFORM_BLOCK_LIGHT_POINT1,
		UNIFORM_BLOCK_LIGHT_POINT2,
		UNIFORM_BLOCK_LIGHT_POINT3,
		UNIFORM_BLOCK_LIGHT_POINT4,
		UNIFORM_BLOCK_LIGHT_SPOT1,
		UNIFORM_BLOCK_LIGHT_SPOT2,
		UNIFORM_BLOCK_LIGHT_SPOT3,
		UNIFORM_BLOCK_LIGHT_SPOT4,

	} UNIFORM_BLOCK;

	typedef enum UNIFORM_MODE
	{

		UNIFORM_MODE_NONE,
		UNIFORM_MODE_NORMAL,
		UNIFORM_MODE_SHADOW_MAP,
		UNIFORM_MODE_PREVIOUS,

	} UNIFORM_MODE;

	FBOXAPI extern void GrabUniforms();

	FBOXAPI extern UNIFORM_FLAG GetUniformFlag(String name);
	FBOXAPI extern UNIFORM_BLOCK GetUniformBlockFlag(String name);

	FBOXAPI extern GlUniform* GetUniform(UNIFORM_FLAG flag);
	FBOXAPI extern GlUniformBlock* GetUniformBlock(UNIFORM_BLOCK block);

}

#endif