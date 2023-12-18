#include "cmp_hud.h"

HUDComponent::HUDComponent(Entity *p): Component(p) {
    _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
    loadScoreText();
    loadCoinSprite();
    loadHealthText();
    loadHeartSprite();
}

void HUDComponent::render() {
    Renderer::queue(&_scoreText);
    Renderer::queue(_coinSprite.get());
    Renderer::queue(&_healthText);
    Renderer::queue(_heartSprite.get());
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

void HUDComponent::loadHeartSprite() {
    _heartTexture = Resources::get<sf::Texture>("hud_spritesheet.png");
    _heartSprite = std::make_shared<sf::Sprite>();

    _heartSprite->setTexture(*_heartTexture);
    _heartSprite->setTextureRect({0,94,53,45});

    _heartSprite->setOrigin({
        _heartSprite->getLocalBounds().width/2,
        _heartSprite->getLocalBounds().height/2
    });

    _heartSprite->setPosition(_parent->getPosition() + sf::Vector2f{550, 40});
}

void HUDComponent::loadHealthText() {
    _healthText.setString("= " + std::to_string(100));
    _healthText.setFont(*_font);
    _healthText.setCharacterSize(60);
    _healthText.setPosition(_parent->getPosition() + sf::Vector2f {600,0});
}


void HUDComponent::setScore(int score) {
    _score = score;
    _scoreText.setString("= " + std::to_string(_score));
}

void
 HUDComponent::setHealth(int health) {
    _healthText.setString("= " + std::to_string(health));
}