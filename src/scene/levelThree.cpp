#include "levelThree.h"
#include "LevelSystem.h"
#include "../components/components.h"
#include "game_manager.h"
#include "../game.h"

void LevelThree::Load() {
    ls::setBackground("res/img/snow.png", {0,0}, {1.5,1.5});
    LevelSystem::loadLevelFile("res/levels/LevelThree/levelThree_V1.json","res/img/tile_colision.json");

    Engine::resizeWindow({
        static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
        static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
    });

    {
        _HUD = makeEntity();
        auto hud =  _HUD->addComponent<HUDComponent>();
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
        auto p = _player->addComponent<PlayerComponent>
                (ls::getTilePosition(ls::findTiles(ls::START)[0]));
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
        _lever->setPosition({140,630});
        _lever->addComponent<LeverComponent>(_player);
    }
}

void LevelThree::Update(const double &dt) {

    if (_lever->GetCompatibleComponent<LeverComponent>()[0]->isPulled()){
        _door->GetCompatibleComponent<DoorComponent>()[0]->open();
    }

    int tile = ls::getTileAt({_player->getPosition().x, _player->getPosition().y+40});

    if (tile == ls::END && _door->GetCompatibleComponent<DoorComponent>()[0]->isOpen()){
        Engine::ChangeScene(&endMenu);
    }

    auto playerPos = _player->getPosition();
    for (int i = 0; i < _coins.size(); i++) {
        auto parent = _coins[i];
        auto coin  = parent->GetCompatibleComponent<PickupComponent>()[0];
        auto sprite = parent->GetCompatibleComponent<SpriteComponent>()[0];

        if(coin->isCollide(playerPos) && !coin->isPickedUp()){
            GameManager::updateScore();
            parent->GetCompatibleComponent<SoundComponent>()[0]->play();
            coin->setPickedUp(true);
            _coins.erase(_coins.begin()+i);
            sprite->setTexure(nullptr);
        }
    }

    auto hud  = _HUD->GetCompatibleComponent<HUDComponent>()[0];
    hud->setScore(GameManager::getScore());
    hud->setHealth(GameManager::getCurrentHealth());

    Scene::Update(dt);
}

void LevelThree::Render() {
 ls::render(Engine::GetWindow());
 Scene::Render();
}

void LevelThree::UnLoad() {
ls::unload();
Scene::UnLoad();
}