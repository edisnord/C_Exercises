#include "stdio.h"
#include "stdlib.h"
#include "curl/curl.h"
#include "glad.h"
#include "GLFW/glfw3.h"
// Driver code
int main()
{
    char *types[7] = {
            "int", "char", "struct", "enum", "double", "float", "union"
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(1200, 720, "Test", NULL, NULL);
    return 0;
}