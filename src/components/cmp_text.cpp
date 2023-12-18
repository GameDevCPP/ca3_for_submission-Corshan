#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);
  _text.setPosition(_parent->getPosition());
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
  _text.setOrigin({
     _text.getLocalBounds().width/2.f,
     _text.getLocalBounds().height/2.f
  });
}

void TextComponent::setFontSize(unsigned int size) {
    _text.setCharacterSize(size);
    _text.setOrigin({
        _text.getLocalBounds().width/2.f,
        _text.getLocalBounds().height/2.f
    });
}

void TextComponent::setFillColor(sf::Color color) {
    _text.setFillColor(color);
}