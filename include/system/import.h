#ifndef FBOX_IMPORT_H
#define FBOX_IMPORT_H

namespace fbox
{

	class FBOXAPI Import
	{
	public:

		static void Read(String filepath);

	protected:

		static void ParseScene(XmlNode* node);
		static void ParseActor(XmlNode* node);

		static void ParseTransform(XmlNode* node, Transform* transform);
		static MeshFilter* ParseMesh(XmlNode* node);
		static TextureFilter* ParseTexture(XmlNode* node);
		static Material* ParseMaterial(XmlNode* node);
		static Behavior* ParseBehavior(XmlNode* node);
		static Camera* ParseCamera(XmlNode* node);
		static Light* ParseLight(XmlNode* node);

	};

}

#endif