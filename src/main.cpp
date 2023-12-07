#include "engine.h"
#include "game.h"

MainMenu menu;
LevelOne levelOne;
int GAME_WIDTH = 2000;
int GAME_HEIGHT = 1200;

int main(){
    Engine::Start(GAME_WIDTH,GAME_HEIGHT,"Untitled Game", &menu);
}