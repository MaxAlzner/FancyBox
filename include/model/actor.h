#ifndef FBOX_ACTOR_H
#define FBOX_ACTOR_H

namespace fbox
{

	class FBOXAPI Actor
	{
	public:

		inline Actor() :
			transform(0),
			material(0),
			camera(0),
			light(0) {}
		inline ~Actor() {}

		void build();
		void dispose();

		bool isEmpty() const;

		void add(Component* component);

		void attach(Mesh::Shape* shape);
		void attach(Image::Surface* surface, TextureFilter::TEXTURETYPE type);

		Component* findComponent(String type);

		Transform* transform;
		Material* material;
		Camera* camera;
		Light* light;
		List<Component*> components;

	};

}

#endif