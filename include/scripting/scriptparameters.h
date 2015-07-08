#ifndef FBOX_SCRIPTPARAMETERS_H
#define FBOX_SCRIPTPARAMETERS_H
	
namespace fbox
{

	class FBOXAPI ScriptParameters
	{
	public:

		inline ScriptParameters() : _parameters(4) {}
		inline ~ScriptParameters() { this->_parameters.clear(); }

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

		const int count() const;

		operator v8::Handle<v8::Value>*() const;
		void operator+=(String value);
		void operator+=(__int32 value);
		void operator+=(bool value);
		void operator+=(float value);
		void operator+=(double value);
		void operator+=(ScriptObject& value);
		void operator+=(ScriptArray& value);

	protected:

		Array<v8::Handle<v8::Value>> _parameters;

	};

}

#endif