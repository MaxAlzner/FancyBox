#ifndef FBOX_SCRIPTFUNCTIONPARAMETERS_H
#define FBOX_SCRIPTFUNCTIONPARAMETERS_H
	
namespace fbox
{
	namespace js
	{

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

	}
}

#endif