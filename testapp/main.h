#pragma once
#include <kat/Application.h>
#include <kat/renderer/Renderer2D.h>

class TestApp : public kat::Application {
public:
    TestApp();

    void configure() override;
    void create() override;
    void render(double dt) override;

private:
    std::shared_ptr<kat::Renderer2D> m_Renderer;
};