#include "cmp_interaction.h"

#include <utility>

InteractionComponent::InteractionComponent(Entity *p, std::shared_ptr<Entity> player):
        Component(p), _player(std::move(player)), _distance(50.f) {

}

void InteractionComponent::update(double dt) {
    if (sf::distance(_player->getPosition(), _parent->getPosition()) <= _distance) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            _interaction = true;
        }
    }
}

bool InteractionComponent::isInteraction() {
    return _interaction;
}