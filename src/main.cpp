
#include "../include/FancyBox.h"

void OnMouseMove(GLFWwindow* window, double x, double y)
{
	fbox::Input.Mouse.position.x = (float)x;
	fbox::Input.Mouse.position.y = (float)y;
}

void OnMouseEnter(GLFWwindow* window, int entered)
{
	fbox::Input.Mouse.active = entered == GL_TRUE;
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		fbox::Input.Mouse.left = action == GLFW_PRESS ? true : false;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		fbox::Input.Mouse.middle = action == GLFW_PRESS ? true : false;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		fbox::Input.Mouse.right = action == GLFW_PRESS ? true : false;
		break;
	default:
		break;
	}
}

void OnMouseScroll(GLFWwindow* window, double offsetx, double offsety)
{
	fbox::Input.Mouse.scroll = offsety;
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	fbox::Input.Key[key] = action == GLFW_PRESS ? true : false;
}

void OnFileDrop(GLFWwindow* window, int count, const char** paths)
{
	for (int i = 0; i < count; i++)
	{
		String path = paths[i];
		printf(" Dropped file: %s\n", (char*)path);
		fbox::Import::Read(path);
	}
}

void cleanup()
{
	fbox::OnEnd();
	fbox::OnUnload();
	glfwTerminate();
}

int main(int argv, char** argc)
{
	atexit(cleanup);
	fbox::OnLoad();
	if (!glfwInit())
	{
		exit(1);
	}

	GLFWwindow* window = glfwCreateWindow(480, 320, "FancyBox", 0, 0);
	glfwSetCursorPosCallback(window, OnMouseMove);
	glfwSetCursorEnterCallback(window, OnMouseEnter);
	glfwSetMouseButtonCallback(window, OnMouseButton);
	glfwSetScrollCallback(window, OnMouseScroll);
	glfwSetKeyCallback(window, OnKey);
	glfwSetDropCallback(window, OnFileDrop);
	if (!window)
	{
		exit(1);
	}

	glfwMakeContextCurrent(window);
	fbox::OnStart();
	OnFileDrop(window, argv - 1, (const char**)argc + 1);

	fbox::ScriptManager::Register("testbehavior.js");
	fbox::ScriptObject global = fbox::ScriptManager::Global();
	fbox::ScriptArray globals = global.properties();
	for (int i = 0; i < globals.count(); i++)
	{
		printf(" %d ). %s : %s\n", i + 1, (const char*)(globals.gets(i)), (const char*)(global.typeof(globals.gets(i))));
		fbox::ScriptObject property = global.get(globals.gets(i));
		fbox::ScriptArray props = property.properties();
		for (int k = 0; k < props.count(); k++)
		{
			printf("   %d ). %s : %s\n", k + 1, (const char*)(props.gets(k)), (const char*)(property.typeof(props.gets(k))));
		}
	}

	fbox::ScriptObject test0 = fbox::ScriptManager::Global().construct("TestBehavior");
	fbox::ScriptArray test0props = test0.properties();
	for (int i = 0; i < test0props.count(); i++)
	{
		printf(" %d ). %s : %s\n", i + 1, (const char*)(test0props.gets(i)), (const char*)(test0.typeof(test0props.gets(i))));
	}

	test0.call("OnStart");
	test0.call("OnUpdate");
	test0.call("OnUpdate");
	test0.call("OnUpdate");
	test0.call("OnEnd");

	while (!glfwWindowShouldClose(window))
	{
		fbox::Frame::Start();
		glfwPollEvents();
		fbox::OnUpdate();
		fbox::OnDraw();
		glfwSwapBuffers(window);
		fbox::Frame::Finish();
	}

	return 0;
}