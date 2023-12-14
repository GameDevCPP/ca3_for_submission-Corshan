#include "cmp_hud.h"

HUDComponent::HUDComponent(Entity *p): Component(p) {
    _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
    loadScoreText();
    loadCoinSprite();
}

void HUDComponent::render() {
    Renderer::queue(&_scoreText);
    Renderer::queue(_coinSprite.get());
}

void HUDComponent::update(double dt) {

}

void HUDComponent::loadScoreText() {
    _scoreText.setString("= " + std::to_string(_score));
    _scoreText.setFont(*_font);
    _scoreText.setCharacterSize(60);
    _scoreText.setPosition(_parent->getPosition() + sf::Vector2f {300,0});
}

void HUDComponent::loadCoinSprite() {
    _coinTexture = Resources::get<sf::Texture>("items_spritesheet.png");
    _coinSprite = std::make_shared<sf::Sprite>();

    _coinSprite->setTexture(*_coinTexture);
    _coinSprite->setTextureRect({288,360,70,70});
    _coinSprite->setScale({1.5,1.5});

    _coinSprite->setOrigin({
        _coinSprite->getLocalBounds().width/2,
        _coinSprite->getLocalBounds().height/2
    });

    _coinSprite->setPosition(
            _parent->getPosition() + sf::Vector2f {250, _coinSprite->getLocalBounds().height/2}
            );
}

void HUDComponent::setScore(int score) {
    _score = score;
    _scoreText.setString("= " + std::to_string(_score));
}