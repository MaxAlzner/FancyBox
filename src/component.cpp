
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	using namespace glm;

	FBOXAPI void Transform::bind()
	{
		GetUniform(UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD)->bind4x4f(this->transformation);
	}

	FBOXAPI void Transform::recalculate()
	{
		this->space = mat4(1.0f);
		this->space *= rotate(glm::radians(this->rotation.x), vec3(1.0f, 0.0f, 0.0f));
		this->space *= rotate(glm::radians(this->rotation.y), vec3(0.0f, 1.0f, 0.0f));
		this->space *= rotate(glm::radians(this->rotation.z), vec3(0.0f, 0.0f, 1.0f));

		this->transformation = mat4(1.0f);
		this->transformation *= translate(this->position);
		this->transformation *= this->space;
		this->transformation *= glm::scale(this->scale);

		mat3 spaceNormal = mat3(this->space);
		this->right = normalize(spaceNormal * vec3(1.0f, 0.0f, 0.0f));
		this->up = normalize(spaceNormal * vec3(0.0f, 1.0f, 0.0f));
		this->forward = normalize(spaceNormal * vec3(0.0f, 0.0f, 1.0f));
	}
	FBOXAPI void Transform::zero()
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

	FBOXAPI void Transform::look(const vec3& focus)
	{
		vec3 to = normalize(focus - this->position);
	}

	FBOXAPI void MeshFilter::bind()
	{

	}

	FBOXAPI void TextureFilter::bind()
	{
		switch (this->type)
		{
		case TEXTURE_COLOR:
			GetUniform(UNIFORM_FLAG_MAP_COLOR)->texture(this->texture, 0);
			break;
		case TEXTURE_NORMAL:
			GetUniform(UNIFORM_FLAG_MAP_NORMAL)->texture(this->texture, 1);
			break;
		case TEXTURE_SPECULAR:
			GetUniform(UNIFORM_FLAG_MAP_SPECULAR)->texture(this->texture, 2);
			break;
		case TEXTURE_TRANSPARENCY:
			break;
		case TEXTURE_REFLECT:
			break;
		case TEXTURE_EMISSIVE:
			break;
		case TEXTURE_DISPLACEMENT:
			break;
		default:
			break;
		}
	}

	FBOXAPI void Material::bind()
	{

	}

	FBOXAPI void Behavior::bind()
	{

	}

	FBOXAPI void Behavior::start()
	{
		if (!name.empty())
		{
			this->state = js::Manager::Global().construct(this->name);
		}

#if 0
		ScriptArray props = this->state.properties();
		for (ScriptArray::Iterator i = props.begin(); i < props.count(); i++)
		{
			printf(" %d ). %s : %s\n", i.index() + 1, (const char*)i.gets(), (const char*)this->state.typeof(i.gets()));
		}
#endif

		this->state.call((string)"OnStart");
	}
	FBOXAPI void Behavior::end()
	{
		this->state.call((string)"OnEnd");
	}
	FBOXAPI void Behavior::update()
	{
		//this->state.call("OnUpdate");
	}

	FBOXAPI void Camera::bind()
	{
		vec3 eye = this->object->transform->position;
		vec3 focus = eye + (this->object->transform->forward);
		mat4 view = lookAt(eye, focus, -this->object->transform->up);
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

	FBOXAPI void Light::bind()
	{
		switch (this->lightType)
		{
		case LIGHT_DIRECTIONAL:
			break;
		case LIGHT_POINT:
			break;
		case LIGHT_SPOT:
			break;
		}
	}

}