#ifndef __COMMANDS_H__
#define __COMMANDS_H__

typedef char OpCode;

#define LIT_BYTE 2
#define LIT_INT 3
#define LIT_FLOAT 4
#define LIT_STRING 20

#define V_CREATE 1
#define V_SET_MARGIN 5
#define V_SET_REL 6
#define V_SET_CHILD 7
#define V_SET_BACKGROUND_COLOR 8
#define V_SET_DIMEN 10

#define A_SET_CONTENT 9

#define S_PRINT 11
#define S_JMP 12
#define S_JMP_E 13
#define S_JMP_GT 14
#define S_JMP_LT 15
#define S_JMP_GTE 16
#define S_JMP_LTE 17
#define S_FUNC 18
#define S_RET 19

#define RELATIVE 1
#define VIEW 2
#define IMAGE 3

#define FUNC_DELIM ':'

extern const char* CMD_V_CRT;
extern const char* CMD_V_CHLD;
extern const char* CMD_V_BG_COLOR;
extern const char* CMD_V_SET_MARGIN;
extern const char* CMD_V_SET_DIMEN;
extern const char* CMD_V_SET_REL;
extern const char* CMD_A_SET_CONTENT;
extern const char* CMD_S_PRINT;
extern const char* CMD_S_JMP;
extern const char* CMD_S_JMP_E;
extern const char* CMD_S_JMP_GT;
extern const char* CMD_S_JMP_LT;
extern const char* CMD_S_JMP_GTE;
extern const char* CMD_S_JMP_LTE;
extern const char* CMD_S_RETURN;

extern const char* C_RELATIVE;
extern const char* C_VIEW;
extern const char* C_IMAGE;
extern const char* C_BELOW;
extern const char* C_RIGHT;

extern OpCode getOpCode(const char* cmd);
extern char getConstant(const char* constant);


#endif
