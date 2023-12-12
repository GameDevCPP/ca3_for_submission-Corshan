#include "mainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"


void MainMenu::Load() {
    Engine::resizeWindow({600,600});
    {
        _playButton = makeEntity();
        _playButton->addComponent<ButtonComponent>(sf::Vector2f {Engine::getWindowSize().x/2.F,Engine::getWindowSize().y/2.F}, "Play");
    }
    setLoaded(true);
}

void MainMenu::Update(const double &dt) {

    if (_playButton->GetCompatibleComponent<ButtonComponent>()[0]->isPressed()){
        Engine::ChangeScene(&levelOne);
    }
    Scene::Update(dt);
}