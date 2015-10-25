#ifndef FBOX_SCRIPTING_H
#define FBOX_SCRIPTING_H

#include "FancyBox_setup.h"

namespace fbox
{
	namespace js
	{
		class FBOXAPI Object;
		class FBOXAPI Array;
		class FBOXAPI FunctionParameters;
		class FBOXAPI Manager;

		class FBOXAPI FunctionParameters
		{
		public:

			inline FunctionParameters() : _parameters(4) {}
			inline ~FunctionParameters() { this->_parameters.clear(); }

			void add(string& value);
			void add(__int32 value);
			void add(bool value);
			void add(float value);
			void add(double value);
			void add(Object& value);
			void add(Array& value);

			const int count() const;

			operator v8::Handle<v8::Value>*() const;
			void operator+=(string& value);
			void operator+=(__int32 value);
			void operator+=(bool value);
			void operator+=(float value);
			void operator+=(double value);
			void operator+=(Object& value);
			void operator+=(Array& value);

		protected:

			std::vector<v8::Handle<v8::Value>> _parameters;

		};

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

		class FBOXAPI Array
		{
		public:

			Array();
			Array(const int length);
			Array(v8::Handle<v8::Array>& source);
			~Array();

			class Iterator;
			friend class Iterator;

			void add(string& value);
			void add(int32_t value);
			void add(bool value);
			void add(float value);
			void add(double value);
			void add(Object& value);
			void add(Array& value);

			void set(const int index, string& value);
			void set(const int index, int32_t value);
			void set(const int index, bool value);
			void set(const int index, float value);
			void set(const int index, double value);
			void set(const int index, Object& value);
			void set(const int index, Array& value);

			string gets(const int index);
			int32_t geti(const int index);
			bool getb(const int index);
			float getf(const int index);
			double getd(const int index);
			Object get(const int index);
			Array getarr(const int index);

			string typeof(const int index) const;

			const int count() const;

			Iterator begin() const;
			Iterator end() const;

			void operator=(const Array& object);
			void operator=(v8::Handle<v8::Array>& object);
			operator v8::Handle<v8::Array>();
			operator v8::Handle<v8::Value>();
			void operator+=(string& value);
			void operator+=(__int32 value);
			void operator+=(bool value);
			void operator+=(float value);
			void operator+=(double value);
			void operator+=(Object& value);
			void operator+=(Array& value);

			class Iterator
			{
			public:

				inline Iterator() {}
				inline Iterator(const Array* _array, const int start) : _array(_array), _index(start) {}
				inline ~Iterator() {}

				string gets();
				int32_t geti();
				bool getb();
				float getf();
				double getd();
				Object get();
				Array getarr();

				string typeof() const;
				const int index() const;

				Iterator& operator=(const int index);
				Iterator& operator++();
				Iterator operator++(const int);
				Iterator& operator--();
				Iterator operator--(const int);
				bool operator==(const int index);
				bool operator!=(const int index);
				bool operator>(const int index);
				bool operator<(const int index);
				bool operator>=(const int index);
				bool operator<=(const int index);
				Iterator& operator+=(const int increment);
				Iterator& operator-=(const int increment);

			protected:

				const Array* _array;
				int _index;

			};

		protected:

			v8::Handle<v8::Array>* _state;

		};

		class FBOXAPI Manager
		{
		public:

			static void Initialize();
			static void Dispose();

			static Object Global();

			static void Register(string& filename);
			static void Execute(string& command);

			static bool Started();

			static v8::Isolate* Isolate;

		protected:

			static v8::Local<v8::Context> Context;

		};

	}
}

#endif