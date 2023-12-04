#pragma once

#include "ecm.h"
#include "system_resources.h"
#include "system_renderer.h"
#include "SFML/Graphics.hpp"
#include "engine.h"
#include "string"

class ButtonComponent: public Component {
protected:
    sf::Vector2f _pos;
    sf::Vector2f _size = {200,50};
    std::shared_ptr<sf::Font> _font;
    sf::RectangleShape _shape;
    sf::Text _text;
    std::string _str;
    bool _isPressed = false;

public:
    ButtonComponent() = delete;

    explicit ButtonComponent(Entity* p, sf::Vector2f pos, std::string str);
    void update(double dt) override;
    void render() override;
    bool isPressed();

    ~ButtonComponent() override = default;
};