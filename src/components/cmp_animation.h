#pragma once

#include "ecm.h"
#include "SFML/Graphics.hpp"
#include "cmp_sprite.h"
#include "json.hpp"
#include <fstream>
#include <utility>

enum Anim {
    IDLE,
    RUN
};

class AnimationComponent: public Component {
protected:
    std::vector<sf::Rect<int>> _rects;
    unsigned int _index;
    Anim _currentAnim;
    float _delay = 0.1f;
public:
    void update(double dt) override;
    void render() override {};
    explicit AnimationComponent(Entity* p);
    AnimationComponent() = delete;
    void setTextureRects(std::vector<sf::Rect<int>> rects);
    void flipSprite(sf::Vector2f scale);
};