#ifndef FBOX_FRAME_H
#define FBOX_FRAME_H

namespace fbox
{

	typedef __int64 FrameValue;
	typedef float TimeValue;

	class FBOXAPI Frame
	{
	public:
		
		static FrameValue Count();
		static FrameValue Current();
		static FrameValue Rate();

		static TimeValue FixedTime();
		static TimeValue DeltaTime();

		static void SetFramesPerSecond(FrameValue fps);

		static void Start();
		static void Finish();

	};

}

#endif