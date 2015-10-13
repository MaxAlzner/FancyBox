#ifndef FBOX_SCRIPTOBJECT_H
#define FBOX_SCRIPTOBJECT_H
	
namespace fbox
{
	namespace js
	{

		class FBOXAPI Object
		{
		public:

			Object();
			Object(v8::Handle<v8::Object>& object);
			~Object();

			void set(const char* key, string& value);
			void set(const char* key, int32_t value);
			void set(const char* key, bool value);
			void set(const char* key, float value);
			void set(const char* key, double value);
			void set(const char* key, Object& object);
			void set(const char* key, Array& object);

			string gets(const char* key);
			int32_t geti(const char* key);
			bool getb(const char* key);
			float getf(const char* key);
			double getd(const char* key);
			Object get(const char* key);
			Array getarr(const char* key);

			void call(const char* name);
			void call(string& name);
			void call(const char* name, FunctionParameters& parameters);
			void call(string& name, FunctionParameters& parameters);

			Object construct(const char* name);
			Object construct(string& name);
			Object construct(const char* name, FunctionParameters& parameters);
			Object construct(string& name, FunctionParameters& parameters);

			void accessor(const char* prop, const char* type, void* src, int size, bool setter = true);
			void accessor(const char* prop, Object& object, bool setter = false);
			void accessor(const char* prop, Array& object, bool setter = false);
			void accessor(const char* prop, glm::vec2* v, bool setter = false);
			void accessor(const char* prop, glm::vec3* v, bool setter = false);
			void accessor(const char* prop, glm::vec4* v, bool setter = false);

			string typeof(const char* key) const;
			string typeof(string& key) const;
			Array properties() const;

			void operator=(const Object& object);
			void operator=(v8::Handle<v8::Object>& object);
			operator v8::Handle<v8::Object>() const;
			operator v8::Handle<v8::Value>() const;

		protected:

			static void _getterCallback(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value>& info);
			static void _setterCallback(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);

			v8::Handle<v8::Object>* _state;

		};

	}
}

#endif