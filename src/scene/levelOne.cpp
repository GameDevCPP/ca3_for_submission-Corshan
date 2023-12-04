#include "levelOne.h"

void LevelOne::Load() {
    auto txt = makeEntity();
    txt->addComponent<TextComponent>("LevelOne");

    setLoaded(true);
}

void LevelOne::Update(const double &dt) {}