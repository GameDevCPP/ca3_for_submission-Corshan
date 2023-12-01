#include "engine.h"
#include "game.h"

MainMenu menu;

int main(){
    Engine::Start(500,500,"Untitled Game", &menu);
}