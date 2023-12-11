#include "levelOne.h"
#include "LevelSystem.h"
#include "system_resources.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_animation.h"

std::shared_ptr<Entity> player;

void LevelOne::Load() {
    LevelSystem::loadLevelFile("res/levels/LevelOne/levelOne_V3.json","res/img/tile_colision.json");
//    Engine::GetWindow().setSize({
//        static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
//             static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
//    });
//    Engine::GetWindow().setView(sf::View(
//            {0,0,
//             static_cast<float>(Engine::getWindowSize().x),
//             static_cast<float>(Engine::getWindowSize().y)}));

Engine::resizeWindow({
    static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
    static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
});
    auto txt = makeEntity();
    txt->addComponent<TextComponent>("LevelOne");

    {
        player = makeEntity();
        auto s = player->addComponent<SpriteComponent>();
        auto texture = Resources::get<sf::Texture>("p1_spritesheet.png");
        s->setTexure(texture);
//        auto pos = ls::getTilePosition(ls::findTiles(ls::START)[0]);
        player->setPosition({200,200});
        s->getSprite().setTextureRect({0,0, 72, 94});
        auto pp = player->addComponent<PlayerPhysicsComponent>(sf::Vector2f {72.f,94.f});

        player->addComponent<PlayerAnimationComponent>();
    }

    {
        auto ground = ls::findTiles(ls::WALL);
        for (auto g : ground) {
            auto pos = ls::getTilePosition(g);
            pos += sf::Vector2f(70.f/2, -10);//offset to center
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<PhysicsComponent>(false, sf::Vector2f(70.f, 70.f));
        }
    }

    setLoaded(true);
}

void LevelOne::Update(const double &dt) {
    Scene::Update(dt);
}

void LevelOne::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}