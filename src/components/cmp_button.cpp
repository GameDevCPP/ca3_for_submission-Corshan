#include "cmp_button.h"


const sf::Color IDLE_COLOR = sf::Color::White;
const sf::Color HOVER_COLOR = sf::Color::Blue;
const sf::Color ACTIVE_COLOR = sf::Color::Red;

void ButtonComponent::update(double dt) {
    auto pos = sf::Vector2f {sf::Mouse::getPosition(Engine::GetWindow())};

    if (_shape.getGlobalBounds().contains(pos)){
        _shape.setFillColor(HOVER_COLOR);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            _shape.setFillColor(ACTIVE_COLOR);
            _isPressed = true;
        }
    } else{
        _shape.setFillColor(IDLE_COLOR);
    }
}

void ButtonComponent::render() {
    Renderer::queue(&_shape);
    Renderer::queue(&_text);
}

ButtonComponent::ButtonComponent(Entity *p, sf::Vector2f pos, std::string str):
Component(p), _pos(pos), _str(str) {
    _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
    _shape = sf::RectangleShape(_size);
    _shape.setOrigin(_shape.getGlobalBounds().width/2, _shape.getGlobalBounds().height/2);
    _shape.setPosition(_pos);
    _shape.setFillColor(IDLE_COLOR);

    _text = sf::Text();
    _text.setString(str);
    _text.setFont(*_font);
    _text.setOrigin(_text.getGlobalBounds().width/2, _text.getGlobalBounds().height/2);
    _text.setFillColor(sf::Color::Black);
    _text.setPosition({_pos.x, _pos.y-5});
}

bool ButtonComponent::isPressed() {
    return _isPressed;
}