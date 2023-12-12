#pragma once

#include "ecm.h"
#include "json.hpp"
#include "cmp_sprite.h"
#include "system_resources.h"

class DoorComponent: public Component {
protected:
    bool _isOpen = false;
    sf::IntRect _doorOpen;
    sf::IntRect _doorClose;
public:
    DoorComponent() = delete;
    explicit DoorComponent(Entity* p);
    void render() override {};
    void update(double dt) override {};
    bool isOpen();
    void open();
    void close();
};