#pragma once

#if defined(_WIN32)

#if defined(FBOX_EXPORT)
#define FBOXAPI __declspec(dllexport)
#else
#define FBOXAPI __declspec(dllimport)
#endif

#else

#define FBOXAPI

#endif

namespace fbox
{
	class FBOXAPI GlUniform;
	class FBOXAPI GlTexture;
	class FBOXAPI GlBuffer;
	class FBOXAPI GlUniformBlock;
	class FBOXAPI GlVertexArray;
	class FBOXAPI GlFramebuffer;
	class FBOXAPI GlShader;
	class FBOXAPI GlProgram;

	class FBOXAPI ScriptEntity;
	class FBOXAPI ScriptObject;
	class FBOXAPI ScriptArray;
	class FBOXAPI ScriptParameters;
	class FBOXAPI ScriptFile;
	class FBOXAPI ScriptManager;

	class FBOXAPI Component;
	class FBOXAPI Transform;
	class FBOXAPI MeshFilter;
	class FBOXAPI TextureFilter;
	class FBOXAPI Material;
	class FBOXAPI Camera;
	class FBOXAPI Light;

	class FBOXAPI Actor;
}

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>

#include <MediaLoader.h>
//#include <vec2.hpp>
//#include <vec3.hpp>
//#include <vec4.hpp>
//#include <geometric.hpp>
//#include <mat3x3.hpp>
//#include <mat4x4.hpp>
//#include <ext.hpp>

#include <array.hpp>
#include <list.hpp>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <v8.h>

//using namespace glm;
using namespace medialoader;

#include "input\button.h"
#include "input\axis.h"
#include "input\mouse.h"
#include "input\key.h"
#include "input\gamepad.h"

#include "graphics\gluniform.h"
#include "graphics\gltexture.h"
#include "graphics\glbuffer.h"
#include "graphics\gluniformblock.h"
#include "graphics\glvertexarray.h"
#include "graphics\glframebuffer.h"
#include "graphics\glshader.h"
#include "graphics\glprogram.h"

#include "scripting\scriptentity.h"
#include "scripting\scriptobject.h"
#include "scripting\scriptarray.h"
#include "scripting\scriptparameters.h"
#include "scripting\scriptfile.h"
#include "scripting\scriptmanager.h"

#include "model\components\component.h"
#include "model\components\transform.h"
#include "model\components\meshfilter.h"
#include "model\components\texturefilter.h"
#include "model\components\material.h"
#include "model\components\camera.h"
#include "model\components\light.h"

#include "model\actor.h"

#include "system\global.h"
#include "system\callback.h"
#include "system\graphics.h"