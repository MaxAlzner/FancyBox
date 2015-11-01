
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace js
	{

		FBOXAPI Object::Object()
		{
			this->_state = 0;
			if (Manager::Started())
			{
				this->_state = new v8::Handle<v8::Object>;
				*this->_state = v8::Object::New(Manager::Isolate);
			}
		}
		FBOXAPI Object::Object(const v8::Handle<v8::Object>& object)
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

		FBOXAPI void Object::set(const char* key, const std::string& value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), v8::String::NewFromUtf8(Manager::Isolate, value.data()));
			}
		}
		FBOXAPI void Object::set(const char* key, int32_t value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), v8::Int32::New(Manager::Isolate, value));
			}
		}
		FBOXAPI void Object::set(const char* key, bool value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), v8::Boolean::New(Manager::Isolate, value));
			}
		}
		FBOXAPI void Object::set(const char* key, float value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), v8::Number::New(Manager::Isolate, (double)value));
			}
		}
		FBOXAPI void Object::set(const char* key, double value)
		{
			if (Manager::Started() && this->_state != 0)
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), v8::Number::New(Manager::Isolate, value));
			}
		}
		FBOXAPI void Object::set(const char* key, const Object& object)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), (v8::Handle<v8::Object>)object);
			}
		}
		FBOXAPI void Object::set(const char* key, const Array& object)
		{
			if (Manager::Started() && this->_state != 0 && !((v8::Handle<v8::Value>)object).IsEmpty())
			{
				(*this->_state)->Set(v8::String::NewFromUtf8(Manager::Isolate, key), (v8::Handle<v8::Value>)object);
			}
		}

		FBOXAPI std::string Object::gets(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
				if (!value.IsEmpty() && value->IsString())
				{
					v8::String::Utf8Value result(value);
					return *result;
				}
			}

			return std::string();
		}
		FBOXAPI int32_t Object::geti(const char* key)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, name));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					func->Call(*this->_state, 0, 0);
				}
			}
		}
		FBOXAPI void Object::call(const std::string& name)
		{
			this->call(name.data());
		}
		FBOXAPI void Object::call(const char* name, const FunctionParameters& parameters)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, name));
				if (!value.IsEmpty() && value->IsFunction())
				{
					v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(value);
					func->Call(*this->_state, parameters.count(), parameters);
				}
			}
		}
		FBOXAPI void Object::call(const std::string& name, const FunctionParameters& parameters)
		{
			this->call(name.data(), parameters);
		}

		FBOXAPI Object Object::construct(const char* name)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, name));
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
		FBOXAPI Object Object::construct(const std::string& name)
		{
			return this->construct(name.data());
		}
		FBOXAPI Object Object::construct(const char* name, const FunctionParameters& parameters)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && parameters.count() > 0)
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, name));
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
		FBOXAPI Object Object::construct(const std::string& name, const FunctionParameters& parameters)
		{
			return this->construct(name.data(), parameters);
		}

		FBOXAPI void Object::accessor(const char* prop, const char* type, const void* src, int size, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Handle<v8::Object> data = v8::Object::New(Manager::Isolate);
				data->Set(0, v8::String::NewFromUtf8(Manager::Isolate, type));
				data->Set(1, v8::Uint32::New(Manager::Isolate, (unsigned int)src));
				data->Set(2, v8::Uint32::New(Manager::Isolate, size));
				(*this->_state)->SetAccessor(v8::String::NewFromUtf8(Manager::Isolate, prop), &(this->_getter), setter ? &(this->_setter) : 0, data);
			}
		}
		FBOXAPI void Object::accessor(const char* prop, const Object& object, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && object._state != 0)
			{
				v8::Handle<v8::Object> data = v8::Object::New(Manager::Isolate);
				data->Set(0, v8::String::NewFromUtf8(Manager::Isolate, "object"));
				data->Set(1, *object._state);
				(*this->_state)->SetAccessor(v8::String::NewFromUtf8(Manager::Isolate, prop), &(this->_getter), setter ? &(this->_setter) : 0, data);
			}
		}
		FBOXAPI void Object::accessor(const char* prop, const Array& object, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Handle<v8::Object> data = v8::Object::New(Manager::Isolate);
				data->Set(0, v8::String::NewFromUtf8(Manager::Isolate, "array"));
				data->Set(1, (v8::Handle<v8::Value>)object);
				(*this->_state)->SetAccessor(v8::String::NewFromUtf8(Manager::Isolate, prop), &(this->_getter), setter ? &(this->_setter) : 0, data);
			}
		}
		FBOXAPI void Object::accessor(const char* prop, const glm::vec2* v, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && v != 0)
			{
				Object obj;
				obj.accessor("x", "number", &v->x, sizeof(float), true);
				obj.accessor("y", "number", &v->y, sizeof(float), true);
				obj.accessor("r", "number", &v->r, sizeof(float), true);
				obj.accessor("g", "number", &v->g, sizeof(float), true);
				obj.accessor("s", "number", &v->s, sizeof(float), true);
				obj.accessor("t", "number", &v->t, sizeof(float), true);
				this->accessor(prop, obj, setter);
			}
		}
		FBOXAPI void Object::accessor(const char* prop, const glm::vec3* v, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && v != 0)
			{
				Object obj;
				obj.accessor("x", "number", &v->x, sizeof(float), true);
				obj.accessor("y", "number", &v->y, sizeof(float), true);
				obj.accessor("z", "number", &v->z, sizeof(float), true);
				obj.accessor("r", "number", &v->r, sizeof(float), true);
				obj.accessor("g", "number", &v->g, sizeof(float), true);
				obj.accessor("b", "number", &v->b, sizeof(float), true);
				obj.accessor("s", "number", &v->s, sizeof(float), true);
				obj.accessor("t", "number", &v->t, sizeof(float), true);
				obj.accessor("p", "number", &v->p, sizeof(float), true);
				this->accessor(prop, obj, setter);
			}
		}
		FBOXAPI void Object::accessor(const char* prop, const glm::vec4* v, bool setter)
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty() && v != 0)
			{
				Object obj;
				obj.accessor("x", "number", &v->x, sizeof(float), true);
				obj.accessor("y", "number", &v->y, sizeof(float), true);
				obj.accessor("z", "number", &v->z, sizeof(float), true);
				obj.accessor("w", "number", &v->w, sizeof(float), true);
				obj.accessor("r", "number", &v->r, sizeof(float), true);
				obj.accessor("g", "number", &v->g, sizeof(float), true);
				obj.accessor("b", "number", &v->b, sizeof(float), true);
				obj.accessor("a", "number", &v->a, sizeof(float), true);
				obj.accessor("s", "number", &v->s, sizeof(float), true);
				obj.accessor("t", "number", &v->t, sizeof(float), true);
				obj.accessor("p", "number", &v->p, sizeof(float), true);
				obj.accessor("q", "number", &v->q, sizeof(float), true);
				this->accessor(prop, obj, setter);
			}
		}

		FBOXAPI std::string Object::type(const char* key) const
		{
			if (Manager::Started() && this->_state != 0 && !this->_state->IsEmpty())
			{
				v8::Local<v8::Value> value = (*this->_state)->Get(v8::String::NewFromUtf8(Manager::Isolate, key));
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
					else if (value->IsSymbol() || value->IsSymbolObject()) { return "symbol"; }
					else if (value->IsInt32()) { return "int32"; }
					else if (value->IsUint32()) { return "uint32"; }
					else if (value->IsDate()) { return "date"; }
					else if (value->IsRegExp()) { return "regex"; }
				}
			}

			return "undefined";
		}
		FBOXAPI std::string Object::type(const std::string& key) const
		{
			return this->type(key.data());
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
		FBOXAPI void Object::operator=(const v8::Handle<v8::Object>& object)
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
				return *this->_state;
			}

			return v8::Handle<v8::Value>();
		}

		FBOXAPI void Object::_getter(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value>& info)
		{
			v8::Handle<v8::Object> ctx = (v8::Handle<v8::Object>)info.Data().As<v8::Object>();
			std::string type(*v8::String::Utf8Value(ctx->Get(0)));
			v8::Handle<v8::Value> src = ctx->Get(1);
			if (type == "null") { info.GetReturnValue().Set(v8::Null()); }
			else if (type == "string") { info.GetReturnValue().Set(v8::String::NewFromUtf8(Manager::Isolate, ((std::string*)src->Int32Value())->c_str())); }
			else if (type == "boolean") { info.GetReturnValue().Set(*((bool*)src->Int32Value())); }
			else if (type == "number") { info.GetReturnValue().Set(*((float*)src->Int32Value())); }
			else if (type == "int32") { info.GetReturnValue().Set(*((int32_t*)src->Int32Value())); }
			else if (type == "uint32") { info.GetReturnValue().Set(*((uint32_t*)src->Int32Value())); }
			else if (type == "array" || type == "object") { info.GetReturnValue().Set(src); }
		}
		FBOXAPI void Object::_setter(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
		{
			v8::Handle<v8::Object> ctx = (v8::Handle<v8::Object>)info.Data().As<v8::Object>();
			std::string type(*v8::String::Utf8Value(ctx->Get(0)));
			v8::Handle<v8::Value> src = ctx->Get(1);
			if (value->IsNull() || value->IsUndefined()) { return; }
			else if (type == "string" && (value->IsString() || value->IsStringObject())) { *((std::string*)src->Int32Value()) = *v8::String::Utf8Value(value->ToString()); }
			else if (type == "boolean" && (value->IsBoolean() || value->IsBooleanObject())) { *((bool*)src->Int32Value()) = value->BooleanValue(); }
			else if (type == "number" && (value->IsNumber() || value->IsNumberObject())) { *((float*)src->Int32Value()) = (float)value->NumberValue(); }
			else if (type == "int32" && value->IsInt32()) { *((int32_t*)src->Int32Value()) = value->Int32Value(); }
			else if (type == "uint32" && value->IsUint32()) { *((uint32_t*)src->Int32Value()) = value->Uint32Value(); }
			else if (type == "array" && value->IsArray())
			{
				v8::Handle<v8::Array> obj = src.As<v8::Array>();
				v8::Handle<v8::Array> values = value.As<v8::Array>();
				obj.Clear();
				for (uint32_t i = 0; i < values->Length(); i++)
				{
					obj->Set(i, values->Get(i));
				}
			}
			else if (type == "object" && value->IsObject())
			{
				v8::Handle<v8::Object> obj = src.As<v8::Object>();
				v8::Handle<v8::Object> values = value.As<v8::Object>();
				v8::Handle<v8::Array> props = values->GetPropertyNames();
				for (uint32_t i = 0; i < props->Length(); i++)
				{
					obj->Set(props->Get(i), values->Get(props->Get(i)));
				}
			}
		}

	}
}