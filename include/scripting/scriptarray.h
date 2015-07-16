#ifndef FBOX_SCRIPTARFBOX_H
#define FBOX_SCRIPTARFBOX_H
	
namespace fbox
{

	class FBOXAPI ScriptArray
	{
	public:

		ScriptArray();
		ScriptArray(const int length);
		ScriptArray(v8::Handle<v8::Array>& source);
		~ScriptArray();

		class Iterator;
		friend class Iterator;

		void add(String value);
		void add(__int32 value);
		void add(bool value);
		void add(float value);
		void add(double value);
		void add(ScriptObject& value);
		void add(ScriptArray& value);

		void set(const int index, String value);
		void set(const int index, __int32 value);
		void set(const int index, bool value);
		void set(const int index, float value);
		void set(const int index, double value);
		void set(const int index, ScriptObject& value);
		void set(const int index, ScriptArray& value);

		String gets(const int index);
		int geti(const int index);
		bool getb(const int index);
		float getf(const int index);
		double getd(const int index);
		ScriptObject get(const int index);
		ScriptArray getarr(const int index);

		String typeof(const int index) const;

		const int count() const;

		Iterator begin() const;
		Iterator end() const;

		void operator=(const ScriptArray& object);
		void operator=(v8::Handle<v8::Array>& object);
		operator v8::Handle<v8::Array>();
		operator v8::Handle<v8::Value>();
		void operator+=(String value);
		void operator+=(__int32 value);
		void operator+=(bool value);
		void operator+=(float value);
		void operator+=(double value);
		void operator+=(ScriptObject& value);
		void operator+=(ScriptArray& value);

		class Iterator
		{
		public:

			inline Iterator() {}
			inline Iterator(const ScriptArray* _array, const int start) : _array(_array), _index(start) {}
			inline ~Iterator() {}

			String gets();
			int geti();
			bool getb();
			float getf();
			double getd();
			ScriptObject get();
			ScriptArray getarr();

			String typeof() const;
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

			const ScriptArray* _array;
			int _index;

		};

	protected:

		v8::Handle<v8::Array>* _state;

	};

}

#endif