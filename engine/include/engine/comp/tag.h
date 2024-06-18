#pragma once

#include <engine/comp/_component.h>
#include <string>

/**
 * @brief A component that represents a tag.
 * @details This class stores a tag as a string, which can be used to identify or categorize entities.
 */
class Tag : public Component {
    std::string _tag;
public:
    /**
     * @brief Constructs a Tag component with the given tag string.
     *
     * @param tag The tag string to initialize the Tag component.
     */
    explicit Tag(std::string tag);

    /**
     * @brief Retrieves the tag string.
     *
     * @return The tag string.
     */
    [[nodiscard]] std::string Get() const;
};