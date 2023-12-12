#include <fstream>
#include "cmp_door.h"


DoorComponent::DoorComponent(Entity *p): Component(p) {
    auto sprite = _parent->addComponent<SpriteComponent>();
    sprite->setTexure(Resources::get<sf::Texture>("tiles_spritesheet.png"));

    std::ifstream json("res/img/anim.json");
    nlohmann::json file = nlohmann::json::parse(json);

    auto door = file.at("door");
    _doorOpen = sf::IntRect {
            door.at("open").at("x"),
            door.at("open").at("y"),
            door.at("open").at("width"),
            door.at("open").at("height")
    };

    _doorClose = sf::IntRect {
            door.at("close").at("x"),
            door.at("close").at("y"),
            door.at("close").at("width"),
            door.at("close").at("height")
    };

    sprite->getSprite().setTextureRect(_doorClose);
}

bool DoorComponent::isOpen() {
    return _isOpen;
}

void DoorComponent::open() {
    _isOpen = true;
    _parent->GetCompatibleComponent<SpriteComponent>
            ()[0]->getSprite().setTextureRect(_doorOpen);
}

void DoorComponent::close() {
    _isOpen = false;
    _parent->GetCompatibleComponent<SpriteComponent>
            ()[0]->getSprite().setTextureRect(_doorClose);
}