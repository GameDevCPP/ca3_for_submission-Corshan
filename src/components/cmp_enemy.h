#pragma once

#include "ecm.h"
#include "components.h"

class EnemyComponent: public Component {
protected:
    std::vector<sf::IntRect> _run;
    std::shared_ptr<EnemyAnimationComponent> _anim;
    std::shared_ptr<EnemyAIComponent> _ai;
public:
    EnemyComponent() = delete;
    explicit EnemyComponent(Entity* p, std::vector<sf::Vector2f> waypoints, sf::Vector2f pos);

    void update(double dt) override;
    void render() override {};
};