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

			void add(const std::string& value);
			void add(int32_t value);
			void add(bool value);
			void add(float value);
			void add(double value);
			void add(const Object& value);
			void add(const Array& value);

			const int count() const;

			operator v8::Handle<v8::Value>*() const;
			void operator+=(const std::string& value);
			void operator+=(int32_t value);
			void operator+=(bool value);
			void operator+=(float value);
			void operator+=(double value);
			void operator+=(const Object& value);
			void operator+=(const Array& value);

		protected:

			std::vector<v8::Handle<v8::Value> > _parameters;

		};

		class FBOXAPI Object
		{
		public:

			Object();
			Object(const v8::Handle<v8::Object>& object);
			~Object();

			void set(const char* key, const std::string& value);
			void set(const char* key, int32_t value);
			void set(const char* key, bool value);
			void set(const char* key, float value);
			void set(const char* key, double value);
			void set(const char* key, const Object& object);
			void set(const char* key, const Array& object);

			std::string gets(const char* key);
			int32_t geti(const char* key);
			bool getb(const char* key);
			float getf(const char* key);
			double getd(const char* key);
			Object get(const char* key);
			Array getarr(const char* key);

			void call(const char* name);
			void call(const std::string& name);
			void call(const char* name, const FunctionParameters& parameters);
			void call(const std::string& name, const FunctionParameters& parameters);

			Object construct(const char* name);
			Object construct(const std::string& name);
			Object construct(const char* name, const FunctionParameters& parameters);
			Object construct(const std::string& name, const FunctionParameters& parameters);

			void accessor(const char* prop, const char* type, const void* src, int size, bool setter = true);
			void accessor(const char* prop, const Object& object, bool setter = false);
			void accessor(const char* prop, const Array& object, bool setter = false);
			void accessor(const char* prop, const glm::vec2* v, bool setter = false);
			void accessor(const char* prop, const glm::vec3* v, bool setter = false);
			void accessor(const char* prop, const glm::vec4* v, bool setter = false);

			std::string type(const char* key) const;
			std::string type(const std::string& key) const;
			Array properties() const;

			void operator=(const Object& object);
			void operator=(const v8::Handle<v8::Object>& object);
			operator v8::Handle<v8::Object>() const;
			operator v8::Handle<v8::Value>() const;

		protected:

			static void _getter(v8::Local<v8::String> prop, const v8::PropertyCallbackInfo<v8::Value>& info);
			static void _setter(v8::Local<v8::String> prop, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);

			v8::Handle<v8::Object>* _state;

		};

		class FBOXAPI Array
		{
		public:

			Array();
			Array(const int length);
			Array(const v8::Handle<v8::Array>& source);
			~Array();

			class Iterator;
			friend class Iterator;

			void add(const std::string& value);
			void add(int32_t value);
			void add(bool value);
			void add(float value);
			void add(double value);
			void add(const Object& value);
			void add(const Array& value);

			void set(const int index, const std::string& value);
			void set(const int index, int32_t value);
			void set(const int index, bool value);
			void set(const int index, float value);
			void set(const int index, double value);
			void set(const int index, const Object& value);
			void set(const int index, const Array& value);

			std::string gets(const int index);
			int32_t geti(const int index);
			bool getb(const int index);
			float getf(const int index);
			double getd(const int index);
			Object get(const int index);
			Array getarr(const int index);

			std::string type(const int index) const;

			const int count() const;

			Iterator begin() const;
			Iterator end() const;

			void operator=(const Array& object);
			void operator=(const v8::Handle<v8::Array>& object);
			operator v8::Handle<v8::Array>() const;
			operator v8::Handle<v8::Value>() const;
			void operator+=(const std::string& value);
			void operator+=(int32_t value);
			void operator+=(bool value);
			void operator+=(float value);
			void operator+=(double value);
			void operator+=(const Object& value);
			void operator+=(const Array& value);

			class Iterator
			{
			public:

				inline Iterator() {}
				inline Iterator(const Array* _array, const int start) : _array(_array), _index(start) {}
				inline ~Iterator() {}

				std::string gets();
				int32_t geti();
				bool getb();
				float getf();
				double getd();
				Object get();
				Array getarr();

				std::string type() const;
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

			static void Register(const std::string& filename);
			static void Execute(const std::string& command);

			static bool Started();

			static v8::Isolate* Isolate;

		protected:

			static v8::Local<v8::Context> Context;

		};

	}
}

#endif