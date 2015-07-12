#ifndef FBOX_LIGHT_H
#define FBOX_LIGHT_H

namespace fbox
{

	class FBOXAPI Light : public Component
	{
	public:

		enum LIGHTTYPE
		{
			NONE,
			DIRECTIONAL,
			POINT,
			SPOT,
		};

		inline Light() :
			Component("Light"),
			lightType(NONE),
			intensity(1.0f) {}
		inline Light(LIGHTTYPE lightType, const float intensity) :
			Component("Light"),
			lightType(lightType),
			intensity(intensity) {}
		inline ~Light() {}

		void bind();

		LIGHTTYPE lightType;
		float intensity;

	protected:

	};

}

#endif