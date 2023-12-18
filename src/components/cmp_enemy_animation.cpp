#include "cmp_enemy_animation.h"

void EnemyAnimationComponent::update(double dt) {
    AnimationComponent::update(dt);
}

EnemyAnimationComponent::EnemyAnimationComponent(Entity *p):
AnimationComponent(p), _runAnim() {
    std::ifstream json("res/img/anim.json");
    nlohmann::json file = nlohmann::json::parse(json);

    for (auto anim: file.at("enemies").at("walk")) {
        _runAnim.push_back(
                sf::Rect<int>{
                        anim.at("x"),
                        anim.at("y"),
                        anim.at("width"),
                        anim.at("height")
                });
    }

    setTextureRects(_runAnim);
    setLoop(true);
}

void EnemyAnimationComponent::flipSprite(sf::Vector2f scale) {
    AnimationComponent::flipSprite(scale);
}