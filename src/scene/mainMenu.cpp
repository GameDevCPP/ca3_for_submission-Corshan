#include "mainMenu.h"
#include "../components/cmp_text.h"


void MainMenu::Load() {
    {
        auto txt = makeEntity();
        auto t = txt->addComponent<TextComponent>("Test");
    }
    setLoaded(true);
}

void MainMenu::Update(const double &dt) {
    Scene::Update(dt);
}