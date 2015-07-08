#ifndef FBOX_CAMERA_H
#define FBOX_CAMERA_H

namespace fbox
{

	class FBOXAPI Camera : public Component
	{
	public:

		inline Camera() :
			Component("Camera"),
			aperture(4.0f, 3.0f),
			fov(60.0f) {}
		inline Camera(const vec2& aperture, const float fov) :
			Component("Camera"),
			aperture(aperture),
			fov(fov) {}
		inline ~Camera() {}

		inline void bind();

		inline void adjust(float width, float height);
		inline void adjust();

		//inline ray getRay(float u, float v);
		//inline ray getRay(vec2& uv);

		vec2 aperture;
		float fov;

	protected:

		struct
		{

			vec3 p1;
			vec3 p2;
			vec3 p3;
			vec3 p4;
			vec3 px;
			vec3 py;
			vec3 focal;

		} viewport;

	};

}

#endif