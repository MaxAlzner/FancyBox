#pragma once

#if 0//defined(_WIN32)

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
	namespace gl
	{
		class FBOXAPI Uniform;
		class FBOXAPI Texture;
		class FBOXAPI Buffer;
		class FBOXAPI UniformBlock;
		class FBOXAPI VertexArray;
		class FBOXAPI Framebuffer;
		class FBOXAPI Shader;
		class FBOXAPI Program;
	}

	namespace al
	{
		class FBOXAPI Buffer;
	}

	namespace js
	{
		class FBOXAPI Object;
		class FBOXAPI Array;
		class FBOXAPI FunctionParameters;
		class FBOXAPI Manager;
	}

	class FBOXAPI Component;
	class FBOXAPI Transform;
	class FBOXAPI MeshFilter;
	class FBOXAPI TextureFilter;
	class FBOXAPI Material;
	class FBOXAPI Behavior;
	class FBOXAPI Camera;
	class FBOXAPI Light;

	class FBOXAPI Actor;
	class FBOXAPI Scene;
}

#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>

#include <string>
#include <vector>
#include <list>

#include <rapidxml.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <shape.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <v8.h>
#include <FreeImage.h>

typedef std::string string;
typedef FIBITMAP surface;
typedef unsigned int uint;

#include "input/button.h"
#include "input/axis.h"
#include "input/mouse.h"
#include "input/key.h"
#include "input/gamepad.h"

#include "graphics/uniform.h"
#include "graphics/texture.h"
#include "graphics/buffer.h"
#include "graphics/uniformblock.h"
#include "graphics/vertexarray.h"
#include "graphics/framebuffer.h"
#include "graphics/shader.h"
#include "graphics/program.h"

#include "audio/buffer.h"

#include "scripting/manager.h"
#include "scripting/object.h"
#include "scripting/array.h"
#include "scripting/functionparameters.h"

#include "model/component.h"
#include "model/actor.h"
#include "model/scene.h"

#include "system/global.h"
#include "system/frame.h"
#include "system/callback.h"