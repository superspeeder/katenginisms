#pragma once

#include "kat/core.h"
#include "kat/colors.h"
#include "kat/geometry.h"
#include "kat/Window.h"

namespace kat {

    class Renderer2D {
    public:

        Renderer2D(kat::Window* window);
        ~Renderer2D();

        void setViewport(const glm::ivec2& position, const glm::ivec2& size);
        void fitViewportToWindow(kat::Window* window);

        void clear();

        void setBackgroundColor(const glm::vec3& color);
        const glm::vec3& getColor();

    private:
        glm::vec3 m_BackgroundColor = kat::colors::BLACK;
        kat::irect m_Viewport;

    };
    
}