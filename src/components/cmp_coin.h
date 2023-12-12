#pragma once

#include "ecm.h"
#include "cmp_pickup.h"
#include "system_resources.h"

class CoinComponent: public Component {
public:
    CoinComponent() = delete;
    explicit CoinComponent(Entity* p, sf::Vector2f pos);
    void render() override {};
    void update(double dt) override {};
};