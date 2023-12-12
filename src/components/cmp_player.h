#pragma once

#include "ecm.h"
#include "cmp_sprite.h"
#include "system_resources.h"
#include "cmp_player_physics.h"
#include "cmp_player_animation.h"

class PlayerComponent: public Component {
public:
    void update(double dt) override {};
    void render() override {};
    PlayerComponent() = delete;
    explicit PlayerComponent(Entity* p, sf::Vector2f pos);

    void setPosition(sf::Vector2f pos);
};
