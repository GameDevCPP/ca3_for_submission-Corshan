#include "cmp_player.h"

PlayerComponent::PlayerComponent(Entity *p, sf::Vector2f pos): Component(p) {
    auto sprite = _parent->addComponent<SpriteComponent>();
    sprite->setTexure(Resources::get<sf::Texture>("p3_spritesheet.png"));
    sprite->getSprite().setTextureRect({0,0, 72, 94});

    sprite->getSprite().setOrigin({
        sprite->getSprite().getLocalBounds().width/2,
        0
    });

    _parent->setPosition(pos);
    _parent->addComponent<PlayerPhysicsComponent>(sf::Vector2f {72.f,94.f});
    _parent->addComponent<PlayerAnimationComponent>();
}

void PlayerComponent::setPosition(sf::Vector2f pos) {
    _parent->setPosition(pos);
}