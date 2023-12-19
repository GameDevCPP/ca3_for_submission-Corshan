#pragma once

#include "ecm.h"
#include "system_resources.h"
#include "components.h"

class LeverComponent: public Component {
protected:
    sf::Rect<int> _idle;
    std::vector<sf::Rect<int>> _play;
    bool _isPulled = false;
public:
    LeverComponent() = delete;
    explicit LeverComponent(Entity* p, std::shared_ptr<Entity> player);
    void update(double dt) override;
    void render() override {};
    bool isPulled();
};