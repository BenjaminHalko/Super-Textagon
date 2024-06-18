#pragma once

#include <engine/comp/_component.h>
#include <soloud_wav.h>
#include <memory>

/**
 * @brief A component for handling audio in the engine.
 *
 * @details Handles audio components within the game engine.
 * Stores audio component and allows access to it.
 */
class AudioComponent : public Component {
    unsigned int _handle;
public:
    /**
     * @brief Constructs an AudioComponent with the given handle.
     *
     * @param handle The handle to the audio resource.
     */
    explicit AudioComponent(unsigned int handle);

    /**
     * @brief Retrieves the handle to the audio resource.
     *
     * Returns handle stored within component.
     *
     * @return The handle to the audio resource.
     */
    unsigned int operator()() const;
};