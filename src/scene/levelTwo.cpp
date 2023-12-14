#include "levelTwo.h"
#include "../components/components.h"
#include "../game.h"



void LevelTwo::Load() {
    ls::setBackground("res/img/rock.png", {0,0}, {1.5, 1.5});
    LevelSystem::loadLevelFile("res/levels/LevelTwo/levelTwo_V8.json","res/img/tile_colision.json");

    Engine::resizeWindow({
        static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
        static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
    });

    {
        _HUD = makeEntity();
        _HUD->addComponent<HUDComponent>();
    }

    {
        _door = makeEntity();
        auto pos = ls::getTilePosition(ls::findTiles(ls::END)[0]);
        _door->setPosition({pos.x, pos.y-70});
        _door->addComponent<DoorComponent>();
    }

    {
        _player = makeEntity();
        _player->addComponent<PlayerComponent>(ls::getTilePosition(ls::findTiles(ls::START)[0]));
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
}

void LevelTwo::Update(const double &dt) {

    Scene::Update(dt);
}

void LevelTwo::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}