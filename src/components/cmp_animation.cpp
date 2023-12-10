#include "cmp_animation.h"

AnimationComponent::AnimationComponent(Entity *p):
Component(p), _index(0) {
}

void AnimationComponent::update(double dt) {
    static float progress = 0.f;
    progress += dt;
//    std::cout << progress << std::endl;
    if (progress >= _delay){
        _index++;


        if (_index == _rects.size()){
            _index = 0;
        }

        _parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setTextureRect(_rects[_index]);
//        _sprite->setTextureRect(_rects[_index]);
        progress = 0.f;
    }
    
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