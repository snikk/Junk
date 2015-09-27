#include "Error.h"
#include "../common.h"

void fatalError(const char* message) {
    printf("Fatal error | %s\n", message);
    glfwTerminate();
    exit(1);
}
