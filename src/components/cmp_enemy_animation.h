#pragma once

#include "ecm.h"
#include "cmp_animation.h"

class EnemyAnimationComponent: public AnimationComponent {
protected:
    std::vector<sf::IntRect> _runAnim;

public:
    EnemyAnimationComponent() = delete;
    EnemyAnimationComponent(Entity* p);

    void update(double dt) override;
    void flipSprite(sf::Vector2f scale);

};