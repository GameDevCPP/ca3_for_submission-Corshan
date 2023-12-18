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
        GameManager::resetHealth();
        hud->setHealth(GameManager::getCurrentHealth());
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
        std::ifstream json("res/levels/enemies_spawnpoint.json");
        nlohmann::json file = nlohmann::json::parse(json);

        for(auto en: file.at("levelTwo")){
            auto enemy = makeEntity();
            auto waypoints = std::vector<sf::Vector2f>();

            for (auto waypoint: en.at("waypoints")) {
                waypoints.push_back({
                        waypoint.at("x"),
                        waypoint.at("y")
                        });
            }

            enemy->addComponent<EnemyComponent>(
                    waypoints,
                    sf::Vector2f {en.at("pos").at("x"),en.at("pos").at("y")}
                    );

            _enemies.push_back(enemy);
        }

        json.close();
    }
}

void LevelTwo::Update(const double &dt) {
    static float progress = 0.f;
    progress += dt;
    if (_lever->GetCompatibleComponent<LeverComponent>()[0]->isPulled()){
        _door->GetCompatibleComponent<DoorComponent>()[0]->open();
    }

    int tile = ls::getTileAt({_player->getPosition().x, _player->getPosition().y+40});

    if (tile == ls::END && _door->GetCompatibleComponent<DoorComponent>()[0]->isOpen()){
        Engine::ChangeScene(&endMenu);
    }

    if (progress >= 1){
        damagePlayer();
        progress = 0;
    }

    if (GameManager::getCurrentHealth() <= 0){
        Engine::ChangeScene(&endMenu);
    }

    auto hud  = _HUD->GetCompatibleComponent<HUDComponent>()[0];
    hud->setScore(GameManager::getScore());
    hud->setHealth(GameManager::getCurrentHealth());
    Scene::Update(dt);
}

void LevelTwo::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}

void LevelTwo::UnLoad() {
    ls::unload();
    Scene::UnLoad();
}

void LevelTwo::damagePlayer(){
    auto playerSpite = _player->GetCompatibleComponent<SpriteComponent>()[0];
    for (const auto& enemy: _enemies) {
        auto enemySprite = enemy->GetCompatibleComponent<SpriteComponent>()[0];

        if (playerSpite->getSprite().getGlobalBounds().intersects(enemySprite->getSprite().getGlobalBounds())){
//            std::cout << "colide" << std::endl;
            GameManager::updateHealth();
        }

    }
}