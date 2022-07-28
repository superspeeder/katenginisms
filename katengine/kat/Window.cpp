#include "Window.h"

namespace kat {
    Window::Window(const WindowConfig &cfg) {
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_RESIZABLE, cfg.resizable);
        glfwWindowHint(GLFW_MAXIMIZED, cfg.maximized);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, cfg.debug);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        if (cfg.fullscreenMonitor.has_value()) {
            int m = cfg.fullscreenMonitor.value();
            GLFWmonitor* monitor;
            if (m == 0) {
                monitor = glfwGetPrimaryMonitor();
            } else {
                int mc;
                GLFWmonitor** mons = glfwGetMonitors(&mc);
                if (m < mc) {
                    monitor = mons[m];
                } else {
                    monitor = mons[0];
                    spdlog::warn("Monitor {} is unavailable, defaulting to primary.", m);
                }
            }

            const GLFWvidmode* vm = glfwGetVideoMode(monitor);
            glfwWindowHint(GLFW_REFRESH_RATE, vm->refreshRate);
            glfwWindowHint(GLFW_RED_BITS, vm->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, vm->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, vm->blueBits);

            m_Window = glfwCreateWindow(vm->width, vm->height, cfg.title.c_str(), monitor, nullptr);
        } else {
            m_Window = glfwCreateWindow(cfg.size.x, cfg.size.y, cfg.title.c_str(), nullptr, nullptr);
        };

        glfwMakeContextCurrent(m_Window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
    }

    void Window::swap() {
        glfwSwapBuffers(m_Window);
    }

    bool Window::isOpen() {
        return !glfwWindowShouldClose(m_Window);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    double Window::getTime() {
        return glfwGetTime();
    }

    glm::ivec2 Window::getFramebufferSize() {
        glm::ivec2 v{};
        glfwGetFramebufferSize(m_Window, &v.x, &v.y);
        return v;
    }
} // kat