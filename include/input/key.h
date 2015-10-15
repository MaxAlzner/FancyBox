#ifndef FBOX_KEY_H
#define FBOX_KEY_H

namespace fbox
{

	typedef enum KeyCode
	{
		KEY_UNKNOWN = 0,
		//KEY_BACKSPACE = 8,
		//KEY_TAB = 9,
		//KEY_CLEAR = 12,
		//KEY_ENTER = 13,
		//KEY_ESCAPE = 27,
		KEY_SPACE = 32,
		//KEY_EXCLAIM = 33,
		//KEY_QUOTEDBL = 34,
		//KEY_HASH = 35,
		//KEY_DOLLAR = 36,
		//KEY_AMPERSAND = 38,
		KEY_APOSTROPHE = 39,
		//KEY_LEFTPAREN = 40,
		//KEY_RIGHTPAREN = 41,
		//KEY_ASTERISK = 42,
		//KEY_PLUS = 43,
		KEY_COMMA = 44,
		KEY_MINUS = 45,
		KEY_PERIOD = 46,
		KEY_SLASH = 47,
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_4 = 52,
		KEY_5 = 53,
		KEY_6 = 54,
		KEY_7 = 55,
		KEY_8 = 56,
		KEY_9 = 57,
		//KEY_COLON = 58,
		KEY_SEMICOLON = 59,
		//KEY_LESS = 60,
		KEY_EQUALS = 61,
		//KEY_GREATER = 62,
		//KEY_QUESTION = 63,
		//KEY_AT = 64,
		KEY_A = 65,
		KEY_B = 66,
		KEY_C = 67,
		KEY_D = 68,
		KEY_E = 69,
		KEY_F = 70,
		KEY_G = 71,
		KEY_H = 72,
		KEY_I = 73,
		KEY_J = 74,
		KEY_K = 75,
		KEY_L = 76,
		KEY_M = 77,
		KEY_N = 78,
		KEY_O = 79,
		KEY_P = 80,
		KEY_Q = 81,
		KEY_R = 82,
		KEY_S = 83,
		KEY_T = 84,
		KEY_U = 85,
		KEY_V = 86,
		KEY_W = 87,
		KEY_X = 88,
		KEY_Y = 89,
		KEY_Z = 90,
		KEY_BRACKET_L = 91,
		KEY_BACKSLASH = 92,
		KEY_BRACKET_R = 93,
		//KEY_CARET = 94,
		//KEY_UNDERSCORE = 95,
		KEY_GRAVEACCENT = 96,
		//KEY_a                      = 97,
		//KEY_b                      = 98,
		//KEY_c                      = 99,
		//KEY_d                      = 100,
		//KEY_e                      = 101,
		//KEY_f                      = 102,
		//KEY_g                      = 103,
		//KEY_h                      = 104,
		//KEY_i                      = 105,
		//KEY_j                      = 106,
		//KEY_k                      = 107,
		//KEY_l                      = 108,
		//KEY_m                      = 109,
		//KEY_n                      = 110,
		//KEY_o                      = 111,
		//KEY_p                      = 112,
		//KEY_q                      = 113,
		//KEY_r                      = 114,
		//KEY_s                      = 115,
		//KEY_t                      = 116,
		//KEY_u                      = 117,
		//KEY_v                      = 118,
		//KEY_w                      = 119,
		//KEY_x                      = 120,
		//KEY_y                      = 121,
		//KEY_z                      = 122,
		//KEY_DELETE = 127,

		KEY_ESCAPE = 256,
		KEY_ENTER = 257,
		KEY_TAB = 258,
		KEY_BACKSPACE = 259,
		KEY_INSERT = 260,
		KEY_DELETE = 261,
		KEY_RIGHT = 262,
		KEY_LEFT = 263,
		KEY_DOWN = 264,
		KEY_UP = 265,
		KEY_PAGEUP = 266,
		KEY_PAGEDOWN = 267,
		KEY_HOME = 268,
		KEY_END = 269,
		KEY_CAPS_LOCK = 280,
		KEY_SCROLL_LOCK = 281,
		KEY_NUM_LOCK = 282,
		KEY_PRINT = 283,
		KEY_PAUSE = 284,

		KEY_F1 = 290,
		KEY_F2 = 291,
		KEY_F3 = 292,
		KEY_F4 = 293,
		KEY_F5 = 294,
		KEY_F6 = 295,
		KEY_F7 = 296,
		KEY_F8 = 297,
		KEY_F9 = 298,
		KEY_F10 = 299,
		KEY_F11 = 300,
		KEY_F12 = 301,
		KEY_F13 = 302,
		KEY_F14 = 303,
		KEY_F15 = 304,
		KEY_F16 = 305,
		KEY_F17 = 306,
		KEY_F18 = 307,
		KEY_F19 = 308,
		KEY_F20 = 309,
		KEY_F21 = 310,
		KEY_F22 = 311,
		KEY_F23 = 312,
		KEY_F24 = 313,
		KEY_F25 = 314,

		KEY_NUMPAD_0 = 320,
		KEY_NUMPAD_1 = 321,
		KEY_NUMPAD_2 = 322,
		KEY_NUMPAD_3 = 323,
		KEY_NUMPAD_4 = 324,
		KEY_NUMPAD_5 = 325,
		KEY_NUMPAD_6 = 326,
		KEY_NUMPAD_7 = 327,
		KEY_NUMPAD_8 = 328,
		KEY_NUMPAD_9 = 329,
		KEY_NUMPAD_DECIMAL = 330,
		KEY_NUMPAD_DIVIDE = 331,
		KEY_NUMPAD_MULTIPLY = 332,
		KEY_NUMPAD_MINUS = 333,
		KEY_NUMPAD_PLUS = 334,
		KEY_NUMPAD_ENTER = 335,
		KEY_NUMPAD_EQUALS = 336,

		KEY_SHIFT_L = 340,
		KEY_CTRL_L = 341,
		KEY_ALT_L = 342,
		KEY_SUPER_L = 343,
		KEY_SHIFT_R = 345,
		KEY_CTRL_R = 346,
		KEY_ALT_R = 347,
		KEY_SUPER_R = 348,
		KEY_MENU = 349,

	} KeyCode;

	typedef struct KeyboardState
	{

		inline KeyboardState()
		{
			memset(this->_keys, 0, sizeof(Button) * 360);
		}
		inline ~KeyboardState() {}

		inline Button& operator[](const unsigned char letter)
		{
			return this->_keys[letter];
		}
		inline Button& operator[](const int index)
		{
			return this->_keys[index % 360];
		}
		inline Button& operator[](const KeyCode code)
		{
			return this->_keys[code];
		}

		Button _keys[360];

	} KeyboardState;

}

#endif