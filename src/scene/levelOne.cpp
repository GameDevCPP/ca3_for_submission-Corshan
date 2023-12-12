#include "levelOne.h"
#include "LevelSystem.h"
#include "system_resources.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_player_animation.h"
#include "../components/cmp_pickup.h"

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
        scoreText->setPosition({300,0});
        auto txt = scoreText->addComponent<TextComponent>(std::to_string(score));
        txt->
        auto image = makeEntity();
        auto sprite = image->addComponent<SpriteComponent>();
        sprite->setTexure(Resources::get<sf::Texture>("coinGold.png"));
        image->setPosition({200,0});
    }

    {
        player = makeEntity();
        auto s = player->addComponent<SpriteComponent>();
        auto texture = Resources::get<sf::Texture>("p3_spritesheet.png");
        s->setTexure(texture);
        auto pos = ls::getTilePosition(ls::findTiles(ls::START)[0]);
        player->setPosition(pos);
        s->getSprite().setTextureRect({0,0, 72, 94});
        s->getSprite().setOrigin({s->getSprite().getLocalBounds().width/2, s->getSprite().getLocalBounds().height/2});
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

    scoreText->GetCompatibleComponent<TextComponent>()[0]->SetText(std::to_string(score));
    Scene::Update(dt);
}

void LevelOne::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}