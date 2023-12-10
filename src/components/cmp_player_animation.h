#pragma once

#include "cmp_animation.h"

class PlayerAnimationComponent: public AnimationComponent {
protected:
    std::vector<sf::Rect<int>> _runAnim;
    std::vector<sf::Rect<int>> _idleAnim;

public:
    PlayerAnimationComponent() = delete;
    PlayerAnimationComponent(Entity *p);

    void update(double dt);
};