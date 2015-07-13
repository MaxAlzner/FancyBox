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

		bool isEmpty() const;

		void update();
		void render();

		void add(Component* component);

		Component* findComponent(String type);

		String name;
		Transform* transform;
		MeshFilter* meshfilter;
		Material* material;
		Camera* camera;
		Light* light;
		List<Component*> components;
		List<TextureFilter*> texturefilters;
		List<Behavior*> behaviors;

	};

}

#endif