#include "cmp_sound.h"

SoundComponent::SoundComponent(Entity *p, const std::string& path)
: Component(p) {
    _buffer = Resources::get<sf::SoundBuffer>(path);
    _sound = std::make_shared<sf::Sound>();
}

void SoundComponent::update(double dt) {

}

void SoundComponent::play() {
    _sound->setBuffer(*_buffer);
    _sound->play();
}