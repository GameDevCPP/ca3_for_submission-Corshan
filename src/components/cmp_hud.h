#pragma once

#include "ecm.h"
#include "SFML/Graphics/Text.hpp"
#include "system_resources.h"
#include "system_renderer.h"

class HUDComponent: public Component {
private:
    void loadScoreText();
    void loadCoinSprite();
protected:
    sf::Text _scoreText;
    std::shared_ptr<sf::Texture> _coinTexture;
    std::shared_ptr<sf::Sprite> _coinSprite;
    std::shared_ptr<sf::Font> _font;
    int _score = 0;
public:
    HUDComponent() = delete;
    explicit HUDComponent(Entity* p);
    void render() override;
    void update(double dt) override;
    void setScore(int score);
};