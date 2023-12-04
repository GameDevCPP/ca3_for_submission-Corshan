#include "engine.h"
#include "game.h"

MainMenu menu;
LevelOne levelOne;
int GAME_WIDTH = 1000;
int GAME_HEIGHT = 600;

int main(){
    Engine::Start(GAME_WIDTH,GAME_HEIGHT,"Untitled Game", &menu);
}