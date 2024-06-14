#include <engine/comp/audio.h>

AudioComponent::AudioComponent(unsigned int handle) : _handle(handle) {}

unsigned int AudioComponent::operator()() const {
    return _handle;
}
