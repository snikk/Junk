#include "commands.h"
#include <string.h>
#include <stdio.h>

const char* CMD_V_CRT = "V_CRT";
const char* CMD_V_CHLD = "V_CHLD";
const char* CMD_V_BG_COLOR = "V_BG_COLOR";
const char* CMD_V_SET_MARGIN = "V_SET_MARGIN";
const char* CMD_V_SET_DIMEN = "V_SET_DIMEN";
const char* CMD_V_SET_REL = "V_SET_REL";
const char* CMD_A_SET_CONTENT = "A_SET_CONTENT";
const char* CMD_S_PRINT = "S_PRINT";
const char* CMD_S_JMP = "JMP";
const char* CMD_S_JMP_E = "JMP_E";
const char* CMD_S_JMP_GT = "JMP_GT";
const char* CMD_S_JMP_LT = "JMP_LT";
const char* CMD_S_JMP_GTE = "JMP_GTE";
const char* CMD_S_JMP_LTE = "JMP_LTE";
const char* CMD_S_RETURN = "RETURN";

const char* C_RELATIVE = "RELATIVE";
const char* C_VIEW = "VIEW";
const char* C_IMAGE = "IMAGE";
const char* C_BELOW = "BELOW";
const char* C_RIGHT = "RIGHT";

OpCode getOpCode(const char* cmd) {
    printf("getOpCode | cmp = %s | strlen(cmd) = %d | CMD_V_CRT = %s | strlen(CMD_V_CRT) = %d | strcmp(cmd, CMD_V_CRT) = %d\n", cmd, strlen(cmd), CMD_V_CRT, strlen(CMD_V_CRT), strcmp(cmd, CMD_V_CRT));
    if (strcmp(cmd, CMD_V_CRT) == 0) return V_CREATE;
    else if (strcmp(cmd, CMD_V_CHLD) == 0) return V_SET_CHILD;
    else if (strcmp(cmd, CMD_V_BG_COLOR) == 0) return V_SET_BACKGROUND_COLOR;
    else if (strcmp(cmd, CMD_V_SET_MARGIN) == 0) return V_SET_MARGIN;
    else if (strcmp(cmd, CMD_V_SET_DIMEN) == 0) return V_SET_DIMEN;
    else if (strcmp(cmd, CMD_V_SET_REL) == 0) return V_SET_REL;
    else if (strcmp(cmd, CMD_A_SET_CONTENT) == 0) return A_SET_CONTENT;
    else if (strcmp(cmd, CMD_S_PRINT) == 0) return S_PRINT;
    else if (strcmp(cmd, CMD_S_JMP) == 0) return S_JMP;
    else if (strcmp(cmd, CMD_S_JMP_E) == 0) return S_JMP_E;
    else if (strcmp(cmd, CMD_S_JMP_GT) == 0) return S_JMP_GT;
    else if (strcmp(cmd, CMD_S_JMP_LT) == 0) return S_JMP_LT;
    else if (strcmp(cmd, CMD_S_JMP_GTE) == 0) return S_JMP_GTE;
    else if (strcmp(cmd, CMD_S_JMP_LTE) == 0) return S_JMP_LTE;
    else if (cmd[0] == FUNC_DELIM) return S_FUNC;

    return -1;
}

char getConstant(const char* constant) {
    if (strcmp(constant, C_RELATIVE) == 0) return RELATIVE;
    else if (strcmp(constant, C_VIEW) == 0) return VIEW;
    else if (strcmp(constant, C_IMAGE) == 0) return IMAGE;
    else if (strcmp(constant, C_BELOW) == 0) return 3;
    else if (strcmp(constant, C_RIGHT) == 0) return 1;

    return -1;
}
