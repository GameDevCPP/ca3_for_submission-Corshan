#pragma once

#include "engine.h"
#include "LevelSystem.h"
#include "../components/components.h"
#include "game_manager.h"

class EndMenu: public Scene {
protected:
    std::shared_ptr<Entity> _quit;
    std::shared_ptr<Entity> _restart;

public:
    EndMenu() = default;
    ~EndMenu() override = default;

    void Load() override;
    void Update(const double& dt) override;
    void Render() override;
};