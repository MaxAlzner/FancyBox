#ifndef FBOX_PROGRAM_H
#define FBOX_PROGRAM_H

namespace fbox
{
	class FBOXAPI GlProgram
	{
	public:

		typedef GLuint handleType;

		GlProgram() : _handle(0), _vertex(0), _fragment(0), _geometry(0) {}
		~GlProgram() {}

		void vertex(GlShader* shader);
		void fragment(GlShader* shader);
		void geometry(GlShader* shader);

		void activate();

		void link();
		void release();

		const handleType handle() const;

	protected:

		GlShader* _vertex;
		GlShader* _fragment;
		GlShader* _geometry;
		handleType _handle;

	};

}

#endif