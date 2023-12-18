#include "levelTwo.h"
#include "../components/components.h"
#include "../game.h"
#include "game_manager.h"

void LevelTwo::Load() {
    ls::setBackground("res/img/snow.png", {0,0}, {1.5, 1.5});
    LevelSystem::loadLevelFile("res/levels/LevelTwo/levelTwo_V8.json","res/img/tile_colision.json");

    Engine::resizeWindow({
        static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
        static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
    });

    {
        _HUD = makeEntity();
        auto hud = _HUD->addComponent<HUDComponent>();
        hud->setScore(GameManager::getScore());
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

    {
        auto coinTiles = ls::findTiles(ls::COIN);
        for (auto tile: coinTiles) {
            auto coin = makeEntity();
            coin->addComponent<CoinComponent>(ls::getTilePosition(tile));
            _coins.push_back(coin);
        }
    }

    {
        _lever = makeEntity();
        _lever->setPosition({1680,630});
        _lever->addComponent<LeverComponent>(_player);
    }

    {
//        auto enemy = makeEntity();
//        enemy->addComponent<EnemyAIComponent>(std::vector<sf::Vector2f>{
//            {1890,1120},
//            {140, 1120}
//        });
//        auto sprite = enemy->addComponent<SpriteComponent>();
//        sprite->setTexure(Resources::get<sf::Texture>("enemies.png"));
//        sprite->setTransformRect({0,37,76,55});

        auto enemy = makeEntity();
        enemy->addComponent<EnemyComponent>(
                std::vector<sf::Vector2f>{
            {1890,1120},
            {140, 1120}
        }, sf::Vector2f {120,1120}
                );

    }
}

void LevelTwo::Update(const double &dt) {

    if (_lever->GetCompatibleComponent<LeverComponent>()[0]->isPulled()){
        _door->GetCompatibleComponent<DoorComponent>()[0]->open();
    }

    int tile = ls::getTileAt({_player->getPosition().x, _player->getPosition().y+40});

    if (tile == ls::END && _door->GetCompatibleComponent<DoorComponent>()[0]->isOpen()){
        Engine::ChangeScene(&menu);
    }

    _HUD->GetCompatibleComponent<HUDComponent>()[0]->setScore(GameManager::getScore());
    Scene::Update(dt);
}

void LevelTwo::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}