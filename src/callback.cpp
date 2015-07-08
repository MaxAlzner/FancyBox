
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	
	void OnLoad()
	{

	}
	void OnUnload()
	{

	}
	void OnStart()
	{

	}
	void OnEnd()
	{

	}

	void OnReshape(int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	void OnUpdate()
	{

	}
	void OnDraw()
	{
		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}