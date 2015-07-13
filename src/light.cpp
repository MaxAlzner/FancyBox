
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

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