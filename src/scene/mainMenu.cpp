#include "mainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"
#include "game_manager.h"


void MainMenu::Load() {
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
        _playButton = makeEntity();
        _playButton->addComponent<ButtonComponent>(sf::Vector2f {x,y}, "Play");
    }

    {
        _quitButton = makeEntity();
        _quitButton->addComponent<ButtonComponent>(sf::Vector2f {x,y+100}, "Quit");
    }

    GameManager::resetScore();

    setLoaded(true);
}

void MainMenu::Update(const double &dt) {

    if (_playButton->GetCompatibleComponent<ButtonComponent>()[0]->isPressed()){
        Engine::ChangeScene(&levelOne);
    }

    if (_quitButton->GetCompatibleComponent<ButtonComponent>()[0]->isPressed()){
        Engine::End();
    }
    Scene::Update(dt);
}

void MainMenu::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}