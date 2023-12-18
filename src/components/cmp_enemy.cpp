#include "cmp_enemy.h"

#include <utility>

EnemyComponent::EnemyComponent(Entity *p, std::vector<sf::Vector2f> waypoints, sf::Vector2f pos)
: Component(p) {
    _parent->setPosition(pos);

    auto sprite = _parent->addComponent<SpriteComponent>();
    sprite->setTexure(Resources::get<sf::Texture>("enemies.png"));
    sprite->setTransformRect({0,37, 76, 56});

    sprite->getSprite().setOrigin({
        sprite->getSprite().getLocalBounds().width/2,
        0
    });

    _parent->setPosition(pos);
    _anim = _parent->addComponent<EnemyAnimationComponent>();
    _ai = _parent->addComponent<EnemyAIComponent>(std::move(waypoints));

    _anim->flipSprite(_ai->getDirection());
}

void EnemyComponent::update(double dt) {
    _anim->flipSprite({_ai->getDirection().x*-1, 1});
}