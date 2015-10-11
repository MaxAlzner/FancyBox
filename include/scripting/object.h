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

			void set(string& key, string& value);
			void set(string& key, __int32 value);
			void set(string& key, bool value);
			void set(string& key, float value);
			void set(string& key, double value);
			void set(string& key, Object& object);
			void set(string& key, Array& object);

			string gets(string& key);
			__int32 geti(string& key);
			bool getb(string& key);
			float getf(string& key);
			double getd(string& key);
			Object get(string& key);
			Array getarr(string& key);

			void call(string& name);
			void call(string& name, Object& parameter);
			void call(string& name, FunctionParameters& parameters);

			Object construct(string& name);
			Object construct(string& name, Object& parameter);
			Object construct(string& name, FunctionParameters& parameters);

			string typeof(string& key) const;
			Array properties() const;

			void operator=(const Object& object);
			void operator=(v8::Handle<v8::Object>& object);
			operator v8::Handle<v8::Object>() const;
			operator v8::Handle<v8::Value>() const;

		protected:

			void _getter(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value>& info);
			void _setter(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);

			template <typename T> class propertyLink
			{
			public:

				T* source;

			};

			v8::Handle<v8::Object>* _state;

		};

	}
}

#endif