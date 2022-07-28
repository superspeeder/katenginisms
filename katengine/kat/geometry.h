#pragma once

#include "kat/core.h"

namespace kat {
    struct rect {
        glm::vec2 position, size;

        inline rect(const glm::vec2& position_, const glm::vec2& size_) : position(position_), size(size_) {};
    };

    struct irect {
        glm::ivec2 position, size;

        inline irect(const glm::ivec2& position_, const glm::ivec2& size_) : position(position_), size(size_) {};
    };
}