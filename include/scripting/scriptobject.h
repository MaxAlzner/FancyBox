#ifndef FBOX_SCRIPTOBJECT_H
#define FBOX_SCRIPTOBJECT_H
	
namespace fbox
{

	class FBOXAPI ScriptObject : public ScriptEntity
	{
	public:

		inline ScriptObject() : ScriptEntity(), _state(0) {}
		inline ScriptObject(ScriptManager* manager);
		inline ScriptObject(ScriptManager* manager, v8::Handle<v8::Object>& object);
		inline ~ScriptObject();

		void set(String key, String value);
		void set(String key, __int32 value);
		void set(String key, bool value);
		void set(String key, float value);
		void set(String key, double value);
		void set(String key, ScriptObject& object);
		void set(String key, ScriptArray& object);

		String gets(String key);
		__int32 geti(String key);
		bool getb(String key);
		float getf(String key);
		double getd(String key);
		ScriptObject get(String key);
		ScriptArray getarr(String key);

		void call(String name);
		void call(String name, ScriptObject& parameter);
		void call(String name, ScriptParameters& parameters);

		ScriptObject construct(String name);
		ScriptObject construct(String name, ScriptObject& parameter);
		ScriptObject construct(String name, ScriptParameters& parameters);

		String typeof(String key) const;
		ScriptArray properties() const;

		void operator=(v8::Handle<v8::Object>& object);
		operator v8::Handle<v8::Object>() const;
		operator v8::Handle<v8::Value>() const;

	protected:

		v8::Handle<v8::Object>* _state;

	};

}

#endif