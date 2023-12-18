#pragma once

#include "ecm.h"
#include "SFML/Audio.hpp"
#include "system_resources.h"

class SoundComponent: public Component {
protected:
    std::shared_ptr<sf::SoundBuffer> _buffer;
    std::shared_ptr<sf::Sound> _sound;
public:
    SoundComponent() = delete;
    explicit SoundComponent(Entity* p, const std::string& path);
    void render() override {};
    void update(double dt) override;
    void play();
};