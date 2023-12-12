#include "levelOne.h"
#include "LevelSystem.h"
#include "system_resources.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_animation.h"
#include "../components/cmp_pickup.h"
#include "../components/cmp_player.h"

std::shared_ptr<Entity> player;
std::shared_ptr<Entity> scoreText;
std::vector<std::shared_ptr<Entity>> coins;
int score = 0;

void LevelOne::Load() {
    ls::setBackground("res/img/background0.png", {2000,2000});
    LevelSystem::loadLevelFile("res/levels/LevelOne/levelOne_V3.json","res/img/tile_colision.json");

Engine::resizeWindow({
    static_cast<unsigned int>(ls::getWidth()*ls::getTileSize()),
    static_cast<unsigned int>(ls::getHeight()*ls::getTileSize())
});
//HUD
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
        auto cs = ls::findTiles(ls::COIN);

        for (auto c: cs) {
            auto coin = makeEntity();
            auto pos  =ls::getTilePosition(c);
            coin->setPosition({pos.x+40, pos.y});
            coin->addComponent<PickupComponent>(30.f);
            auto sprite = coin->addComponent<SpriteComponent>();
            sprite->setTexure(Resources::get<sf::Texture>("coinGold.png"));
            sprite->getSprite().setOrigin({
                        sprite->getSprite().getLocalBounds().width/2,
                        sprite->getSprite().getLocalBounds().height/2
                    });

            coins.push_back(coin);
        }
    }

    setLoaded(true);
}

void LevelOne::Update(const double &dt) {

    int tile = ls::getTileAt({player->getPosition().x, player->getPosition().y+40});

    if (tile == ls::END){
        Engine::ChangeScene(&menu);
    }

    auto playerPos = player->getPosition();
    for (int i = 0; i < coins.size(); i++) {
        auto parent = coins[i];
        auto coin  = parent->GetCompatibleComponent<PickupComponent>()[0];
//        std::cout << c->getPosition() << " : " << playerPos << std::endl;
        if(coin->isCollide(playerPos) && !coin->isPickedUp()){
            parent->setForDelete();
            score += 100;
            coin->setPickedUp(true);
            coins.erase(coins.begin()+i);
        }
    }

    scoreText->GetCompatibleComponent<TextComponent>()[0]->SetText("= " + std::to_string(score));
    Scene::Update(dt);
}

void LevelOne::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}