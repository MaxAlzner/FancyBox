#ifndef FBOX_LIGHT_H
#define FBOX_LIGHT_H

namespace fbox
{

	class FBOXAPI Light : public Component
	{
	public:

		enum LIGHTTYPE
		{
			LIGHT_NONE,
			LIGHT_DIRECTIONAL,
			LIGHT_POINT,
			LIGHT_SPOT,
		};

		inline Light() :
			Component("Light"),
			lightType(LIGHT_NONE),
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