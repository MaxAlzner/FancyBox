#ifndef FBOX_ALBUFFER_H
#define FBOX_ALBUFFER_H

namespace fbox
{

	class FBOXAPI AlBuffer
	{
	public:

		typedef ALuint handleType;
		typedef ALenum formatType;

		AlBuffer() : _handle(0), _format(0) {}
		~AlBuffer() {}

		void create();
		void release();

		void map(const Sound::Track* track);

		const handleType handle() const { return this->_handle; }
		const formatType format() const { return this->_format; }

	protected:

		handleType _handle;
		formatType _format;

	};

}

#endif