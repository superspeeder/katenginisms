#include "Renderer2D.h"

kat::Renderer2D::Renderer2D(kat::Window *window) : m_Viewport({0, 0}, window->getFramebufferSize()) {

}

kat::Renderer2D::~Renderer2D() = default;

void kat::Renderer2D::setViewport(const glm::ivec2 &position, const glm::ivec2 &size) {
    m_Viewport.position = position;
    m_Viewport.size = size;
}

void kat::Renderer2D::fitViewportToWindow(kat::Window *window) {
    m_Viewport = kat::irect({0, 0}, window->getFramebufferSize());
}

void kat::Renderer2D::clear() {
    glClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void kat::Renderer2D::setBackgroundColor(const glm::vec3 &color) {
    m_BackgroundColor = color;
}

const glm::vec3 &kat::Renderer2D::getColor() {
    return m_BackgroundColor;
}

