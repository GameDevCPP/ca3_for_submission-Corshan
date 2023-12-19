#include "engine.h"
#include "game.h"

MainMenu menu;
LevelOne levelOne;
LevelTwo levelTwo;
EndMenu endMenu;

int main(){
    Engine::Start(500,500,"Untitled Game", &levelTwo);
}