#ifndef FBOX_SCRIPTARFBOX_H
#define FBOX_SCRIPTARFBOX_H
	
namespace fbox
{

	class FBOXAPI ScriptArray : public ScriptEntity
	{
	public:

		inline ScriptArray() : ScriptEntity(), _state(0) {}
		ScriptArray(ScriptManager* manager);
		ScriptArray(ScriptManager* manager, const int length);
		ScriptArray(ScriptManager* manager, v8::Handle<v8::Array>& source);
		~ScriptArray();

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
		__int32 geti(const int index);
		bool getb(const int index);
		float getf(const int index);
		double getd(const int index);
		ScriptObject get(const int index);
		ScriptArray getarr(const int index);

		String typeof(const int index) const;

		const int count() const;

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

	protected:

		v8::Handle<v8::Array>* _state;

	};

}

#endif