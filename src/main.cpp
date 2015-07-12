
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
	if (glewInit() != GLEW_OK)
	{
		exit(1);
	}

	if (!GLEW_VERSION_3_0)
	{
		exit(1);
	}

	fbox::OnStart();
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