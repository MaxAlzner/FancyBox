
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace js
	{

		FBOXAPI void FunctionParameters::add(const std::string& value)
		{
			this->_parameters.push_back(v8::String::New(value.data()));
		}
		FBOXAPI void FunctionParameters::add(int32_t value)
		{
			this->_parameters.push_back(v8::Int32::New(value));
		}
		FBOXAPI void FunctionParameters::add(bool value)
		{
			this->_parameters.push_back(v8::Boolean::New(value));
		}
		FBOXAPI void FunctionParameters::add(float value)
		{
			this->_parameters.push_back(v8::Number::New((double)value));
		}
		FBOXAPI void FunctionParameters::add(double value)
		{
			this->_parameters.push_back(v8::Number::New(value));
		}
		FBOXAPI void FunctionParameters::add(const Object& value)
		{
			this->_parameters.push_back((v8::Handle<v8::Value>)value);
		}
		FBOXAPI void FunctionParameters::add(const Array& value)
		{
			this->_parameters.push_back((v8::Handle<v8::Value>)value);
		}

		FBOXAPI const int FunctionParameters::count() const
		{
			return this->_parameters.size();
		}

		FBOXAPI FunctionParameters::operator v8::Handle<v8::Value>*() const
		{
			return (v8::Handle<v8::Value>*)this->_parameters.data();
		}
		FBOXAPI void FunctionParameters::operator+=(const std::string& value)
		{
			this->add(value);
		}
		FBOXAPI void FunctionParameters::operator+=(int32_t value)
		{
			this->add(value);
		}
		FBOXAPI void FunctionParameters::operator+=(bool value)
		{
			this->add(value);
		}
		FBOXAPI void FunctionParameters::operator+=(float value)
		{
			this->add(value);
		}
		FBOXAPI void FunctionParameters::operator+=(double value)
		{
			this->add(value);
		}
		FBOXAPI void FunctionParameters::operator+=(const Object& value)
		{
			this->add(value);
		}
		FBOXAPI void FunctionParameters::operator+=(const Array& value)
		{
			this->add(value);
		}

	}
}