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

#define GLM_FORCE_RADIANS

#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>

#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <list>
#include <map>

#include <rapidxml.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <shape.h>

#include <GL/glew.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <v8.h>
#include <FreeImage.h>

#if defined(_WIN32)
#define _stdcall _stdcall
#else
#define _stdcall __attribute__((stdcall))
#endif

typedef FIBITMAP surface;
#if !defined(uint)
typedef unsigned int uint;
#endif

inline std::string _stdcall trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first) + 1);
}

#endif