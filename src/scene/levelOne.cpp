#include "levelOne.h"
#include "LevelSystem.h"

void LevelOne::Load() {
    auto txt = makeEntity();
    txt->addComponent<TextComponent>("LevelOne");


//    LevelSystem::setOffset({-1680, -700});
    LevelSystem::loadLevelFile("res/levels/maze.txt", 10);

    setLoaded(true);
}

void LevelOne::Update(const double &dt) {}

void LevelOne::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}