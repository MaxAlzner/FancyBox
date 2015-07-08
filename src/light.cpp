
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void Light::bind()
	{
		switch (this->lightType)
		{
		case LIGHTTYPE::DIRECTIONAL:
			break;
		case LIGHTTYPE::POINT:
			break;
		case LIGHTTYPE::SPOT:
			break;
		}
	}

}