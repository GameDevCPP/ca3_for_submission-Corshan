#include "levelOne.h"
#include "LevelSystem.h"
#include "system_resources.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"

std::shared_ptr<Entity> player;

void LevelOne::Load() {
    auto txt = makeEntity();
    txt->addComponent<TextComponent>("LevelOne");
    LevelSystem::loadLevelFile("res/levels/levelOne.json", 10);

    {
        player = makeEntity();
        auto s = player->addComponent<SpriteComponent>();
        auto texture = Resources::get<sf::Texture>("p1_spritesheet.png");
        s->setTexure(texture);
        auto pos = ls::getTilePosition(ls::findTiles(ls::START)[0]);
        player->setPosition(pos);
        s->getSprite().setTextureRect({0,0, 72, 94});
        auto pp = player->addComponent<PlayerPhysicsComponent>(sf::Vector2f {72.f,94.f});
    }

    {
        auto ground = ls::findTiles(ls::WALL);
        for (auto g : ground) {
            auto pos = ls::getTilePosition(g);
//            pos += sf::Vector2f(70.f/2, 70.f/2);//offset to center
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