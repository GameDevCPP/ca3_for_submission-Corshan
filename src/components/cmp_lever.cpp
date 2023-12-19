#include "cmp_lever.h"

#include <utility>

LeverComponent::LeverComponent(Entity *p, std::shared_ptr<Entity> player): Component(p) {
    auto sprite = _parent->addComponent<SpriteComponent>();
    sprite->setTexure(Resources::get<sf::Texture>("items_spritesheet.png"));
    sprite->getSprite().setTextureRect({504, 216, 70,70});

    _parent->addComponent<InteractionComponent>(std::move(player));

    std::ifstream json("res/img/anim.json");
    nlohmann::json file = nlohmann::json::parse(json);

    auto idle = file.at("lever").at("idle");
    _idle = sf::IntRect {
        idle.at("x"),
        idle.at("y"),
        idle.at("width"),
        idle.at("height")
    };

    for (auto rect: file.at("lever").at("play")) {
        _play.push_back({
           rect.at("x"),
           rect.at("y"),
           rect.at("width"),
           rect.at("height")
        });
    }

    auto anim = _parent->addComponent<AnimationComponent>();
    anim->setTextureRects({_idle});
    _parent->addComponent<SoundComponent>("rattle1.wav");
}

void LeverComponent::update(double dt) {
    auto interact = _parent->GetCompatibleComponent<InteractionComponent>()[0];
    auto anim = _parent->GetCompatibleComponent<AnimationComponent>()[0];
    auto sound = _parent->GetCompatibleComponent<SoundComponent>()[0];

    if (interact->isInteraction() && !_isPulled){
        anim->setTextureRects(_play);
        anim->play(true);
        _isPulled = true;
        sound->play();
    }
}

bool LeverComponent::isPulled() {
    return _isPulled;
}