#pragma once

#include "ecm.h"
#include "SFML/Graphics/Text.hpp"
#include "system_resources.h"
#include "system_renderer.h"

class HUDComponent: public Component {
private:
    void loadScoreText();
    void loadCoinSprite();
    void loadHealthText();
    void loadHeartSprite();
protected:
    sf::Text _scoreText;
    sf::Text _healthText;
    std::shared_ptr<sf::Texture> _coinTexture;
    std::shared_ptr<sf::Sprite> _coinSprite;

    std::shared_ptr<sf::Texture> _heartTexture;
    std::shared_ptr<sf::Sprite> _heartSprite;

    std::shared_ptr<sf::Font> _font;
    int _score = 0;
public:
    HUDComponent() = delete;
    explicit HUDComponent(Entity* p);
    void render() override;
    void update(double dt) override;
    void setScore(int score);
    void setHealth(int health);
};