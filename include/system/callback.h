#ifndef FBOX_CALLBACK_H
#define FBOX_CALLBACK_H

namespace fbox
{

	extern void OnLoad();
	extern void OnUnload();
	extern void OnStart();
	extern void OnEnd();

	extern void OnReshape(int width, int height);
	extern void OnUpdate();
	extern void OnDraw();

}

#endif