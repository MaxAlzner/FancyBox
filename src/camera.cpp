
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Camera::bind()
	{
		vec3 eye = this->object->transform->position;
		vec3 focus = eye + (this->object->transform->forward);
		mat4 view = look(eye, focus, this->object->transform->up);
		mat4 proj = perspective(this->fov, this->aperture.x / this->aperture.y, this->clipping.x, this->clipping.y);
		GetUniform(UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA)->bind4x4f(view);
		GetUniform(UNIFORM_FLAG_MATRIX_PROJECTION)->bind4x4f(proj);
	}

	FBOXAPI void Camera::adjust(float width, float height)
	{

	}
	FBOXAPI void Camera::adjust()
	{

	}

}