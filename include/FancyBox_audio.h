#ifndef FBOX_AUDIO_H
#define FBOX_AUDIO_H

#include "FancyBox_setup.h"

namespace fbox
{
	namespace al
	{
		class FBOXAPI Buffer;

		class FBOXAPI Buffer
		{
		public:

			typedef ALuint handleType;
			typedef ALenum formatType;

			Buffer() : _handle(0), _format(0) {}
			~Buffer() {}

			void create();
			void release();

			//void map(const Sound::Track* track);

			const handleType handle() const { return this->_handle; }
			const formatType format() const { return this->_format; }

		protected:

			handleType _handle;
			formatType _format;

		};

	}
}

#endif