
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Camera::bind()
	{
		vec3 eye = this->object->transform->position;
		vec3 focus = eye + (this->object->transform->forward);
		mat4 view = look(eye, focus, this->object->transform->up);

	}

}