
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	using namespace glm;

	FBOXAPI void Transform::bind()
	{
		Renderer::GetUniform(UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD)->bind4x4f(this->transformation);
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
		//vec3 to = normalize(focus - this->position);
	}

	FBOXAPI void MeshFilter::bind()
	{

	}

	FBOXAPI void TextureFilter::bind()
	{
		switch (this->type)
		{
		case TEXTURE_COLOR:
			Renderer::GetUniform(UNIFORM_FLAG_MAP_COLOR)->texture(this->texture, 0);
			break;
		case TEXTURE_NORMAL:
			Renderer::GetUniform(UNIFORM_FLAG_MAP_NORMAL)->texture(this->texture, 1);
			break;
		case TEXTURE_SPECULAR:
			Renderer::GetUniform(UNIFORM_FLAG_MAP_SPECULAR)->texture(this->texture, 2);
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

		this->state.accessor("name", "string", &this->name, sizeof(std::string), false);
		js::Object transform;
		transform.accessor("position", &this->object->transform->position, true);
		transform.accessor("rotation", &this->object->transform->rotation, true);
		transform.accessor("scale", &this->object->transform->scale, true);
		transform.accessor("forward", &this->object->transform->forward, false);
		transform.accessor("up", &this->object->transform->up, false);
		transform.accessor("right", &this->object->transform->right, false);
		this->state.set("transform", transform);
		if (this->object->material != 0)
		{
			js::Object material;
			this->state.set("material", material);
		}

		if (this->object->camera != 0)
		{
			js::Object camera;
			camera.accessor("aperture", &this->object->camera->aperture, true);
			camera.accessor("clipping", &this->object->camera->clipping, true);
			camera.accessor("fov", "number", &this->object->camera->fov, sizeof(float));
			this->state.set("camera", camera);
		}

		if (this->object->light != 0)
		{
			js::Object light;
			light.accessor("color", &this->object->light->color, true);
			light.accessor("intensity", "number", &this->object->light->intensity, sizeof(float));
			light.accessor("range", "number", &this->object->light->range, sizeof(float));
			light.accessor("angle", "number", &this->object->light->angle, sizeof(float));
			this->state.set("light", light);
		}

		this->state.call("OnStart");
	}
	FBOXAPI void Behavior::end()
	{
		this->state.call("OnEnd");
	}
	FBOXAPI void Behavior::update()
	{
		this->state.call("OnUpdate");
	}

	FBOXAPI void Camera::bind()
	{
		vec3 eye = this->object->transform->position;
		vec3 focus = eye + (this->object->transform->forward);
		vec3 up = this->object->transform->up;
		mat4 view = lookAt(eye, focus, up);
		mat4 proj = perspective(this->fov, this->aperture.x / this->aperture.y, this->clipping.x, this->clipping.y);
		Renderer::GetUniform(UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA)->bind4x4f(view);
		Renderer::GetUniform(UNIFORM_FLAG_MATRIX_PROJECTION)->bind4x4f(proj);
		Renderer::MainCamera = this;
	}

	FBOXAPI void Camera::adjust(float width, float height)
	{
		width /= 2.0f;
		height /= 2.0f;
		this->viewport.p1 = (this->object->transform->right * -width) + (this->object->transform->up * height) + this->object->transform->position;
		this->viewport.p2 = (this->object->transform->right * width) + (this->object->transform->up * height) + this->object->transform->position;
		this->viewport.p3 = (this->object->transform->right * width) + (this->object->transform->up * -height) + this->object->transform->position;
		this->viewport.p4 = (this->object->transform->right * -width) + (this->object->transform->up * -height) + this->object->transform->position;
		this->viewport.px = normalize(this->viewport.p2 - this->viewport.p1);
		this->viewport.py = normalize(this->viewport.p4 - this->viewport.p1);
		this->viewport.focal = this->object->transform->position + -this->object->transform->forward;
	}

	FBOXAPI void Light::bind()
	{
		if (this->lightType == LIGHT_DIRECTIONAL)
		{
			Renderer::GetUniform(UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR)->bind3f(this->object->transform->forward);
			Renderer::GetUniform(UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR)->bind4f(this->color);
			Renderer::GetUniform(UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY)->bind1f(this->intensity);
		}
		else if (this->lightType == LIGHT_POINT)
		{
			struct
			{
				vec4 position;
				vec4 color;
				float intensity;
				float range;
			} lightData;
			lightData.position = vec4(this->object->transform->position, 1.0);
			lightData.color = this->color;
			lightData.intensity = this->intensity;
			lightData.range = this->range;
			Renderer::GetUniformBlock(UNIFORM_BLOCK_LIGHT_POINT1)->bind(0, &lightData, sizeof(lightData));
			Renderer::GetUniform(UNIFORM_FLAG_LIGHT_POINT_NUM)->bind1i(1);
		}
		else if (this->lightType == LIGHT_SPOT)
		{
			struct
			{
				vec4 position;
				vec3 forward;
				float angle;
				vec4 color;
				float intensity;
				float range;
			} lightData;
			lightData.position = vec4(this->object->transform->position, 1.0);
			lightData.forward = this->object->transform->forward;
			lightData.angle = this->angle;
			lightData.color = this->color;
			lightData.intensity = this->intensity;
			lightData.range = this->range;
			Renderer::GetUniformBlock(UNIFORM_BLOCK_LIGHT_SPOT1)->bind(4, &lightData, sizeof(lightData));
			Renderer::GetUniform(UNIFORM_FLAG_LIGHT_SPOT_NUM)->bind1i(1);
		}
	}

}