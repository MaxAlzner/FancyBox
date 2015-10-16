
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{
	
	FBOXAPI void OnLoad()
	{
		Uniforms.resize(32);
		UniformBlocks.resize(16);
		VertexArrays.resize(64);
		Textures.resize(64);

		VertexProgram = new gl::Shader(gl::Shader::TYPE_VERTEX);
		FragmentProgram = new gl::Shader(gl::Shader::TYPE_FRAGMENT);
		MainProgram = new gl::Program;
		MainProgram->vertex(VertexProgram);
		MainProgram->fragment(FragmentProgram);
		MainScene = new Scene;
	}
	FBOXAPI void OnUnload()
	{
		MainScene->dispose();
		delete MainScene;
		MainScene = 0;
		MainProgram->release();
		delete MainProgram;
		MainProgram = 0;
		FragmentProgram->release();
		delete FragmentProgram;
		FragmentProgram = 0;
		VertexProgram->release();
		delete VertexProgram;
		VertexProgram = 0;

		for (uint i = 0; i < Textures.size(); i++)
		{
			gl::Texture* texture = Textures[i];
			if (texture != 0)
			{
				texture->release();
				delete texture;
			}
		}

		for (uint i = 0; i < VertexArrays.size(); i++)
		{
			gl::VertexArray* vao = VertexArrays[i];
			if (vao != 0)
			{
				vao->release();
				delete vao;
			}
		}

		for (uint i = 0; i < UniformBlocks.size(); i++)
		{
			gl::UniformBlock* uniform = UniformBlocks[i];
			if (uniform != 0)
			{
				uniform->release();
				delete uniform;
			}
		}

		for (uint i = 0; i < Uniforms.size(); i++)
		{
			gl::Uniform* uniform = Uniforms[i];
			if (uniform != 0)
			{
				delete uniform;
			}
		}

		Textures.clear();
		VertexArrays.clear();
		UniformBlocks.clear();
		Uniforms.clear();
	}

	FBOXAPI void OnInitialize()
	{
		js::Manager::Initialize();
		FreeImage_Initialise();

		if (glewInit() != GLEW_OK)
		{
			exit(1);
		}

		if (!GLEW_VERSION_3_0)
		{
			exit(1);
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);

		VertexProgram->compile("base.vert");
		FragmentProgram->compile("base.frag");
		MainProgram->link();
		MainProgram->activate();
		GrabUniforms();

#if 0
		const int filterSize = 32 * 2;
		float* randoms = new float[filterSize];
		for (int i = 0; i < filterSize; i += 2)
		{
			float theta = random::scalar() * PI * 2.0f;
			float r = random::scalar();
			randoms[i + 0] = cos(theta) * r;
			randoms[i + 1] = sin(theta) * r;
		}
		GetUniform(UNIFORM_FLAG_FILTER_RANDOM)->bind2fv((const vec2*)randoms, filterSize / 2);
		delete[] randoms;
#endif

		js::Object global = js::Manager::Global();
		js::Object mouse;
		mouse.accessor("position", &Input.Mouse.position);
		mouse.accessor("scroll", "number", &Input.Mouse.scroll, sizeof(float), false);
		mouse.accessor("left", "boolean", &Input.Mouse.left, sizeof(bool), false);
		mouse.accessor("middle", "boolean", &Input.Mouse.middle, sizeof(bool), false);
		mouse.accessor("right", "boolean", &Input.Mouse.right, sizeof(bool), false);
		mouse.accessor("active", "boolean", &Input.Mouse.active, sizeof(bool), false);
		global.accessor("Mouse", mouse);
		js::Object key;
		key.accessor("space", "boolean", &Input.Key[KEY_SPACE], sizeof(bool), false);
		key.accessor("apostrophe", "boolean", &Input.Key[KEY_APOSTROPHE], sizeof(bool), false);
		key.accessor("comma", "boolean", &Input.Key[KEY_COMMA], sizeof(bool), false);
		key.accessor("minus", "boolean", &Input.Key[KEY_MINUS], sizeof(bool), false);
		key.accessor("period", "boolean", &Input.Key[KEY_PERIOD], sizeof(bool), false);
		key.accessor("slash", "boolean", &Input.Key[KEY_SLASH], sizeof(bool), false);
		key.accessor("0", "boolean", &Input.Key[KEY_0], sizeof(bool), false);
		key.accessor("1", "boolean", &Input.Key[KEY_1], sizeof(bool), false);
		key.accessor("2", "boolean", &Input.Key[KEY_2], sizeof(bool), false);
		key.accessor("3", "boolean", &Input.Key[KEY_3], sizeof(bool), false);
		key.accessor("4", "boolean", &Input.Key[KEY_4], sizeof(bool), false);
		key.accessor("5", "boolean", &Input.Key[KEY_5], sizeof(bool), false);
		key.accessor("6", "boolean", &Input.Key[KEY_6], sizeof(bool), false);
		key.accessor("7", "boolean", &Input.Key[KEY_7], sizeof(bool), false);
		key.accessor("8", "boolean", &Input.Key[KEY_8], sizeof(bool), false);
		key.accessor("9", "boolean", &Input.Key[KEY_9], sizeof(bool), false);
		key.accessor("semicolon", "boolean", &Input.Key[KEY_SEMICOLON], sizeof(bool), false);
		key.accessor("equals", "boolean", &Input.Key[KEY_EQUALS], sizeof(bool), false);
		key.accessor("a", "boolean", &Input.Key[KEY_A], sizeof(bool), false);
		key.accessor("b", "boolean", &Input.Key[KEY_B], sizeof(bool), false);
		key.accessor("c", "boolean", &Input.Key[KEY_C], sizeof(bool), false);
		key.accessor("d", "boolean", &Input.Key[KEY_D], sizeof(bool), false);
		key.accessor("e", "boolean", &Input.Key[KEY_E], sizeof(bool), false);
		key.accessor("f", "boolean", &Input.Key[KEY_F], sizeof(bool), false);
		key.accessor("g", "boolean", &Input.Key[KEY_G], sizeof(bool), false);
		key.accessor("h", "boolean", &Input.Key[KEY_H], sizeof(bool), false);
		key.accessor("i", "boolean", &Input.Key[KEY_I], sizeof(bool), false);
		key.accessor("j", "boolean", &Input.Key[KEY_J], sizeof(bool), false);
		key.accessor("k", "boolean", &Input.Key[KEY_K], sizeof(bool), false);
		key.accessor("l", "boolean", &Input.Key[KEY_L], sizeof(bool), false);
		key.accessor("m", "boolean", &Input.Key[KEY_M], sizeof(bool), false);
		key.accessor("n", "boolean", &Input.Key[KEY_N], sizeof(bool), false);
		key.accessor("o", "boolean", &Input.Key[KEY_O], sizeof(bool), false);
		key.accessor("p", "boolean", &Input.Key[KEY_P], sizeof(bool), false);
		key.accessor("q", "boolean", &Input.Key[KEY_Q], sizeof(bool), false);
		key.accessor("r", "boolean", &Input.Key[KEY_R], sizeof(bool), false);
		key.accessor("s", "boolean", &Input.Key[KEY_S], sizeof(bool), false);
		key.accessor("t", "boolean", &Input.Key[KEY_T], sizeof(bool), false);
		key.accessor("u", "boolean", &Input.Key[KEY_U], sizeof(bool), false);
		key.accessor("v", "boolean", &Input.Key[KEY_V], sizeof(bool), false);
		key.accessor("w", "boolean", &Input.Key[KEY_W], sizeof(bool), false);
		key.accessor("x", "boolean", &Input.Key[KEY_X], sizeof(bool), false);
		key.accessor("y", "boolean", &Input.Key[KEY_Y], sizeof(bool), false);
		key.accessor("z", "boolean", &Input.Key[KEY_Z], sizeof(bool), false);
		key.accessor("bracketleft", "boolean", &Input.Key[KEY_BRACKET_L], sizeof(bool), false);
		key.accessor("bracketright", "boolean", &Input.Key[KEY_BRACKET_R], sizeof(bool), false);
		key.accessor("backslash", "boolean", &Input.Key[KEY_BACKSLASH], sizeof(bool), false);
		key.accessor("graveaccent", "boolean", &Input.Key[KEY_GRAVEACCENT], sizeof(bool), false);
		key.accessor("escape", "boolean", &Input.Key[KEY_ESCAPE], sizeof(bool), false);
		key.accessor("enter", "boolean", &Input.Key[KEY_ENTER], sizeof(bool), false);
		key.accessor("tab", "boolean", &Input.Key[KEY_TAB], sizeof(bool), false);
		key.accessor("backspace", "boolean", &Input.Key[KEY_BACKSPACE], sizeof(bool), false);
		key.accessor("insert", "boolean", &Input.Key[KEY_INSERT], sizeof(bool), false);
		key.accessor("delete", "boolean", &Input.Key[KEY_DELETE], sizeof(bool), false);
		key.accessor("right", "boolean", &Input.Key[KEY_RIGHT], sizeof(bool), false);
		key.accessor("left", "boolean", &Input.Key[KEY_LEFT], sizeof(bool), false);
		key.accessor("down", "boolean", &Input.Key[KEY_DOWN], sizeof(bool), false);
		key.accessor("up", "boolean", &Input.Key[KEY_UP], sizeof(bool), false);
		key.accessor("pageup", "boolean", &Input.Key[KEY_PAGEUP], sizeof(bool), false);
		key.accessor("pagedown", "boolean", &Input.Key[KEY_PAGEDOWN], sizeof(bool), false);
		key.accessor("home", "boolean", &Input.Key[KEY_HOME], sizeof(bool), false);
		key.accessor("end", "boolean", &Input.Key[KEY_END], sizeof(bool), false);
		key.accessor("caps lock", "boolean", &Input.Key[KEY_CAPS_LOCK], sizeof(bool), false);
		key.accessor("scroll lock", "boolean", &Input.Key[KEY_SCROLL_LOCK], sizeof(bool), false);
		key.accessor("num lock", "boolean", &Input.Key[KEY_NUM_LOCK], sizeof(bool), false);
		key.accessor("print", "boolean", &Input.Key[KEY_PRINT], sizeof(bool), false);
		key.accessor("pause", "boolean", &Input.Key[KEY_PAUSE], sizeof(bool), false);
		key.accessor("f1", "boolean", &Input.Key[KEY_F1], sizeof(bool), false);
		key.accessor("f2", "boolean", &Input.Key[KEY_F2], sizeof(bool), false);
		key.accessor("f3", "boolean", &Input.Key[KEY_F3], sizeof(bool), false);
		key.accessor("f4", "boolean", &Input.Key[KEY_F4], sizeof(bool), false);
		key.accessor("f5", "boolean", &Input.Key[KEY_F5], sizeof(bool), false);
		key.accessor("f6", "boolean", &Input.Key[KEY_F6], sizeof(bool), false);
		key.accessor("f7", "boolean", &Input.Key[KEY_F7], sizeof(bool), false);
		key.accessor("f8", "boolean", &Input.Key[KEY_F8], sizeof(bool), false);
		key.accessor("f9", "boolean", &Input.Key[KEY_F9], sizeof(bool), false);
		key.accessor("f10", "boolean", &Input.Key[KEY_F10], sizeof(bool), false);
		key.accessor("f11", "boolean", &Input.Key[KEY_F11], sizeof(bool), false);
		key.accessor("f12", "boolean", &Input.Key[KEY_F12], sizeof(bool), false);
		key.accessor("f13", "boolean", &Input.Key[KEY_F13], sizeof(bool), false);
		key.accessor("f14", "boolean", &Input.Key[KEY_F14], sizeof(bool), false);
		key.accessor("f15", "boolean", &Input.Key[KEY_F15], sizeof(bool), false);
		key.accessor("f16", "boolean", &Input.Key[KEY_F16], sizeof(bool), false);
		key.accessor("f17", "boolean", &Input.Key[KEY_F17], sizeof(bool), false);
		key.accessor("f18", "boolean", &Input.Key[KEY_F18], sizeof(bool), false);
		key.accessor("f19", "boolean", &Input.Key[KEY_F19], sizeof(bool), false);
		key.accessor("f20", "boolean", &Input.Key[KEY_F20], sizeof(bool), false);
		key.accessor("f21", "boolean", &Input.Key[KEY_F21], sizeof(bool), false);
		key.accessor("f22", "boolean", &Input.Key[KEY_F22], sizeof(bool), false);
		key.accessor("f23", "boolean", &Input.Key[KEY_F23], sizeof(bool), false);
		key.accessor("f24", "boolean", &Input.Key[KEY_F24], sizeof(bool), false);
		key.accessor("f25", "boolean", &Input.Key[KEY_F25], sizeof(bool), false);
		js::Object numpad;
		numpad.accessor("0", "boolean", &Input.Key[KEY_0], sizeof(bool), false);
		numpad.accessor("1", "boolean", &Input.Key[KEY_1], sizeof(bool), false);
		numpad.accessor("2", "boolean", &Input.Key[KEY_2], sizeof(bool), false);
		numpad.accessor("3", "boolean", &Input.Key[KEY_3], sizeof(bool), false);
		numpad.accessor("4", "boolean", &Input.Key[KEY_4], sizeof(bool), false);
		numpad.accessor("5", "boolean", &Input.Key[KEY_5], sizeof(bool), false);
		numpad.accessor("6", "boolean", &Input.Key[KEY_6], sizeof(bool), false);
		numpad.accessor("7", "boolean", &Input.Key[KEY_7], sizeof(bool), false);
		numpad.accessor("8", "boolean", &Input.Key[KEY_8], sizeof(bool), false);
		numpad.accessor("9", "boolean", &Input.Key[KEY_9], sizeof(bool), false);
		numpad.accessor("decimal", "boolean", &Input.Key[KEY_0], sizeof(bool), false);
		numpad.accessor("divide", "boolean", &Input.Key[KEY_1], sizeof(bool), false);
		numpad.accessor("multiply", "boolean", &Input.Key[KEY_2], sizeof(bool), false);
		numpad.accessor("minus", "boolean", &Input.Key[KEY_3], sizeof(bool), false);
		numpad.accessor("plus", "boolean", &Input.Key[KEY_4], sizeof(bool), false);
		numpad.accessor("enter", "boolean", &Input.Key[KEY_5], sizeof(bool), false);
		numpad.accessor("equals", "boolean", &Input.Key[KEY_6], sizeof(bool), false);
		key.accessor("numpad", numpad);
		key.accessor("shift left", "boolean", &Input.Key[KEY_SHIFT_L], sizeof(bool), false);
		key.accessor("ctrl left", "boolean", &Input.Key[KEY_CTRL_L], sizeof(bool), false);
		key.accessor("alt left", "boolean", &Input.Key[KEY_ALT_L], sizeof(bool), false);
		key.accessor("super left", "boolean", &Input.Key[KEY_SUPER_L], sizeof(bool), false);
		key.accessor("shift right", "boolean", &Input.Key[KEY_SHIFT_R], sizeof(bool), false);
		key.accessor("ctrl right", "boolean", &Input.Key[KEY_CTRL_R], sizeof(bool), false);
		key.accessor("alt right", "boolean", &Input.Key[KEY_ALT_R], sizeof(bool), false);
		key.accessor("super right", "boolean", &Input.Key[KEY_SUPER_R], sizeof(bool), false);
		key.accessor("menu", "boolean", &Input.Key[KEY_MENU], sizeof(bool), false);
		global.accessor("Key", key);
		js::Object gamepad;
		gamepad.accessor("a", "boolean", &Input.Gamepad.a, sizeof(bool), false);
		gamepad.accessor("b", "boolean", &Input.Gamepad.b, sizeof(bool), false);
		gamepad.accessor("x", "boolean", &Input.Gamepad.x, sizeof(bool), false);
		gamepad.accessor("y", "boolean", &Input.Gamepad.y, sizeof(bool), false);
		js::Object bumpers;
		bumpers.accessor("left", "boolean", &Input.Gamepad.bumperLeft, sizeof(bool), false);
		bumpers.accessor("right", "boolean", &Input.Gamepad.bumperRight, sizeof(bool), false);
		gamepad.accessor("bumpers", bumpers);
		js::Object sticks;
		js::Object leftStick;
		leftStick.accessor("x", "number", &Input.Gamepad.stickLeft.x, sizeof(float), false);
		leftStick.accessor("y", "number", &Input.Gamepad.stickLeft.y, sizeof(float), false);
		leftStick.accessor("pressed", "boolean", &Input.Gamepad.stickButtonLeft, sizeof(bool), false);
		sticks.accessor("left", leftStick);
		js::Object rightStick;
		rightStick.accessor("x", "number", &Input.Gamepad.stickRight.x, sizeof(float), false);
		rightStick.accessor("y", "number", &Input.Gamepad.stickRight.y, sizeof(float), false);
		rightStick.accessor("pressed", "boolean", &Input.Gamepad.stickButtonRight, sizeof(bool), false);
		sticks.accessor("right", rightStick);
		gamepad.accessor("sticks", sticks);
		gamepad.accessor("back", "boolean", &Input.Gamepad.back, sizeof(bool), false);
		gamepad.accessor("start", "boolean", &Input.Gamepad.start, sizeof(bool), false);
		gamepad.accessor("connected", "boolean", &Input.Gamepad.a, sizeof(bool), false);
		gamepad.accessor("user", "int32", &Input.Gamepad.a, sizeof(int), false);
		global.accessor("Gamepad", gamepad);
		js::Object frame;
		frame.accessor("count", "int32", &Frame::Count, sizeof(Frame::frameValue), false);
		frame.accessor("current", "int32", &Frame::Current, sizeof(Frame::frameValue), false);
		frame.accessor("rate", "int32", &Frame::Rate, sizeof(Frame::frameValue), false);
		frame.accessor("fixedTime", "number", &Frame::FixedTime, sizeof(Frame::timeValue), false);
		frame.accessor("deltaTime", "number", &Frame::DeltaTime, sizeof(Frame::timeValue), false);
		global.accessor("Frame", frame);
	}
	FBOXAPI void OnDispose()
	{
		ReleaseAssets();
		FreeImage_DeInitialise();
		js::Manager::Dispose();
	}

	FBOXAPI void OnReshape(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	FBOXAPI void OnStart()
	{
#if 0
		js::Object global = js::Manager::Global();
		js::Array globals = global.properties();
		for (int i = 0; i < globals.count(); i++)
		{
			printf(" %d ). %s : %s\n", i + 1, (const char*)globals.gets(i).data(), (const char*)global.typeof(globals.gets(i)).data());
			js::Object property = global.get(globals.gets(i).data());
			js::Array props = property.properties();
			for (int k = 0; k < props.count(); k++)
			{
				printf("   %d ). %s : %s\n", k + 1, (const char*)props.gets(k).data(), (const char*)property.typeof(props.gets(k)).data());
			}
		}

#endif
		if (MainScene != 0)
		{
			MainScene->start();
		}
	}
	FBOXAPI void OnUpdate()
	{
		if (Input.Key[KEY_SPACE])
		{
			VertexProgram->compile("base.vert");
			FragmentProgram->compile("base.frag");
			MainProgram->link();
			MainProgram->activate();
		}

		if (MainScene != 0)
		{
			MainScene->update();
		}
	}
	FBOXAPI void OnDraw()
	{
		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (MainScene != 0)
		{
			MainScene->render();
		}
	}

}