#include "mainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_button.h"
#include "../game.h"


void MainMenu::Load() {
    {
        _playButton = makeEntity();
        _playButton->addComponent<ButtonComponent>(sf::Vector2f {GAME_WIDTH/2.F,GAME_HEIGHT/2.F}, "Play");
    }
    setLoaded(true);
}

void MainMenu::Update(const double &dt) {

    if (_playButton->GetCompatibleComponent<ButtonComponent>()[0]->isPressed()){
        Engine::ChangeScene(&levelOne);
    }
    Scene::Update(dt);
}