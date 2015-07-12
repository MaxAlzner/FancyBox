#ifndef FBOX_AXIS_H
#define FBOX_AXIS_H

namespace fbox
{

	typedef struct Axis
	{

		inline Axis()
		{
			this->_value = 0.0f;
			this->_deadzone = 0.4f;
		}
		inline ~Axis() {}

		inline void deadzone(const float value)
		{
			this->_deadzone = min(max(value, 0.0f), 1.0f);
		}

		inline void operator=(const float value)
		{
			this->_value = min(max(value, -1.0f), 1.0f);
		}
		inline void operator=(const Axis& axis)
		{
			this->_value = axis._value;
			this->_deadzone = axis._deadzone;
		}
		inline operator float() const
		{
			return this->_value;
		}
		inline operator bool() const
		{
			if (abs(this->_value) <= this->_deadzone)
			{
				return false;
			}

			return true;
		}

		float _value;
		float _deadzone;

	} Axis;

}

#endif