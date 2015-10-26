
#include "../include/FancyBox.h"

void OnMouseMove(GLFWwindow* window, double x, double y)
{
	fbox::Input::Mouse.position.x = (float)x;
	fbox::Input::Mouse.position.y = (float)y;
}

void OnMouseEnter(GLFWwindow* window, int entered)
{
	fbox::Input::Mouse.active = entered == GL_TRUE;
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		fbox::Input::Mouse.left = action == GLFW_PRESS ? true : false;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		fbox::Input::Mouse.middle = action == GLFW_PRESS ? true : false;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		fbox::Input::Mouse.right = action == GLFW_PRESS ? true : false;
		break;
	default:
		break;
	}
}

void OnMouseScroll(GLFWwindow* window, double offsetx, double offsety)
{
	fbox::Input::Mouse.scroll = offsety;
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	fbox::Input::Key[key] = action == GLFW_PRESS ? true : false;
}

void OnFileDrop(GLFWwindow* window, int count, const char** paths)
{
	for (int i = 0; i < count; i++)
	{
		string path = paths[i];
		printf(" Dropped file: %s\n", path.data());
		fbox::Import::Model(path);
		fbox::Stage::Build();
	}
}

void cleanup()
{
	fbox::Event::OnUnload();
	fbox::Event::OnDispose();
	glfwTerminate();
}

int main(int argv, char** argc)
{
	fbox::Event::OnPreInitialize();
	srand(time(0));
	atexit(cleanup);
	if (!glfwInit())
	{
		exit(1);
	}

	GLFWwindow* window = glfwCreateWindow(fbox::Renderer::Screen.x, fbox::Renderer::Screen.y, "FancyBox", 0, 0);
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
	fbox::Event::OnInitialize();
	fbox::Event::OnLoad();
	fbox::Event::OnStart();
	while (!glfwWindowShouldClose(window))
	{
		fbox::Frame::Start();
		glfwPollEvents();
		fbox::Event::OnUpdate();
		fbox::Event::OnDraw();
		glfwSwapBuffers(window);
		fbox::Frame::Finish();
	}

	return 0;
}