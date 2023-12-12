#include "levelOne.h"
#include "LevelSystem.h"
#include "system_resources.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_animation.h"
#include "../components/cmp_pickup.h"
#include "../components/cmp_player.h"
#include "../components/cmp_coin.h"
#include "../components/cmp_interaction.h"
#include "../components/cmp_lever.h"
#include "../components/cmp_door.h"

std::shared_ptr<Entity> player;
std::shared_ptr<Entity> scoreText;
std::vector<std::shared_ptr<Entity>> coins;
std::shared_ptr<Entity> door;
std::shared_ptr<Entity> lever;

int score = 0;

void LevelOne::Load() {
    ls::setBackground("res/img/background0.png", {2000,2000});
    LevelSystem::loadLevelFile("res/levels/LevelOne/levelOne_V3.json","res/img/tile_colision.json");

Engine::resizeWindow({
    static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
    static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
});

    {
        scoreText = makeEntity();
        scoreText->setPosition({270,0});
        auto txt = scoreText->addComponent<TextComponent>
                (" = " + std::to_string(score));
        txt->setFontSize(60);
        auto image = makeEntity();
        auto sprite = image->addComponent<SpriteComponent>();
        sprite->setTexure(Resources::get<sf::Texture>("coinGold.png"));
        sprite->getSprite().setScale({1.5,1.5});
        sprite->getSprite().setOrigin({
            sprite->getSprite().getLocalBounds().width/2,
            sprite->getSprite().getLocalBounds().height/2
        });
        image->setPosition({200,sprite->getSprite().getLocalBounds().height/2});
    }

    {
        door = makeEntity();
        auto pos = ls::getTilePosition(ls::findTiles(ls::END)[0]);
        door->setPosition({pos.x, pos.y-70});
        door->addComponent<DoorComponent>();
    }

    {
        player = makeEntity();
        auto p = player->addComponent<PlayerComponent>
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
            coins.push_back(coin);
        }
    }

    {
        lever = makeEntity();
        lever->setPosition({1820,630});
        lever->addComponent<LeverComponent>(player);
    }


    setLoaded(true);
}

void LevelOne::Update(const double &dt) {

    int tile = ls::getTileAt({player->getPosition().x, player->getPosition().y+40});

    auto playerPos = player->getPosition();
    for (int i = 0; i < coins.size(); i++) {
        auto parent = coins[i];
        auto coin  = parent->GetCompatibleComponent<PickupComponent>()[0];

        if(coin->isCollide(playerPos) && !coin->isPickedUp()){
            parent->setForDelete();
            score += 100;
            coin->setPickedUp(true);
            coins.erase(coins.begin()+i);
        }
    }

    if (lever->GetCompatibleComponent<LeverComponent>()[0]->isPulled()){
        door->GetCompatibleComponent<DoorComponent>()[0]->open();
    }

    scoreText->GetCompatibleComponent<TextComponent>()[0]->SetText("= " + std::to_string(score));

    if (tile == ls::END && door->GetCompatibleComponent<DoorComponent>()[0]->isOpen()){
        Engine::ChangeScene(&menu);
    }

    Scene::Update(dt);
}

void LevelOne::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}