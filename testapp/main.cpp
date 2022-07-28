#include <iostream>
#include "main.h"
#include <glm/gtx/compatibility.hpp>

int main() {
    std::cout << "Hello!" << std::endl;

    TestApp app = TestApp();
    app.run();

	return 0;
}

void TestApp::configure() {
    Application::configure();
    windowConfig.title = "Test App";

    maxFPS = 60;
}

TestApp::TestApp() : kat::Application() {
}

void TestApp::create() {
    Application::create();
    m_Renderer = std::make_shared<kat::Renderer2D>(getWindow());
}

float n = 0.0f, c = 1.0f;

void TestApp::render(double dt) {
    Application::render(dt);
    spdlog::info("FPS: {}", 1.0 / dt);

    if (n >= 1.0f && c > 0) {
        c = -c;
        n = 1.0f;
    } else if (n <= 0.0f && c < 0) {
        c = -c;
        n = 0.0f;
    }

    n += c * dt;

    m_Renderer->setBackgroundColor(glm::lerp(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), n));

    m_Renderer->clear();
}
