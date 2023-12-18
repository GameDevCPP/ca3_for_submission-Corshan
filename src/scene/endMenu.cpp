#include "endMenu.h"
#include "../game.h"

void EndMenu::Load() {
    Engine::resizeWindow({700,700});
    ls::setBackground("res/img/rock.png", {0,0});

    float x = Engine::getWindowSize().x/2.f;
    float y = Engine::getWindowSize().y/2.f;

    {
        auto titleText = makeEntity();
        titleText->setPosition({x, y-200});
        auto txt = titleText->addComponent<TextComponent>();

        txt->SetText("Untiled Game");
        txt->setFontSize(60);
        txt->setFillColor(sf::Color::Black);
    }

    {
        auto rect = makeEntity();
        rect->setPosition({x-200,y-100});
        auto sprite =  rect->addComponent<ShapeComponent>();

        sprite->setShape<sf::RectangleShape>(sf::Vector2f {400,200});
        auto c = sf::Color(0,0,0,150);
        sprite->getShape().setFillColor(c);
    }

    {
        auto scoreText = makeEntity();
        scoreText->setPosition({x-50,y-10});
        auto txt = scoreText->addComponent<TextComponent>();

        txt->SetText("Total Score: " + std::to_string(GameManager::getScore()));
        txt->setFontSize(30);
    }

    {
        _restart = makeEntity();
        _restart->addComponent<ButtonComponent>(sf::Vector2f {x-200,y+200},"Restart");
    }

    {
        _quit = makeEntity();
        _quit->addComponent<ButtonComponent>(sf::Vector2f {x+200, y+200}, "Quit");
    }
}

void EndMenu::Update(const double &dt) {

    if (_quit->GetCompatibleComponent<ButtonComponent>()[0]->isPressed()){
        Engine::End();
    }

    if (_restart->GetCompatibleComponent<ButtonComponent>()[0]->isPressed()){
        Engine::ChangeScene(&levelOne);
    }

    Scene::Update(dt);
}

void EndMenu::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}