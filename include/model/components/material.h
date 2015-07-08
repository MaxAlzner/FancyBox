#ifndef FBOX_MATERIAL_H
#define FBOX_MATERIAL_H

namespace fbox
{

	class FBOXAPI Material : public Component
	{
	public:

		inline Material() : Component("Material") {}
		inline ~Material() {}

		inline void bind();

	};

}

#endif