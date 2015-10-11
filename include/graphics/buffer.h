#ifndef FBOX_GLBUFFER_H
#define FBOX_GLBUFFER_H

namespace fbox
{
	namespace gl
	{

		class FBOXAPI Buffer
		{
		public:

			typedef GLuint handleType;

			enum targetType
			{
				TARGET_NONE = 0,
				TARGET_ARRAY = 1,
				TARGET_ELEMENT_ARRAY = 2,
				TARGET_TEXTURE = 3,
				TARGET_UNIFORM = 4
			};

			enum usageType
			{
				USAGE_NONE = 0,
				USAGE_STATIC_DRAW = 1,
				USAGE_DYNAMIC_DRAW = 2
			};

			Buffer() : _handle(0), _target(TARGET_NONE), _usage(USAGE_NONE) {}
			Buffer(targetType target, usageType usage) : _handle(0), _target(target), _usage(usage) {}
			~Buffer() {}

			void create();
			void release();

			void bind();
			void unbind();

			void map(const void* data, unsigned int bytes);

			const handleType handle() const;
			const targetType target() const;
			const usageType usage() const;

		protected:

			handleType _handle;
			targetType _target;
			usageType _usage;

		};

	}
}

#endif