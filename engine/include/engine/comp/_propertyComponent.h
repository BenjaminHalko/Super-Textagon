#pragma once

#include <engine/comp/_component.h>

/**
 * @brief A component that represents a property of an entity.
 * @note Components such as audio and timer are not properties.
 */

class PropertyComponent : public Component {};
