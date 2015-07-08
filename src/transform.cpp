
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Transform::bind()
	{

	}

	FBOXAPI inline void Transform::recalculate()
	{
		this->space = mat4(1.0f);
		this->space *= rotateX(this->rotation.x);
		this->space *= rotateY(this->rotation.y);
		this->space *= rotateZ(this->rotation.z);

		this->transformation = mat4(1.0f);
		this->transformation *= translate(this->position);
		this->transformation *= rotateX(this->rotation.x);
		this->transformation *= rotateY(this->rotation.y);
		this->transformation *= rotateZ(this->rotation.z);
		this->transformation *= this->space;
		this->transformation *= gmath::scale(this->scale);

		mat3 spaceNormal = mat3(this->space);
		this->right = normalize(vec3(1.0f, 0.0f, 0.0f) * spaceNormal);
		this->up = normalize(vec3(0.0f, 1.0f, 0.0f) * spaceNormal);
		this->forward = normalize(vec3(0.0f, 0.0f, 1.0f) * spaceNormal);
	}
	FBOXAPI inline void Transform::zero()
	{
		this->transformation = mat4(1.0f);
		this->space = mat4(1.0f);
		this->position = vec3(0.0f);
		this->rotation = vec3(0.0f);
		this->scale = vec3(1.0f);
		this->right = vec3(1.0f, 0.0f, 0.0f);
		this->up = vec3(0.0f, 1.0f, 0.0f);
		this->forward = vec3(0.0f, 0.0f, 1.0f);
	}

	FBOXAPI inline void Transform::look(const vec3& focus)
	{
		vec3 to = normalize(focus - this->position);
	}

}