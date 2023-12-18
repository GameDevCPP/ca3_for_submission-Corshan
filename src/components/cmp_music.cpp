#include "cmp_music.h"

MusicComponent::MusicComponent(Entity *p, const std::string& fileName)
: Component(p) {
    _music = std::make_shared<sf::Music>();
    _music->openFromFile("res/music/" + fileName);
}

void MusicComponent::play() {
    _music->play();
}

void MusicComponent::pause() {
    _music->pause();
}

void MusicComponent::stop() {
    _music->stop();
}

void MusicComponent::setLoop(bool loop) {
    _music->setLoop(loop);
}
