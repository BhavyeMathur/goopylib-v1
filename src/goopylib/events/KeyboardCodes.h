#pragma once

#if GP_USING_GLFW

constexpr uint32_t GP_KEY_UNKNOWN (-1);

constexpr uint32_t GP_KEY_SPACE = 32;
constexpr uint32_t GP_KEY_APOSTROPHE = 39;
constexpr uint32_t GP_KEY_COMMA = 44;
constexpr uint32_t GP_KEY_MINUS = 45;
constexpr uint32_t GP_KEY_PERIOD = 46;
constexpr uint32_t GP_KEY_SLASH = 47;

constexpr uint32_t GP_KEY_0 = 48;
constexpr uint32_t GP_KEY_1 = 49;
constexpr uint32_t GP_KEY_2 = 50;
constexpr uint32_t GP_KEY_3 = 51;
constexpr uint32_t GP_KEY_4 = 52;
constexpr uint32_t GP_KEY_5 = 53;
constexpr uint32_t GP_KEY_6 = 54;
constexpr uint32_t GP_KEY_7 = 55;
constexpr uint32_t GP_KEY_8 = 56;
constexpr uint32_t GP_KEY_9 = 57;

constexpr uint32_t GP_KEY_SEMICOLON = 59;
constexpr uint32_t GP_KEY_EQUAL = 61;

constexpr uint32_t GP_KEY_A = 65;
constexpr uint32_t GP_KEY_B = 66;
constexpr uint32_t GP_KEY_C = 67;
constexpr uint32_t GP_KEY_D = 68;
constexpr uint32_t GP_KEY_E = 69;
constexpr uint32_t GP_KEY_F = 70;
constexpr uint32_t GP_KEY_G = 71;
constexpr uint32_t GP_KEY_H = 72;
constexpr uint32_t GP_KEY_I = 73;
constexpr uint32_t GP_KEY_J = 74;
constexpr uint32_t GP_KEY_K = 75;
constexpr uint32_t GP_KEY_L = 76;
constexpr uint32_t GP_KEY_M = 77;
constexpr uint32_t GP_KEY_N = 78;
constexpr uint32_t GP_KEY_O = 79;
constexpr uint32_t GP_KEY_P = 80;
constexpr uint32_t GP_KEY_Q = 81;
constexpr uint32_t GP_KEY_R = 82;
constexpr uint32_t GP_KEY_S = 83;
constexpr uint32_t GP_KEY_T = 84;
constexpr uint32_t GP_KEY_U = 85;
constexpr uint32_t GP_KEY_V = 86;
constexpr uint32_t GP_KEY_W = 87;
constexpr uint32_t GP_KEY_X = 88;
constexpr uint32_t GP_KEY_Y = 89;
constexpr uint32_t GP_KEY_Z = 90;

constexpr uint32_t GP_KEY_LEFT_BRACKET = 91;
constexpr uint32_t GP_KEY_RIGHT_BRACKET = 93;
constexpr uint32_t GP_KEY_BACKSLASH = 92;
constexpr uint32_t GP_KEY_GRAVE_ACCENT = 96;

constexpr uint32_t GP_KEY_WORLD_1 = 161;
constexpr uint32_t GP_KEY_WORLD_2 = 162;

constexpr uint32_t GP_KEY_ESCAPE = 256;
constexpr uint32_t GP_KEY_ENTER = 257;
constexpr uint32_t GP_KEY_TAB = 258;
constexpr uint32_t GP_KEY_BACKSPACE = 259;
constexpr uint32_t GP_KEY_INSERT = 260;
constexpr uint32_t GP_KEY_DELETE = 261;

constexpr uint32_t GP_KEY_RIGHT = 262;
constexpr uint32_t GP_KEY_LEFT = 263;
constexpr uint32_t GP_KEY_DOWN = 264;
constexpr uint32_t GP_KEY_UP = 265;

