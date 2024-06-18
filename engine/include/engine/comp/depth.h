#pragma once

#include <engine/comp/_component.h>

/**
 * @brief A component for handling execution order based on depth.
 *
 * @details This manages the execution order of components in the game engine by assigning
 * a depth value. Components with different depth values can be processed in a specific order.
 */
class Depth : public Component {
    int _depth;
public:
    /**
     * @brief Constructs a Depth component with the given depth value.
     *
     * @param depth The depth value used to determine execution order.
     */
    explicit Depth(int depth);

    /**
     * @brief Retrieves the depth value.
     *
     * @return The depth value.
     */
    [[nodiscard]] int Get() const;
};