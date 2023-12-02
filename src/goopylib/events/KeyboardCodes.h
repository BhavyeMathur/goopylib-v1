#pragma once

#if GP_USING_GLFW

constexpr int32_t GP_KEY_UNKNOWN (-1);

constexpr int32_t GP_KEY_SPACE = 32;
constexpr int32_t GP_KEY_APOSTROPHE = 39;
constexpr int32_t GP_KEY_COMMA = 44;
constexpr int32_t GP_KEY_MINUS = 45;
constexpr int32_t GP_KEY_PERIOD = 46;
constexpr int32_t GP_KEY_SLASH = 47;

constexpr int32_t GP_KEY_0 = 48;
constexpr int32_t GP_KEY_1 = 49;
constexpr int32_t GP_KEY_2 = 50;
constexpr int32_t GP_KEY_3 = 51;
constexpr int32_t GP_KEY_4 = 52;
constexpr int32_t GP_KEY_5 = 53;
constexpr int32_t GP_KEY_6 = 54;
constexpr int32_t GP_KEY_7 = 55;
constexpr int32_t GP_KEY_8 = 56;
constexpr int32_t GP_KEY_9 = 57;

constexpr int32_t GP_KEY_SEMICOLON = 59;
constexpr int32_t GP_KEY_EQUAL = 61;

constexpr int32_t GP_KEY_A = 65;
constexpr int32_t GP_KEY_B = 66;
constexpr int32_t GP_KEY_C = 67;
constexpr int32_t GP_KEY_D = 68;
constexpr int32_t GP_KEY_E = 69;
constexpr int32_t GP_KEY_F = 70;
constexpr int32_t GP_KEY_G = 71;
constexpr int32_t GP_KEY_H = 72;
constexpr int32_t GP_KEY_I = 73;
constexpr int32_t GP_KEY_J = 74;
constexpr int32_t GP_KEY_K = 75;
constexpr int32_t GP_KEY_L = 76;
constexpr int32_t GP_KEY_M = 77;
constexpr int32_t GP_KEY_N = 78;
constexpr int32_t GP_KEY_O = 79;
constexpr int32_t GP_KEY_P = 80;
constexpr int32_t GP_KEY_Q = 81;
constexpr int32_t GP_KEY_R = 82;
constexpr int32_t GP_KEY_S = 83;
constexpr int32_t GP_KEY_T = 84;
constexpr int32_t GP_KEY_U = 85;
constexpr int32_t GP_KEY_V = 86;
constexpr int32_t GP_KEY_W = 87;
constexpr int32_t GP_KEY_X = 88;
constexpr int32_t GP_KEY_Y = 89;
constexpr int32_t GP_KEY_Z = 90;

constexpr int32_t GP_KEY_LEFT_BRACKET = 91;
constexpr int32_t GP_KEY_RIGHT_BRACKET = 93;
constexpr int32_t GP_KEY_BACKSLASH = 92;
constexpr int32_t GP_KEY_GRAVE_ACCENT = 96;

constexpr int32_t GP_KEY_WORLD_1 = 161;
constexpr int32_t GP_KEY_WORLD_2 = 162;

constexpr int32_t GP_KEY_ESCAPE = 256;
constexpr int32_t GP_KEY_ENTER = 257;
constexpr int32_t GP_KEY_TAB = 258;
constexpr int32_t GP_KEY_BACKSPACE = 259;
constexpr int32_t GP_KEY_INSERT = 260;
constexpr int32_t GP_KEY_DELETE = 261;

constexpr int32_t GP_KEY_RIGHT = 262;
constexpr int32_t GP_KEY_LEFT = 263;
constexpr int32_t GP_KEY_DOWN = 264;
constexpr int32_t GP_KEY_UP = 265;

constexpr int32_t GP_KEY_PAGE_UP = 266;
constexpr int32_t GP_KEY_PAGE_DOWN = 267;

constexpr int32_t GP_KEY_HOME = 268;
constexpr int32_t GP_KEY_END = 269;

constexpr int32_t GP_KEY_CAPS_LOCK = 280;
constexpr int32_t GP_KEY_SCROLL_LOCK = 281;
constexpr int32_t GP_KEY_NUM_LOCK = 282;
constexpr int32_t GP_KEY_PRINT_SCREEN = 283;
constexpr int32_t GP_KEY_PAUSE = 284;

constexpr int32_t GP_KEY_F1 = 290;
constexpr int32_t GP_KEY_F2 = 291;
constexpr int32_t GP_KEY_F3 = 292;
constexpr int32_t GP_KEY_F4 = 293;
constexpr int32_t GP_KEY_F5 = 294;
constexpr int32_t GP_KEY_F6 = 295;
constexpr int32_t GP_KEY_F7 = 296;
constexpr int32_t GP_KEY_F8 = 297;
constexpr int32_t GP_KEY_F9 = 298;
constexpr int32_t GP_KEY_F10 = 299;
constexpr int32_t GP_KEY_F11 = 300;
constexpr int32_t GP_KEY_F12 = 301;
constexpr int32_t GP_KEY_F13 = 302;
constexpr int32_t GP_KEY_F14 = 303;
constexpr int32_t GP_KEY_F15 = 304;
constexpr int32_t GP_KEY_F16 = 305;
constexpr int32_t GP_KEY_F17 = 306;
constexpr int32_t GP_KEY_F18 = 307;
constexpr int32_t GP_KEY_F19 = 308;
constexpr int32_t GP_KEY_F20 = 309;
constexpr int32_t GP_KEY_F21 = 310;
constexpr int32_t GP_KEY_F22 = 311;
constexpr int32_t GP_KEY_F23 = 312;
constexpr int32_t GP_KEY_F24 = 313;
constexpr int32_t GP_KEY_F25 = 314;

constexpr int32_t GP_KEY_KP_0 = 320;
constexpr int32_t GP_KEY_KP_1 = 321;
constexpr int32_t GP_KEY_KP_2 = 322;
constexpr int32_t GP_KEY_KP_3 = 323;
constexpr int32_t GP_KEY_KP_4 = 324;
constexpr int32_t GP_KEY_KP_5 = 325;
constexpr int32_t GP_KEY_KP_6 = 326;
constexpr int32_t GP_KEY_KP_7 = 327;
constexpr int32_t GP_KEY_KP_8 = 328;
constexpr int32_t GP_KEY_KP_9 = 329;

constexpr int32_t GP_KEY_KP_DECIMAL = 330;
constexpr int32_t GP_KEY_KP_DIVIDE = 331;
constexpr int32_t GP_KEY_KP_MULTIPLY = 332;
constexpr int32_t GP_KEY_KP_SUBTRACT = 333;
constexpr int32_t GP_KEY_KP_ADD = 334;
constexpr int32_t GP_KEY_KP_ENTER = 335;
constexpr int32_t GP_KEY_KP_EQUAL = 336;

constexpr int32_t GP_KEY_LEFT_CONTROL = 341;
constexpr int32_t GP_KEY_LEFT_ALT = 342;
constexpr int32_t GP_KEY_LEFT_SUPER = 343;

constexpr int32_t GP_KEY_RIGHT_SHIFT = 344;
constexpr int32_t GP_KEY_RIGHT_CONTROL = 345;
constexpr int32_t GP_KEY_RIGHT_ALT = 346;
constexpr int32_t GP_KEY_RIGHT_SUPER = 347;

constexpr int32_t GP_KEY_MENU = 348;

#endif
