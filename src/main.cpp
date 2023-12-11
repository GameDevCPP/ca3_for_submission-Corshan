#include "engine.h"
#include "game.h"

MainMenu menu;
LevelOne levelOne;

int main(){
    Engine::Start(500,500,"Untitled Game", &menu);
}