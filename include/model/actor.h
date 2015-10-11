#ifndef FBOX_ACTOR_H
#define FBOX_ACTOR_H

namespace fbox
{

	class FBOXAPI Actor
	{
	public:

		inline Actor() :
			transform(0),
			meshfilter(0),
			material(0),
			camera(0),
			light(0)
		{
			this->add(new Transform);
		}
		inline ~Actor() {}

		void dispose();

		bool empty() const;

		void start();
		void update();
		void render();

		void add(Component* component);

		Component* findComponent(string& type);
		Component* findComponent(const char* type);

		string name;
		Transform* transform;
		MeshFilter* meshfilter;
		Material* material;
		Camera* camera;
		Light* light;
		std::list<Component*> components;
		std::list<TextureFilter*> texturefilters;
		std::list<Behavior*> behaviors;

	};

}

#endif