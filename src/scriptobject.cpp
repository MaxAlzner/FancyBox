
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI ScriptObject::ScriptObject()
	{
		this->_state = 0;
		if (ScriptManager::Started())
		{
			this->_state = new v8::Handle < v8::Object > ;
			*this->_state = v8::Object::New(ScriptManager::Isolate);
		}
	}
	FBOXAPI ScriptObject::ScriptObject(v8::Handle<v8::Object>& object)
	{
		this->_state = 0;
		if (ScriptManager::Started())
		{
			this->_state = new v8::Handle<v8::Object>;
			*this->_state = object;
		}
	}
	FBOXAPI ScriptObject::~ScriptObject()
	{
		if (this->_state != 0)
		{
			this->_state->Clear();
			delete this->_state;
			this->_state = 0;
		}
	}

	FBOXAPI void ScriptObject::set(String key, String value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(v8::String::New(key), v8::String::New(value));
		}
	}
	FBOXAPI void ScriptObject::set(String key, __int32 value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(v8::String::New(key), v8::Int32::New(value));
		}
	}
	FBOXAPI void ScriptObject::set(String key, bool value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(v8::String::New(key), v8::Boolean::New(value));
		}
	}
	FBOXAPI void ScriptObject::set(String key, float value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(v8::String::New(key), v8::Number::New((double)value));
		}
	}
	FBOXAPI void ScriptObject::set(String key, double value)
	{
		if (ScriptManager::Started() && this->_state != 0)
		{
			(*this->_state)->Set(v8::String::New(key), v8::Number::New(value));
		}
	}
	FBOXAPI void ScriptObject::set(String key, ScriptObject& object)
	{
		if (ScriptManager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
		{
			(*this->_state)->Set(v8::String::New(key), (v8::Handle<v8::Object>)object);
		}
	}
	FBOXAPI void ScriptObject::set(String key, ScriptArray& object)
	{
		if (ScriptManager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
		{
			(*this->_state)->Set(v8::String::New(key), (v8::Handle<v8::Value>)object);
		}
	}

	FBOXAPI String ScriptObject::gets(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsString())
			{
				v8::String::Utf8Value result(value);
				return *result;
			}
		}

		return String::Empty();
	}
	FBOXAPI __int32 ScriptObject::geti(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsInt32())
			{
				return value->Int32Value();
			}
		}

		return 0;
	}
	FBOXAPI bool ScriptObject::getb(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsBoolean())
			{
				return value->BooleanValue();
			}
		}

		return false;
	}
	FBOXAPI float ScriptObject::getf(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsNumber())
			{
				return (float)value->NumberValue();
			}
		}

		return 0.0f;
	}
	FBOXAPI double ScriptObject::getd(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsNumber())
			{
				return value->NumberValue();
			}
		}

		return 0.0;
	}
	FBOXAPI ScriptObject ScriptObject::get(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsObject())
			{
				return ScriptObject(v8::Local<v8::Object>::Cast(value));
			}
		}

		return ScriptObject();
	}
	FBOXAPI ScriptArray ScriptObject::getarr(String key)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
			if (!value.IsEmpty() && value->IsArray())
			{
				return ScriptArray(v8::Local<v8::Array>::Cast(value));
			}
		}

		return ScriptArray();
	}

	FBOXAPI void ScriptObject::call(String name)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
			if (!value.IsEmpty() && value->IsFunction())
			{
				v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
				func->Call(v8::Handle<v8::Value>::Cast(*this->_state), 0, 0);
			}
		}
	}
	FBOXAPI void ScriptObject::call(String name, ScriptObject& parameter)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() &&
			parameter._state != 0 && !parameter._state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
			if (!value.IsEmpty() && value->IsFunction())
			{
				v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
				v8::Handle<v8::Value> arg = parameter;
				func->Call(v8::Handle<v8::Value>::Cast(*this->_state), 1, (v8::Handle<v8::Value>*)&arg);
			}
		}
	}
	FBOXAPI void ScriptObject::call(String name, ScriptParameters& parameters)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
			if (!value.IsEmpty() && value->IsFunction())
			{
				v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
				func->Call(v8::Handle<v8::Value>::Cast(*this->_state), parameters.count(), parameters);
			}
		}
	}

	FBOXAPI ScriptObject ScriptObject::construct(String name)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
			if (!value.IsEmpty() && value->IsFunction())
			{
				v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
				v8::Handle<v8::Value> created = func->CallAsConstructor(0, 0);
				if (!created.IsEmpty() && created->IsObject())
				{
					return ScriptObject(v8::Handle<v8::Object>::Cast(created));
				}
			}
		}

		return ScriptObject();
	}
	FBOXAPI ScriptObject ScriptObject::construct(String name, ScriptObject& parameter)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() &&
			parameter._state != 0 && !parameter._state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
			if (!value.IsEmpty() && value->IsFunction())
			{
				v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
				v8::Handle<v8::Value> arg = parameter;
				v8::Handle<v8::Value> created = func->CallAsConstructor(1, (v8::Handle<v8::Value>*)&arg);
				if (!created.IsEmpty() && created->IsObject())
				{
					return ScriptObject(v8::Handle<v8::Object>::Cast(created));
				}
			}
		}

		return ScriptObject();
	}
	FBOXAPI ScriptObject ScriptObject::construct(String name, ScriptParameters& parameters)
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
			if (!value.IsEmpty() && value->IsFunction())
			{
				v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
				v8::Handle<v8::Value> created = func->CallAsConstructor(parameters.count(), parameters);
				if (!created.IsEmpty() && created->IsObject())
				{
					return ScriptObject(v8::Handle<v8::Object>::Cast(created));
				}
			}
		}

		return ScriptObject();
	}

	FBOXAPI String ScriptObject::typeof(String key) const
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
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
	FBOXAPI ScriptArray ScriptObject::properties() const
	{
		if (ScriptManager::Started() && this->_state != 0 && !this->_state->IsEmpty())
		{
			return ScriptArray((*this->_state)->GetPropertyNames());
		}

		return ScriptArray();
	}

	FBOXAPI void ScriptObject::operator=(v8::Handle<v8::Object>& object)
	{
		if (this->_state != 0)
		{
			*this->_state = object;
		}
	}
	FBOXAPI ScriptObject::operator v8::Handle<v8::Object>() const
	{
		if (this->_state != 0)
		{
			return *this->_state;
		}

		return v8::Handle<v8::Object>();
	}
	FBOXAPI ScriptObject::operator v8::Handle<v8::Value>() const
	{
		if (this->_state != 0)
		{
			return v8::Handle<v8::Value>::Cast(*this->_state);
		}

		return v8::Handle<v8::Value>();
	}

}