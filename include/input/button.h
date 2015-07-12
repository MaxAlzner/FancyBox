#ifndef FBOX_BUTTON_H
#define FBOX_BUTTON_H

namespace fbox
{

	typedef struct Button
	{

		inline Button() : _latched(false), _pressed(false) {}
		inline ~Button() {}

		inline void latch()
		{
			this->_latched = true;
		}
		inline void unlatch()
		{
			this->_latched = false;
		}

		inline void operator=(const bool value)
		{
			this->_pressed = value;
		}
		inline void operator=(const Button& button)
		{
			this->_pressed = button._pressed;
			this->_latched = button._latched;
		}
		inline operator bool() const
		{
			if (this->_latched)
			{
				return false;
			}

			return this->_pressed;
		}

		bool _pressed;
		bool _latched;

	} Button;

}

#endif