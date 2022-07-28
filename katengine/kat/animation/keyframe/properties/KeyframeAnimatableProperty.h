#pragma once

#include "kat/core.h"

namespace kat {

    class KeyframeAnimatableProperty {
    public:

        inline void setPos(float t) {
            m_Pos = t;
        };

        inline float getPos() const noexcept {
            return m_Pos;
        };

        virtual void update() = 0;

    protected:
        float m_Pos;

    private:

    };
    
}