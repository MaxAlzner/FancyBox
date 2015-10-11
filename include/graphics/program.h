#ifndef FBOX_GLPROGRAM_H
#define FBOX_GLPROGRAM_H

namespace fbox
{
	namespace gl
	{

		class FBOXAPI Program
		{
		public:

			typedef GLuint handleType;

			Program() : _handle(0), _vertex(0), _fragment(0), _geometry(0) {}
			~Program() {}

			void vertex(Shader* shader);
			void fragment(Shader* shader);
			void geometry(Shader* shader);

			void activate();

			void link();
			void release();

			const handleType handle() const;

		protected:

			Shader* _vertex;
			Shader* _fragment;
			Shader* _geometry;
			handleType _handle;

		};

	}
}

#endif