constexpr uint32_t GP_KEY_PAGE_UP = 266;
constexpr uint32_t GP_KEY_PAGE_DOWN = 267;

constexpr uint32_t GP_KEY_HOME = 268;
constexpr uint32_t GP_KEY_END = 269;

constexpr uint32_t GP_KEY_CAPS_LOCK = 280;
constexpr uint32_t GP_KEY_SCROLL_LOCK = 281;
constexpr uint32_t GP_KEY_NUM_LOCK = 282;
constexpr uint32_t GP_KEY_PRINT_SCREEN = 283;
constexpr uint32_t GP_KEY_PAUSE = 284;

constexpr uint32_t GP_KEY_F1 = 290;
constexpr uint32_t GP_KEY_F2 = 291;
constexpr uint32_t GP_KEY_F3 = 292;
constexpr uint32_t GP_KEY_F4 = 293;
constexpr uint32_t GP_KEY_F5 = 294;
constexpr uint32_t GP_KEY_F6 = 295;
constexpr uint32_t GP_KEY_F7 = 296;
constexpr uint32_t GP_KEY_F8 = 297;
constexpr uint32_t GP_KEY_F9 = 298;
constexpr uint32_t GP_KEY_F10 = 299;
constexpr uint32_t GP_KEY_F11 = 300;
constexpr uint32_t GP_KEY_F12 = 301;
constexpr uint32_t GP_KEY_F13 = 302;
constexpr uint32_t GP_KEY_F14 = 303;
constexpr uint32_t GP_KEY_F15 = 304;
constexpr uint32_t GP_KEY_F16 = 305;
constexpr uint32_t GP_KEY_F17 = 306;
constexpr uint32_t GP_KEY_F18 = 307;
constexpr uint32_t GP_KEY_F19 = 308;
constexpr uint32_t GP_KEY_F20 = 309;
constexpr uint32_t GP_KEY_F21 = 310;
constexpr uint32_t GP_KEY_F22 = 311;
constexpr uint32_t GP_KEY_F23 = 312;
constexpr uint32_t GP_KEY_F24 = 313;
constexpr uint32_t GP_KEY_F25 = 314;

constexpr uint32_t GP_KEY_KP_0 = 320;
constexpr uint32_t GP_KEY_KP_1 = 321;
constexpr uint32_t GP_KEY_KP_2 = 322;
constexpr uint32_t GP_KEY_KP_3 = 323;
constexpr uint32_t GP_KEY_KP_4 = 324;
constexpr uint32_t GP_KEY_KP_5 = 325;
constexpr uint32_t GP_KEY_KP_6 = 326;
constexpr uint32_t GP_KEY_KP_7 = 327;
constexpr uint32_t GP_KEY_KP_8 = 328;
constexpr uint32_t GP_KEY_KP_9 = 329;

constexpr uint32_t GP_KEY_KP_DECIMAL = 330;
constexpr uint32_t GP_KEY_KP_DIVIDE = 331;
constexpr uint32_t GP_KEY_KP_MULTIPLY = 332;
constexpr uint32_t GP_KEY_KP_SUBTRACT = 333;
constexpr uint32_t GP_KEY_KP_ADD = 334;
constexpr uint32_t GP_KEY_KP_ENTER = 335;
constexpr uint32_t GP_KEY_KP_EQUAL = 336;

constexpr uint32_t GP_KEY_LEFT_CONTROL = 341;
constexpr uint32_t GP_KEY_LEFT_ALT = 342;
constexpr uint32_t GP_KEY_LEFT_SUPER = 343;

constexpr uint32_t GP_KEY_RIGHT_SHIFT = 344;
constexpr uint32_t GP_KEY_RIGHT_CONTROL = 345;
constexpr uint32_t GP_KEY_RIGHT_ALT = 346;
constexpr uint32_t GP_KEY_RIGHT_SUPER = 347;

constexpr uint32_t GP_KEY_MENU = 348;

#endif
