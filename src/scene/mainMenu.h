#pragma once

#include "engine.h"
#include "../components/components.h"
#include "game_manager.h"

class MainMenu: public Scene {
private:
    std::shared_ptr<Entity> _playButton;
    std::shared_ptr<Entity> _quitButton;
public:
    MainMenu() = default;
    ~MainMenu() override = default;

    void Load() override;

    void Update(const double& dt) override;

    void Render() override;
};


