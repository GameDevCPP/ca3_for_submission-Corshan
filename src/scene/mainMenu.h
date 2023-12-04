#pragma once
#include "engine.h"

class MainMenu: public Scene {
private:
    std::shared_ptr<Entity> _playButton;
public:
    MainMenu() = default;
    ~MainMenu() override = default;

    void Load() override;

    void Update(const double& dt) override;
};


