#ifndef FBOX_SETUP_H
#define FBOX_SETUP_H

#if 0//defined(_WIN32)

#if defined(FBOX_EXPORT)
#define FBOXAPI __declspec(dllexport)
#else
#define FBOXAPI __declspec(dllimport)
#endif

#else

#define FBOXAPI

#endif

#define _USE_MATH_DEFINES

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
#include <map>

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

#endif