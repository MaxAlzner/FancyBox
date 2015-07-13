
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

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

}