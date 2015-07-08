
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void ScriptParameters::add(String value)
	{
		this->_parameters.add(v8::String::New(value));
	}
	FBOXAPI void ScriptParameters::add(__int32 value)
	{
		this->_parameters.add(v8::Int32::New(value));
	}
	FBOXAPI void ScriptParameters::add(bool value)
	{
		this->_parameters.add(v8::Boolean::New(value));
	}
	FBOXAPI void ScriptParameters::add(float value)
	{
		this->_parameters.add(v8::Number::New((double)value));
	}
	FBOXAPI void ScriptParameters::add(double value)
	{
		this->_parameters.add(v8::Number::New(value));
	}
	FBOXAPI void ScriptParameters::add(ScriptObject& value)
	{
		this->_parameters.add((v8::Handle<v8::Value>)value);
	}
	FBOXAPI void ScriptParameters::add(ScriptArray& value)
	{
		this->_parameters.add((v8::Handle<v8::Value>)value);
	}

	FBOXAPI void ScriptParameters::set(const int index, String value)
	{
		this->_parameters.insert(v8::String::New(value), index);
	}
	FBOXAPI void ScriptParameters::set(const int index, __int32 value)
	{
		this->_parameters.insert(v8::Int32::New(value), index);
	}
	FBOXAPI void ScriptParameters::set(const int index, bool value)
	{
		this->_parameters.insert(v8::Boolean::New(value), index);
	}
	FBOXAPI void ScriptParameters::set(const int index, float value)
	{
		this->_parameters.insert(v8::Number::New((double)value), index);
	}
	FBOXAPI void ScriptParameters::set(const int index, double value)
	{
		this->_parameters.insert(v8::Number::New(value), index);
	}
	FBOXAPI void ScriptParameters::set(const int index, ScriptObject& value)
	{
		this->_parameters.insert((v8::Handle<v8::Value>)value, index);
	}
	FBOXAPI void ScriptParameters::set(const int index, ScriptArray& value)
	{
		this->_parameters.insert((v8::Handle<v8::Value>)value, index);
	}

	FBOXAPI const int ScriptParameters::count() const
	{
		return this->_parameters.count();
	}

	FBOXAPI ScriptParameters::operator v8::Handle<v8::Value>*() const
	{
		return (v8::Handle<v8::Value>*)this->_parameters;
	}
	FBOXAPI void ScriptParameters::operator+=(String value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptParameters::operator+=(__int32 value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptParameters::operator+=(bool value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptParameters::operator+=(float value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptParameters::operator+=(double value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptParameters::operator+=(ScriptObject& value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptParameters::operator+=(ScriptArray& value)
	{
		this->add(value);
	}

}