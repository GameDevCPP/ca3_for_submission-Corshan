#include "cmp_player_animation.h"

PlayerAnimationComponent::PlayerAnimationComponent(Entity *p):
        AnimationComponent(p), _runAnim(), _idleAnim() {
    std::ifstream json("res/img/anim.json");
    nlohmann::json file = nlohmann::json::parse(json);

    for (auto t: file.at("player").at("run")){
        _runAnim.push_back(
               sf::Rect<int>{
                       t.at("x"),
                       t.at("y"),
                       t.at("width"),
                       t.at("height")
               });
    }

    for(auto t: file.at("player").at("idle")){
        _idleAnim.push_back(
                sf::Rect<int>{
                        t.at("x"),
                        t.at("y"),
                        t.at("width"),
                        t.at("height")
                });
    }

    setTextureRects(_idleAnim);
}

void PlayerAnimationComponent::update(double dt) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        flipSprite({-1,1});
        if (_currentAnim != RUN){
            _currentAnim = RUN;
            setTextureRects(_runAnim);
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        flipSprite({1,1});
        if (_currentAnim != RUN){
            _currentAnim = RUN;
            setTextureRects(_runAnim);
        }
    } else{
        if (_currentAnim != IDLE){
            _currentAnim = IDLE;
            setTextureRects(_idleAnim);
        }
    }
    AnimationComponent::update(dt);
}