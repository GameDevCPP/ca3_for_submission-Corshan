#include "cmp_animation.h"

AnimationComponent::AnimationComponent(Entity *p):
Component(p), _index(0) {
}

void AnimationComponent::update(double dt) {
    if (_isLoop) {
        loop(dt);
    } else if (_play){
        play(dt);
    }

}

void AnimationComponent::loop(double dt) {
    static float progress = 0.f;
    progress += dt;

    if (progress >= _delay){
        _index++;

        if (_index == _rects.size()){
            _index = 0;
        }

        _parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(_rects[_index]);
        progress = 0.f;
    }
}

void AnimationComponent::play(double dt) {
    static float progress = 0.f;
    progress += dt;
    if (progress >= _delay){
        _index++;

        if (_index == _rects.size()){
            _play = false;
            return;
        }

        _parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(_rects[_index]);
        progress = 0.f;
    }
}

void AnimationComponent::play(bool play) {
    _play = play;
    _index = 0;
}

void AnimationComponent::setLoop(bool isLoop) {
    _isLoop = isLoop;
}

void AnimationComponent::setTextureRects(std::vector<sf::Rect<int>> rects) {
    _index = 0;
    _rects = rects;
}

void AnimationComponent::flipSprite(sf::Vector2f scale) {
    auto s = _parent->GetCompatibleComponent<SpriteComponent>()[0];
    s->getSprite().setOrigin({s->getSprite().getLocalBounds().width/2.f, 0});
    s->getSprite().setScale(scale);
}