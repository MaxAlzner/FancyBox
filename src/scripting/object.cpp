
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	namespace js
	{

		FBOXAPI Object::Object()
		{
			this->_state = 0;
			if (Manager::Started())
			{
				this->_state = new v8::Handle < v8::Object >;
				*this->_state = v8::Object::New(Manager::Isolate);
			}
		}
		FBOXAPI Object::Object(v8::Handle<v8::Object>& object)
		{
			this->_state = 0;
			if (Manager::Started())
			{
				this->_state = new v8::Handle<v8::Object>;
				*this->_state = object;
			}
		}
		FBOXAPI Object::~Object()
		{
			if (this->_state != 0)
			{
				delete this->_state;
				this->_state = 0;
			}
		}

		FBOXAPI void Object::set(string& key, string& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key.data()), v8::String::New(value.data()));
			}
		}
		FBOXAPI void Object::set(string& key, __int32 value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key.data()), v8::Int32::New(value));
			}
		}
		FBOXAPI void Object::set(string& key, bool value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key.data()), v8::Boolean::New(value));
			}
		}
		FBOXAPI void Object::set(string& key, float value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key.data()), v8::Number::New((double)value));
			}
		}
		FBOXAPI void Object::set(string& key, double value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key.data()), v8::Number::New(value));
			}
		}
		FBOXAPI void Object::set(string& key, Object& object)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
			{
				(*this->_state)->Set(v8::String::New(key.data()), (v8::Handle<v8::Object>)object);
			}
		}
		FBOXAPI void Object::set(string& key, Array& object)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
			{
				(*this->_state)->Set(v8::String::New(key.data()), (v8::Handle<v8::Value>)object);
			}
		}

		FBOXAPI string Object::gets(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsString())
				{
					v8::String::Utf8Value result(value);
					return *result;
				}
			}

			return string();
		}
		FBOXAPI __int32 Object::geti(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsInt32())
				{
					return value->Int32Value();
				}
			}

			return 0;
		}
		FBOXAPI bool Object::getb(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsBoolean())
				{
					return value->BooleanValue();
				}
			}

			return false;
		}
		FBOXAPI float Object::getf(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsNumber())
				{
					return (float)value->NumberValue();
				}
			}

			return 0.0f;
		}
		FBOXAPI double Object::getd(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsNumber())
				{
					return value->NumberValue();
				}
			}

			return 0.0;
		}
		FBOXAPI Object Object::get(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsObject())
				{
					return Object(v8::Local<v8::Object>::Cast(value));
				}
			}

			return Object();
		}
		FBOXAPI Array Object::getarr(string& key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
				if (!value.IsEmpty() && value->IsArray())
				{
					return Array(v8::Local<v8::Array>::Cast(value));
				}
			}

			return Array();
		}

		FBOXAPI void Object::call(string& name)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name.data()));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					func->Call(v8::Handle<v8::Value>::Cast(*this->_state), 0, 0);
				}
			}
		}
		FBOXAPI void Object::call(string& name, Object& parameter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() &&
				parameter._state != 0 && !parameter._state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name.data()));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					v8::Handle<v8::Value> arg = parameter;
					func->Call(v8::Handle<v8::Value>::Cast(*this->_state), 1, (v8::Handle<v8::Value>*)&arg);
				}
			}
		}
		FBOXAPI void Object::call(string& name, FunctionParameters& parameters)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name.data()));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					func->Call(v8::Handle<v8::Value>::Cast(*this->_state), parameters.count(), parameters);
				}
			}
		}

		FBOXAPI Object Object::construct(string& name)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name.data()));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					v8::Handle<v8::Value> created = func->CallAsConstructor(0, 0);
					if (!created.IsEmpty() && created->IsObject())
					{
						return Object(v8::Handle<v8::Object>::Cast(created));
					}
				}
			}

			return Object();
		}
		FBOXAPI Object Object::construct(string& name, Object& parameter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() &&
				parameter._state != 0 && !parameter._state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name.data()));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					v8::Handle<v8::Value> arg = parameter;
					v8::Handle<v8::Value> created = func->CallAsConstructor(1, (v8::Handle<v8::Value>*)&arg);
					if (!created.IsEmpty() && created->IsObject())
					{
						return Object(v8::Handle<v8::Object>::Cast(created));
					}
				}
			}

			return Object();
		}
		FBOXAPI Object Object::construct(string& name, FunctionParameters& parameters)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name.data()));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					v8::Handle<v8::Value> created = func->CallAsConstructor(parameters.count(), parameters);
					if (!created.IsEmpty() && created->IsObject())
					{
						return Object(v8::Handle<v8::Object>::Cast(created));
					}
				}
			}

			return Object();
		}

		FBOXAPI string Object::typeof(string& key) const
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key.data()));
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
		FBOXAPI Array Object::properties() const
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				return Array((*this->_state)->GetPropertyNames());
			}

			return Array();
		}

		FBOXAPI void Object::operator=(const Object& object)
		{
			if (this->_state != 0)
			{
				*this->_state = *object._state;
			}
		}
		FBOXAPI void Object::operator=(v8::Handle<v8::Object>& object)
		{
			if (this->_state != 0)
			{
				*this->_state = object;
			}
		}
		FBOXAPI Object::operator v8::Handle<v8::Object>() const
		{
			if (this->_state != 0)
			{
				return *this->_state;
			}

			return v8::Handle<v8::Object>();
		}
		FBOXAPI Object::operator v8::Handle<v8::Value>() const
		{
			if (this->_state != 0)
			{
				return v8::Handle<v8::Value>::Cast(*this->_state);
			}

			return v8::Handle<v8::Value>();
		}

		FBOXAPI void Object::_getter(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value>& info)
		{

		}
		FBOXAPI void Object::_setter(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{

		}

	}
}