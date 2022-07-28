#pragma once

#include "kat/core.h"
#include "kat/animation/keyframe/properties/KeyframeAnimatableProperty.h"

namespace kat {

    class ColorProperty : public KeyframeAnimatableProperty {
    public:
        ColorProperty(glm::vec3& color, const glm::vec3& start, const glm::vec3& end);
        ColorProperty(glm::vec3* color, const glm::vec3& start, const glm::vec3& end);

        void update() override;

    private:
        glm::vec3* m_Target;
        glm::vec3 m_Start, m_End;
    };
    
}