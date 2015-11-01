
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace js
	{

		FBOXAPI Array::Array()
		{
			this->_state = 0;
			if (Manager::Started())
			{
				this->_state = new v8::Handle<v8::Array>;
				*this->_state = v8::Array::New();
			}
		}
		FBOXAPI Array::Array(const int length)
		{
			this->_state = 0;
			if (Manager::Started())
			{
				this->_state = new v8::Handle<v8::Array>;
				*this->_state = v8::Array::New(length);
			}
		}
		FBOXAPI Array::Array(const v8::Handle<v8::Array>& source)
		{
			this->_state = 0;
			if (Manager::Started())
			{
				this->_state = new v8::Handle<v8::Array>;
				*this->_state = source;
			}
		}
		FBOXAPI Array::~Array()
		{
			if (this->_state != 0)
			{
				delete this->_state;
				this->_state = 0;
			}
		}

		FBOXAPI void Array::add(const std::string& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(this->count(), v8::String::New(value.data()));
			}
		}
		FBOXAPI void Array::add(int32_t value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(this->count(), v8::Int32::New(value));
			}
		}
		FBOXAPI void Array::add(bool value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(this->count(), v8::Boolean::New(value));
			}
		}
		FBOXAPI void Array::add(float value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(this->count(), v8::Number::New((double)value));
			}
		}
		FBOXAPI void Array::add(double value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(this->count(), v8::Number::New(value));
			}
		}
		FBOXAPI void Array::add(const Object& value)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)value).IsEmpty())
			{
				(*this->_state)->Set(this->count(), (v8::Handle<v8::Value>)value);
			}
		}
		FBOXAPI void Array::add(const Array& value)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)value).IsEmpty())
			{
				(*this->_state)->Set(this->count(), (v8::Handle<v8::Value>)value);
			}
		}

		FBOXAPI void Array::set(const int index, const std::string& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, v8::String::New(value.data()));
			}
		}
		FBOXAPI void Array::set(const int index, int32_t value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, v8::Int32::New(value));
			}
		}
		FBOXAPI void Array::set(const int index, bool value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, v8::Boolean::New(value));
			}
		}
		FBOXAPI void Array::set(const int index, float value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, v8::Number::New((double)value));
			}
		}
		FBOXAPI void Array::set(const int index, double value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, v8::Number::New(value));
			}
		}
		FBOXAPI void Array::set(const int index, const Object& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, (v8::Handle<v8::Value>)value);
			}
		}
		FBOXAPI void Array::set(const int index, const Array& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(index, (v8::Handle<v8::Value>)value);
			}
		}

		FBOXAPI std::string Array::gets(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsString())
				{
					v8::String::Utf8Value result(value->ToString());
					return *result;
				}
			}

			return std::string();
		}
		FBOXAPI int32_t Array::geti(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsInt32())
				{
					return value->Int32Value();
				}
			}

			return 0;
		}
		FBOXAPI bool Array::getb(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsBoolean())
				{
					return value->BooleanValue();
				}
			}

			return false;
		}
		FBOXAPI float Array::getf(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsNumber())
				{
					return (float)value->NumberValue();
				}
			}

			return 0.0f;
		}
		FBOXAPI double Array::getd(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsNumber())
				{
					return value->NumberValue();
				}
			}

			return 0.0;
		}
		FBOXAPI Object Array::get(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsObject())
				{
					return Object(v8::Local<v8::Object>::Cast(value));
				}
			}

			return Object();
		}
		FBOXAPI Array Array::getarr(const int index)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty() && value->IsArray())
				{
					return Array(v8::Local<v8::Array>::Cast(value));
				}
			}

			return Array();
		}

		FBOXAPI std::string Array::type(const int index) const
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(index);
				if (!value.IsEmpty())
				{
					if (value->IsUndefined()) { return "undefined"; }
					else if (value->IsNull()) { return "null"; }
					else if (value->IsString() || value->IsStringObject()) { return "string"; }
					else if (value->IsFunction()) { return "function"; }
					else if (value->IsArray()) { return "array"; }
					else if (value->IsObject()) { return "object"; }
					else if (value->IsBoolean() || value->IsBooleanObject()) { return "boolean"; }
					else if (value->IsNumber() || value->IsNumberObject()) { return "number"; }
					else if (value->IsInt32()) { return "int32"; }
					else if (value->IsUint32()) { return "uint32"; }
					else if (value->IsDate()) { return "date"; }
					else if (value->IsRegExp()) { return "regex"; }
				}
			}

			return "undefined";
		}

		FBOXAPI const int Array::count() const
		{
			if (Manager::Started() && this->_state != 0)
			{
				return (int)(*this->_state)->Length();
			}

			return 0;
		}

		FBOXAPI Array::Iterator Array::begin() const
		{
			return Iterator(this, 0);
		}
		FBOXAPI Array::Iterator Array::end() const
		{
			return Iterator(this, this->count() - 1);
		}

		FBOXAPI void Array::operator=(const Array& object)
		{
			if (this->_state != 0)
			{
				*this->_state = *object._state;
			}
		}
		FBOXAPI void Array::operator=(const v8::Handle<v8::Array>& object)
		{
			if (this->_state != 0)
			{
				*this->_state = object;
			}
		}
		FBOXAPI Array::operator v8::Handle<v8::Array>() const
		{
			if (this->_state != 0)
			{
				return *this->_state;
			}

			return v8::Handle<v8::Array>();
		}
		FBOXAPI Array::operator v8::Handle<v8::Value>() const
		{
			if (this->_state != 0)
			{
				return (v8::Handle<v8::Value>)*this->_state;
			}

			return v8::Handle<v8::Value>();
		}
		FBOXAPI void Array::operator+=(const std::string& value)
		{
			this->add(value);
		}
		FBOXAPI void Array::operator+=(int32_t value)
		{
			this->add(value);
		}
		FBOXAPI void Array::operator+=(bool value)
		{
			this->add(value);
		}
		FBOXAPI void Array::operator+=(float value)
		{
			this->add(value);
		}
		FBOXAPI void Array::operator+=(double value)
		{
			this->add(value);
		}
		FBOXAPI void Array::operator+=(const Object& value)
		{
			this->add(value);
		}
		FBOXAPI void Array::operator+=(const Array& value)
		{
			this->add(value);
		}

		FBOXAPI std::string Array::Iterator::gets()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsString())
				{
					v8::String::Utf8Value result(value->ToString());
					return *result;
				}
			}

			return std::string();
		}
		FBOXAPI int32_t Array::Iterator::geti()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsInt32())
				{
					return value->Int32Value();
				}
			}

			return 0;
		}
		FBOXAPI bool Array::Iterator::getb()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsBoolean())
				{
					return value->BooleanValue();
				}
			}

			return false;
		}
		FBOXAPI float Array::Iterator::getf()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsNumber())
				{
					return (float)value->NumberValue();
				}
			}

			return 0.0f;
		}
		FBOXAPI double Array::Iterator::getd()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsNumber())
				{
					return value->NumberValue();
				}
			}

			return 0.0;
		}
		FBOXAPI Object Array::Iterator::get()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsObject())
				{
					return Object(v8::Local<v8::Object>::Cast(value));
				}
			}

			return Object();
		}
		FBOXAPI Array Array::Iterator::getarr()
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_array->_state)->Get(this->_index);
				if (!value.IsEmpty() && value->IsArray())
				{
					return Array(v8::Local<v8::Array>::Cast(value));
				}
			}

			return Array();
		}

		FBOXAPI std::string Array::Iterator::type() const
		{
			if (Manager::Started() && this->_array != 0 && this->_array->_state != 0 && !this->_array->_state->IsEmpty())
			{
				return this->_array->type(this->_index);
			}

			return "undefined";
		}
		FBOXAPI const int Array::Iterator::index() const
		{
			return this->_index;
		}

		FBOXAPI Array::Iterator& Array::Iterator::operator=(const int index)
		{
			this->_index = index;
			return *this;
		}
		FBOXAPI Array::Iterator& Array::Iterator::operator++()
		{
			this->_index++;
			return *this;
		}
		FBOXAPI Array::Iterator Array::Iterator::operator++(const int)
		{
			return Iterator(this->_array, (++*this)._index);
		}
		FBOXAPI Array::Iterator& Array::Iterator::operator--()
		{
			this->_index--;
			return *this;
		}
		FBOXAPI Array::Iterator Array::Iterator::operator--(const int)
		{
			return Iterator(this->_array, (--*this)._index);
		}
		FBOXAPI bool Array::Iterator::operator==(const int index)
		{
			return this->_index == index;
		}
		FBOXAPI bool Array::Iterator::operator!=(const int index)
		{
			return this->_index != index;
		}
		FBOXAPI bool Array::Iterator::operator>(const int index)
		{
			return this->_index > index;
		}
		FBOXAPI bool Array::Iterator::operator<(const int index)
		{
			return this->_index < index;
		}
		FBOXAPI bool Array::Iterator::operator>=(const int index)
		{
			return this->_index >= index;
		}
		FBOXAPI bool Array::Iterator::operator<=(const int index)
		{
			return this->_index <= index;
		}
		FBOXAPI Array::Iterator& Array::Iterator::operator+=(const int increment)
		{
			this->_index += increment;
			return *this;
		}
		FBOXAPI Array::Iterator& Array::Iterator::operator-=(const int increment)
		{
			this->_index -= increment;
			return *this;
		}

	}
}