#pragma once

#include "ecm.h"
#include "cmp_sprite.h"
#include "maths.h"

class PickupComponent: public Component {
protected:
    float _distance;
    bool _isPickedUp;
public:
    void update(double dt) override;
    void render() override {};
    explicit PickupComponent(Entity* p, float distance);
    PickupComponent() = delete;

    bool isCollide(sf::Vector2f pos);
    bool isPickedUp();
    void setPickedUp(bool pickUp);
};