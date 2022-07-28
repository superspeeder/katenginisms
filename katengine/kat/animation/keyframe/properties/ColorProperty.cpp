#include <glm/gtx/compatibility.hpp>
#include "ColorProperty.h"

kat::ColorProperty::ColorProperty(glm::vec3 &color, const glm::vec3& start, const glm::vec3& end) : m_Target(&color), m_Start(start), m_End(end) {
}

kat::ColorProperty::ColorProperty(glm::vec3 *color, const glm::vec3& start, const glm::vec3& end) : m_Target(color), m_Start(start), m_End(end) {

}

void kat::ColorProperty::update() {
    *m_Target = glm::lerp(m_Start, m_End, m_Pos);
}


