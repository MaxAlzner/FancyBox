#ifndef FBOX_CALLBACK_H
#define FBOX_CALLBACK_H

namespace fbox
{

	FBOXAPI extern void OnLoad();
	FBOXAPI extern void OnUnload();
	FBOXAPI extern void OnStart();
	FBOXAPI extern void OnEnd();

	FBOXAPI extern void OnReshape(int width, int height);
	FBOXAPI extern void OnUpdate();
	FBOXAPI extern void OnDraw();

}

#endif