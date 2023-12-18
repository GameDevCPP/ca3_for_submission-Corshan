#pragma once

#include "ecm.h"
#include "SFML/Audio.hpp"

class MusicComponent: public Component {
protected:
    std::shared_ptr<sf::Music> _music;
public:
    MusicComponent() = delete;
    explicit MusicComponent(Entity* p, const std::string& fileName);
    void update(double dt) override {};
    void render() override {};
    void play();
    void pause();
    void stop();
    void setLoop(bool loop);
};