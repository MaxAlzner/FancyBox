#ifndef FBOX_SCRIPTARRAY_H
#define FBOX_SCRIPTARRAY_H
	
namespace fbox
{
	namespace js
	{

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

	}
}

#endif