#ifndef FBOX_SCRIPTMANAGER_H
#define FBOX_SCRIPTMANAGER_H
	
namespace fbox
{
	namespace js
	{

		class FBOXAPI Manager
		{
		public:

			static void Initialize();
			static void Dispose();

			static Object Global();

			static void Register(string& filepath);
			static void Execute(string& command);

			static bool Started();

			static v8::Isolate* Isolate;

		protected:

			static v8::Local<v8::Context> Context;

		};

	}
}

#endif