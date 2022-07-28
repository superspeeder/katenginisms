#include "katengine.h"

namespace kat {
    void init() {
        glfwInit();
    }

    void terminate() {
        glfwTerminate();
    }
}