
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI ScriptArray::ScriptArray()
	{
		this->_state = 0;
		if (ScriptManager::Started())
		{
			this->_state = new v8::Handle<v8::Array>;
			*this->_state = v8::Array::New(ScriptManager::Isolate);
		}
	}
	FBOXAPI ScriptArray::ScriptArray(const int length)
	{
		this->_state = 0;
		if (ScriptManager::Started())
		{
			this->_state = new v8::Handle<v8::Array>;
			*this->_state = v8::Array::New(ScriptManager::Isolate, length);
		}
	}
	FBOXAPI ScriptArray::ScriptArray(v8::Handle<v8::Array>& source)
	{
		this->_state = 0;
		if (ScriptManager::Started())
		{
			this->_state = new v8::Handle<v8::Array>;
			*this->_state = source;
		}
	}
	FBOXAPI ScriptArray::~ScriptArray()
	{
		if (this->_state != 0)
		{
			this->_state->Clear();
			delete this->_state;
			this->_state = 0;
		}
	}

	FBOXAPI void ScriptArray::add(String value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(this->count(), v8::String::New(value));
		}
	}
	FBOXAPI void ScriptArray::add(__int32 value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(this->count(), v8::Int32::New(value));
		}
	}
	FBOXAPI void ScriptArray::add(bool value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(this->count(), v8::Boolean::New(value));
		}
	}
	FBOXAPI void ScriptArray::add(float value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(this->count(), v8::Number::New((double)value));
		}
	}
	FBOXAPI void ScriptArray::add(double value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(this->count(), v8::Number::New(value));
		}
	}
	FBOXAPI void ScriptArray::add(ScriptObject& value)
	{
		if (ScriptManager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)value).IsEmpty())
		{
			(*this->_state)->Set(this->count(), (v8::Handle<v8::Value>)value);
		}
	}
	FBOXAPI void ScriptArray::add(ScriptArray& value)
	{
		if (ScriptManager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)value).IsEmpty())
		{
			(*this->_state)->Set(this->count(), (v8::Handle<v8::Value>)value);
		}
	}

	FBOXAPI void ScriptArray::set(const int index, String value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, v8::String::New(value));
		}
	}
	FBOXAPI void ScriptArray::set(const int index, __int32 value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, v8::Int32::New(value));
		}
	}
	FBOXAPI void ScriptArray::set(const int index, bool value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, v8::Boolean::New(value));
		}
	}
	FBOXAPI void ScriptArray::set(const int index, float value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, v8::Number::New((double)value));
		}
	}
	FBOXAPI void ScriptArray::set(const int index, double value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, v8::Number::New(value));
		}
	}
	FBOXAPI void ScriptArray::set(const int index, ScriptObject& value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, (v8::Handle<v8::Value>)value);
		}
	}
	FBOXAPI void ScriptArray::set(const int index, ScriptArray& value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(index, (v8::Handle<v8::Value>)value);
		}
	}

	FBOXAPI String ScriptArray::gets(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsString())
			{
				v8::String::Utf8Value result(value->ToString());
				return *result;
			}
		}

		return String::Empty();
	}
	FBOXAPI __int32 ScriptArray::geti(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsInt32())
			{
				return value->Int32Value();
			}
		}

		return 0;
	}
	FBOXAPI bool ScriptArray::getb(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsBoolean())
			{
				return value->BooleanValue();
			}
		}

		return false;
	}
	FBOXAPI float ScriptArray::getf(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsNumber())
			{
				return (float)value->NumberValue();
			}
		}

		return 0.0f;
	}
	FBOXAPI double ScriptArray::getd(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsNumber())
			{
				return value->NumberValue();
			}
		}

		return 0.0;
	}
	FBOXAPI ScriptObject ScriptArray::get(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsObject())
			{
				return ScriptObject(v8::Local<v8::Object>::Cast(value));
			}
		}

		return ScriptObject();
	}
	FBOXAPI ScriptArray ScriptArray::getarr(const int index)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty() && value->IsArray())
			{
				return ScriptArray(v8::Local<v8::Array>::Cast(value));
			}
		}

		return ScriptArray();
	}

	FBOXAPI String ScriptArray::typeof(const int index) const
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && this->count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(index);
			if (!value.IsEmpty())
			{
				if (value->IsUndefined()) return "undefined";
				else if (value->IsNull()) return "null";
				else if (value->IsString() || value->IsStringObject()) return "string";
				else if (value->IsSymbol() || value->IsSymbolObject()) return "symbol";
				else if (value->IsFunction()) return "function";
				else if (value->IsArray()) return "array";
				else if (value->IsObject()) return "object";
				else if (value->IsBoolean() || value->IsBooleanObject()) return "boolean";
				else if (value->IsNumber() || value->IsNumberObject()) return "number";
				else if (value->IsInt32()) return "int32";
				else if (value->IsUint32()) return "uint32";
				else if (value->IsDate()) return "date";
				else if (value->IsRegExp()) return "regex";
			}
		}

		return "undefined";
	}

	FBOXAPI const int ScriptArray::count() const
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			return (int)(*this->_state)->Length();
		}

		return 0;
	}

	FBOXAPI void ScriptArray::operator=(v8::Handle<v8::Array>& object)
	{
		if (this->_state != 0)
		{
			*this->_state = object;
		}
	}
	FBOXAPI ScriptArray::operator v8::Handle<v8::Array>()
	{
		if (this->_state != 0)
		{
			return *this->_state;
		}

		return v8::Handle<v8::Array>();
	}
	FBOXAPI ScriptArray::operator v8::Handle<v8::Value>()
	{
		if (this->_state != 0)
		{
			return v8::Handle<v8::Value>::Cast(*this->_state);
		}

		return v8::Handle<v8::Value>();
	}
	FBOXAPI void ScriptArray::operator+=(String value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptArray::operator+=(__int32 value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptArray::operator+=(bool value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptArray::operator+=(float value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptArray::operator+=(double value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptArray::operator+=(ScriptObject& value)
	{
		this->add(value);
	}
	FBOXAPI void ScriptArray::operator+=(ScriptArray& value)
	{
		this->add(value);
	}

}