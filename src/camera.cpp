
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI inline void Camera::bind()
	{
		vec3 eye = this->object->transform->position;
		vec3 focus = eye + (this->object->transform->forward);
		mat4 view = look(eye, focus, this->object->transform->up);

	}

	FBOXAPI void Camera::adjust(float width, float height)
	{

	}
	FBOXAPI void Camera::adjust()
	{

	}

}