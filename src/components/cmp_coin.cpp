#include "cmp_coin.h"

CoinComponent::CoinComponent(Entity *p, sf::Vector2f pos):
        Component(p) {
    _parent->setPosition(pos);
    _parent->addComponent<PickupComponent>(40.f);

    auto sprite = _parent->addComponent<SpriteComponent>();
    sprite->setTexure(Resources::get<sf::Texture>("items_spritesheet.png"));
    sprite->getSprite().setTextureRect({288,360,70,70});

    sprite->getSprite().setOrigin({
        sprite->getSprite().getLocalBounds().width/2,
        sprite->getSprite().getLocalBounds().height/2
    });
}