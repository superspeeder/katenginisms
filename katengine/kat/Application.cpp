#include "Application.h"
#include "katengine.h"

namespace kat {


    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::preConfigure() {

    }

    void Application::postConfigure() {

    }

    void Application::preCreate() {
        m_Window = std::make_unique<Window>(windowConfig);
    }

    void Application::postCreate() {
        m_DeltaTime = 1.0 / 60.0;
        m_ThisFrame = Window::getTime() - m_DeltaTime;
        m_LastFrame = m_ThisFrame - m_DeltaTime;
    }

    void Application::preDestroy() {

    }

    void Application::postDestroy() {

    }

    double Application::calcDeltaTime() {
        m_LastFrame = m_ThisFrame;
        m_ThisFrame = Window::getTime();
        m_DeltaTime = m_ThisFrame - m_LastFrame;

        return m_DeltaTime;
    }

    void Application::preRender(double dt) {
        Window::pollEvents();

    }

    void Application::postRender(double dt) {
        m_Window->swap();
        if (maxFPS > 0) {
            double minDt = 1.0 / maxFPS;
            while (Window::getTime() - m_ThisFrame < minDt) {}
        }
    }

    void Application::run() {
        kat::init();

        preConfigure();
        configure();
        postConfigure();

        preCreate();
        create();
        postCreate();

        while (m_Window->isOpen()) {
            calcDeltaTime();
            preRender(m_DeltaTime);
            render(m_DeltaTime);
            postRender(m_DeltaTime);
        }

        preDestroy();
        destroy();
        postDestroy();

        kat::terminate();
    }
} // kat