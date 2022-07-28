#pragma once

#include "kat/core.h"
#include <string>
#include <optional>


namespace kat {

    struct WindowConfig {
        std::string title;
        glm::ivec2 size{800, 800};

        bool resizable = true, maximized = false, debug = false;

        std::optional<int> fullscreenMonitor;
    };

    class Window {
    public:

        Window(const WindowConfig& cfg);
        ~Window();

        void swap();
        bool isOpen();

        static void pollEvents();
        static double getTime();

        glm::ivec2 getFramebufferSize();

    private:
        GLFWwindow* m_Window;
    };

} // kat
