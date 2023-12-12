#pragma once

#include "ecm.h"
#include "SFML/Graphics.hpp"

class InteractionComponent: public Component {
protected:
    std::shared_ptr<Entity> _player;
    float _distance;
    bool _interaction = false;
public:
    InteractionComponent() = delete;
    explicit InteractionComponent(Entity* p, std::shared_ptr<Entity> player);
    void render() override {};
    void update(double dt) override;
    bool isInteraction();
};