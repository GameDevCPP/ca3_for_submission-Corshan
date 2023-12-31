#include "levelOne.h"
#include "LevelSystem.h"
#include "../game.h"
#include "../components/components.h"
#include "game_manager.h"

void LevelOne::Load() {
    ls::setBackground("res/img/background0.png", {50,0});
    LevelSystem::loadLevelFile("res/levels/LevelOne/levelOne_V3.json","res/img/tile_colision.json");

Engine::resizeWindow({
    static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
    static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
});

    {
        _HUD = makeEntity();
       auto hud =  _HUD->addComponent<HUDComponent>();
       GameManager::resetScore();
       GameManager::resetHealth();
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
        _lever->setPosition({1820,630});
        _lever->addComponent<LeverComponent>(_player);
    }

    {
        auto music = makeEntity();
        auto music_cmp = music->addComponent<MusicComponent>("chillloopable.wav");
        music_cmp->play();
    }

    setLoaded(true);
}

void LevelOne::Update(const double &dt) {

    int tile = ls::getTileAt({_player->getPosition().x, _player->getPosition().y+40});

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

    if (_lever->GetCompatibleComponent<LeverComponent>()[0]->isPulled()){
        _door->GetCompatibleComponent<DoorComponent>()[0]->open();
    }

    auto hud  = _HUD->GetCompatibleComponent<HUDComponent>()[0];
    hud->setScore(GameManager::getScore());
    hud->setHealth(GameManager::getCurrentHealth());

    if (tile == ls::END && _door->GetCompatibleComponent<DoorComponent>()[0]->isOpen()){
        Engine::ChangeScene(&levelTwo);
    }

    Scene::Update(dt);
}

void LevelOne::UnLoad() {
    ls::unload();
    Scene::UnLoad();
}

void LevelOne::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}