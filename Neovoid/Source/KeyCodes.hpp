#pragma once

#ifdef NEO_PLATFORM_WINDOWS
/*--------- Mouse Buttons ---------*/
#define NEO_MOUSE_BUTTON_1         0   // Left
#define NEO_MOUSE_BUTTON_2         1   // Right
#define NEO_MOUSE_BUTTON_3         2   // Middle
#define NEO_MOUSE_BUTTON_4         3   // X1
#define NEO_MOUSE_BUTTON_5         4   // X2
#define NEO_MOUSE_BUTTON_6         5
#define NEO_MOUSE_BUTTON_7         6
#define NEO_MOUSE_BUTTON_8         7
#define NEO_MOUSE_BUTTON_LAST      NEO_MOUSE_BUTTON_5
#define NEO_MOUSE_BUTTON_LEFT      NEO_MOUSE_BUTTON_1
#define NEO_MOUSE_BUTTON_RIGHT     NEO_MOUSE_BUTTON_2
#define NEO_MOUSE_BUTTON_MIDDLE    NEO_MOUSE_BUTTON_3

/*----------- Keyboard -----------*/
#define NEO_KEY_UNKNOWN            0
#define NEO_KEY_BACKSPACE          8
#define NEO_KEY_TAB                9
#define NEO_KEY_ENTER              13
#define NEO_KEY_SHIFT              16
#define NEO_KEY_CONTROL            17
#define NEO_KEY_ALT                18
#define NEO_KEY_PAUSE              19
#define NEO_KEY_CAPS_LOCK          20
#define NEO_KEY_ESCAPE             27
#define NEO_KEY_SPACE              32
#define NEO_KEY_PAGE_UP            33
#define NEO_KEY_PAGE_DOWN          34
#define NEO_KEY_END                35
#define NEO_KEY_HOME               36

/*----------- Arrow Keys ----------*/
#define NEO_KEY_LEFT               37
#define NEO_KEY_UP                 38
#define NEO_KEY_RIGHT              39
#define NEO_KEY_DOWN               40

/*---------- Editing Keys ---------*/
#define NEO_KEY_PRINT_SCREEN       44
#define NEO_KEY_INSERT             45
#define NEO_KEY_DELETE             46

/*---------- Number Keys ----------*/
#define NEO_KEY_0                  48
#define NEO_KEY_1                  49
#define NEO_KEY_2                  50
#define NEO_KEY_3                  51
#define NEO_KEY_4                  52
#define NEO_KEY_5                  53
#define NEO_KEY_6                  54
#define NEO_KEY_7                  55
#define NEO_KEY_8                  56
#define NEO_KEY_9                  57

/*------------ Letters ------------*/
#define NEO_KEY_A                  65
#define NEO_KEY_B                  66
#define NEO_KEY_C                  67
#define NEO_KEY_D                  68
#define NEO_KEY_E                  69
#define NEO_KEY_F                  70
#define NEO_KEY_G                  71
#define NEO_KEY_H                  72
#define NEO_KEY_I                  73
#define NEO_KEY_J                  74
#define NEO_KEY_K                  75
#define NEO_KEY_L                  76
#define NEO_KEY_M                  77
#define NEO_KEY_N                  78
#define NEO_KEY_O                  79
#define NEO_KEY_P                  80
#define NEO_KEY_Q                  81
#define NEO_KEY_R                  82
#define NEO_KEY_S                  83
#define NEO_KEY_T                  84
#define NEO_KEY_U                  85
#define NEO_KEY_V                  86
#define NEO_KEY_W                  87
#define NEO_KEY_X                  88
#define NEO_KEY_Y                  89
#define NEO_KEY_Z                  90

/*---------- System Keys ----------*/
#define NEO_KEY_LEFT_SUPER         91
#define NEO_KEY_RIGHT_SUPER        92
#define NEO_KEY_MENU               93

/*------------- Numpad ------------*/
#define NEO_KEY_NUMPAD_0           96
#define NEO_KEY_NUMPAD_1           97
#define NEO_KEY_NUMPAD_2           98
#define NEO_KEY_NUMPAD_3           99
#define NEO_KEY_NUMPAD_4           100
#define NEO_KEY_NUMPAD_5           101
#define NEO_KEY_NUMPAD_6           102
#define NEO_KEY_NUMPAD_7           103
#define NEO_KEY_NUMPAD_8           104
#define NEO_KEY_NUMPAD_9           105
#define NEO_KEY_NUMPAD_MULTIPLY    106
#define NEO_KEY_NUMPAD_ADD         107
#define NEO_KEY_NUMPAD_SUBTRACT    109
#define NEO_KEY_NUMPAD_DECIMAL     110
#define NEO_KEY_NUMPAD_DIVIDE      111

/*---------- Function Keys ---------*/
#define NEO_KEY_F1                 112
#define NEO_KEY_F2                 113
#define NEO_KEY_F3                 114
#define NEO_KEY_F4                 115
#define NEO_KEY_F5                 116
#define NEO_KEY_F6                 117
#define NEO_KEY_F7                 118
#define NEO_KEY_F8                 119
#define NEO_KEY_F9                 120
#define NEO_KEY_F10                121
#define NEO_KEY_F11                122
#define NEO_KEY_F12                123
#define NEO_KEY_F13                124
#define NEO_KEY_F14                125
#define NEO_KEY_F15                126
#define NEO_KEY_F16                127
#define NEO_KEY_F17                128
#define NEO_KEY_F18                129
#define NEO_KEY_F19                130
#define NEO_KEY_F20                131
#define NEO_KEY_F21                132
#define NEO_KEY_F22                133
#define NEO_KEY_F23                134
#define NEO_KEY_F24                135

/*------------ Lock Keys -----------*/
#define NEO_KEY_NUM_LOCK           144
#define NEO_KEY_SCROLL_LOCK        145

/*----- Punctuation / OEM Keys -----*/
#define NEO_KEY_SEMICOLON          186
#define NEO_KEY_EQUAL              187
#define NEO_KEY_COMMA              188
#define NEO_KEY_MINUS              189
#define NEO_KEY_PERIOD             190
#define NEO_KEY_SLASH              191
#define NEO_KEY_GRAVE              192
#define NEO_KEY_LEFT_BRACKET       219
#define NEO_KEY_BACKSLASH          220
#define NEO_KEY_RIGHT_BRACKET      221
#define NEO_KEY_APOSTROPHE         222
#define NEO_KEY_OEM_102            226
#endif