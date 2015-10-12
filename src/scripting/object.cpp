
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

		FBOXAPI void Object::set(const char* key, string& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key), v8::String::New(value.data()));
			}
		}
		FBOXAPI void Object::set(const char* key, __int32 value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key), v8::Int32::New(value));
			}
		}
		FBOXAPI void Object::set(const char* key, bool value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key), v8::Boolean::New(value));
			}
		}
		FBOXAPI void Object::set(const char* key, float value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key), v8::Number::New((double)value));
			}
		}
		FBOXAPI void Object::set(const char* key, double value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::New(key), v8::Number::New(value));
			}
		}
		FBOXAPI void Object::set(const char* key, Object& object)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
			{
				(*this->_state)->Set(v8::String::New(key), (v8::Handle<v8::Object>)object);
			}
		}
		FBOXAPI void Object::set(const char* key, Array& object)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
			{
				(*this->_state)->Set(v8::String::New(key), (v8::Handle<v8::Value>)object);
			}
		}

		FBOXAPI string Object::gets(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsString())
				{
					v8::String::Utf8Value result(value);
					return *result;
				}
			}

			return string();
		}
		FBOXAPI __int32 Object::geti(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsInt32())
				{
					return value->Int32Value();
				}
			}

			return 0;
		}
		FBOXAPI bool Object::getb(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsBoolean())
				{
					return value->BooleanValue();
				}
			}

			return false;
		}
		FBOXAPI float Object::getf(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsNumber())
				{
					return (float)value->NumberValue();
				}
			}

			return 0.0f;
		}
		FBOXAPI double Object::getd(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsNumber())
				{
					return value->NumberValue();
				}
			}

			return 0.0;
		}
		FBOXAPI Object Object::get(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsObject())
				{
					return Object(v8::Local<v8::Object>::Cast(value));
				}
			}

			return Object();
		}
		FBOXAPI Array Object::getarr(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty() && value->IsArray())
				{
					return Array(v8::Local<v8::Array>::Cast(value));
				}
			}

			return Array();
		}

		FBOXAPI void Object::call(const char* name)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					func->Call(v8::Handle<v8::Value>::Cast(*this->_state), 0, 0);
				}
			}
		}
		FBOXAPI void Object::call(string& name)
		{
			this->call(name.data());
		}
		FBOXAPI void Object::call(const char* name, FunctionParameters& parameters)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					func->Call(v8::Handle<v8::Value>::Cast(*this->_state), parameters.count(), parameters);
				}
			}
		}
		FBOXAPI void Object::call(string& name, FunctionParameters& parameters)
		{
			this->call(name.data(), parameters);
		}

		FBOXAPI Object Object::construct(const char* name)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
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
		FBOXAPI Object Object::construct(string& name)
		{
			return this->construct(name.data());
		}
		FBOXAPI Object Object::construct(const char* name, FunctionParameters& parameters)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(name));
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
		FBOXAPI Object Object::construct(string& name, FunctionParameters& parameters)
		{
			return this->construct(name.data(), parameters);
		}

		FBOXAPI void Object::accessor(const char* prop, const char* type, void* src, int size, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Handle<v8::Object> data = v8::Object::New(Manager::Isolate);
				data->Set(0, v8::String::New(type));
				data->Set(1, v8::Uint32::New((unsigned int)src));
				data->Set(2, v8::Uint32::New(size));
				(*this->_state)->SetAccessor(v8::String::New(prop), &(this->_getterCallback), setter ? &(this->_setterCallback) : 0, data);
			}
		}

		FBOXAPI string Object::typeof(const char* key) const
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::New(key));
				if (!value.IsEmpty())
				{
					if (value->IsUndefined()) { return "undefined"; }
					else if (value->IsNull()) { return "null"; }
					else if (value->IsString() || value->IsStringObject()) { return "string"; }
					else if (value->IsSymbol() || value->IsSymbolObject()) { return "symbol"; }
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
		FBOXAPI string Object::typeof(string& key) const
		{
			return this->typeof(key.data());
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

		FBOXAPI void Object::_getterCallback(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value>& info)
		{
			v8::Handle<v8::Object> ctx = (v8::Handle<v8::Object>)info.Data().As<v8::Object>();
			string type(*v8::String::Utf8Value(ctx->Get(0)));
			v8::Handle<v8::Value> src = ctx->Get(1);
			if (type == "null") { return info.GetReturnValue().Set(v8::Null(Manager::Isolate)); }
			else if (type == "string") { return info.GetReturnValue().Set(v8::String::New((*((string*)src->Int32Value())).data())); }
			else if (type == "boolean") { return info.GetReturnValue().Set(*((bool*)src->Int32Value())); }
			else if (type == "number") { return info.GetReturnValue().Set(*((float*)src->Int32Value())); }
			else if (type == "int32") { return info.GetReturnValue().Set(*((int32_t*)src->Int32Value())); }
			else if (type == "uint32") { return info.GetReturnValue().Set(*((uint32_t*)src->Int32Value())); }
		}
		FBOXAPI void Object::_setterCallback(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{
			v8::Handle<v8::Object> ctx = (v8::Handle<v8::Object>)info.Data().As<v8::Object>();
			string type(*v8::String::Utf8Value(ctx->Get(0)));
			v8::Handle<v8::Value> src = ctx->Get(1);
			if (value->IsNull() || value->IsUndefined()) { return; }
			else if (type == "string" && (value->IsString() || value->IsStringObject())) { *((string*)src->Int32Value()) = *v8::String::Utf8Value(value->ToString()); }
			else if (type == "boolean" && (value->IsBoolean() || value->IsBooleanObject())) { *((bool*)src->Int32Value()) = value->BooleanValue(); }
			else if (type == "number" && (value->IsNumber() || value->IsNumberObject())) { *((float*)src->Int32Value()) = (float)value->NumberValue(); }
			else if (type == "int32" && value->IsInt32()) { *((int32_t*)src->Int32Value()) = value->Int32Value(); }
			else if (type == "uint32" && value->IsUint32()) { *((uint32_t*)src->Int32Value()) = value->Uint32Value(); }
		}

	}
}