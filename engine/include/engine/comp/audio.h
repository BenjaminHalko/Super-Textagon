#pragma once

#include <engine/comp/_component.h>
#include <soloud_wav.h>
#include <memory>

class AudioComponent : public Component {
    unsigned int _handle;
public:
    explicit AudioComponent(unsigned int handle);
    unsigned int operator()() const;
};
