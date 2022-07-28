#pragma once

#include "kat/core.h"
#include "kat/Window.h"

namespace kat {

    class Application {
    public:
        Application();
        virtual ~Application();

        void run();

        inline kat::Window* getWindow() { return m_Window.get(); };

    protected:
        inline virtual void configure() {};
        inline virtual void create() {};
        inline virtual void destroy() {};
        inline virtual void render(double dt) {};

        WindowConfig windowConfig{};
        double maxFPS = -1;

    private:

        void preConfigure();
        void postConfigure();

        void preCreate();
        void postCreate();

        void preDestroy();
        void postDestroy();

        double calcDeltaTime();

        void preRender(double dt);
        void postRender(double dt);

        double m_DeltaTime = 1.0 / 60.0;
        double m_LastFrame;
        double m_ThisFrame;

        std::unique_ptr<Window> m_Window;
    };

} // kat
