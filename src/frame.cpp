
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	static clock_t _Ping = 0;
	static clock_t _LastFrameTicks = 0;
	static clock_t _LastSecond = 0;

	static FrameValue _Frame = 0;
	static FrameValue _Frames = 0;
	static FrameValue _Rate = 0;

	static FrameValue _FramesPerSecond = 60;
	static clock_t _TicksPerSecond = CLOCKS_PER_SEC;
	static clock_t _TicksPerFrame = _TicksPerSecond / 60;

	FBOXAPI FrameValue Frame::Count()
	{
		return _Frames;
	}
	FBOXAPI FrameValue Frame::Current()
	{
		return _Frame;
	}
	FBOXAPI FrameValue FrameRate()
	{
		return _Rate;
	}

	FBOXAPI TimeValue FixedTime()
	{
		return float(_Ping) / float(_TicksPerSecond);
	}
	FBOXAPI TimeValue DeltaTime()
	{
		return float(_LastFrameTicks) / float(_TicksPerSecond);
	}

	FBOXAPI void Frame::SetFramesPerSecond(FrameValue fps)
	{
		_FramesPerSecond = fps;
		_TicksPerSecond = CLOCKS_PER_SEC;
		_TicksPerFrame = _TicksPerSecond / clock_t(fps);
	}

	FBOXAPI void Frame::Start()
	{
		clock_t NewPing = clock();

		clock_t ThisSecond = NewPing / _TicksPerSecond;

		_Frame++;
		if (_LastSecond != ThisSecond)
		{
			_Rate = _Frame;
			_Frame = 0;
			_LastSecond = ThisSecond;
		}

		_Ping = NewPing;
	}
	FBOXAPI void Frame::Finish()
	{
		clock_t NewPing = clock();
		_LastFrameTicks = NewPing > _Ping ? NewPing - _Ping : 0;

		_Frames++;
	}

}