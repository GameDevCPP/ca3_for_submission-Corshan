#pragma once

#include "engine.h"
#include "LevelSystem.h"

class LevelTwo: public Scene {
private:
    void damagePlayer();
protected:
    std::shared_ptr<Entity> _player;
    std::shared_ptr<Entity> _HUD;
    std::vector<std::shared_ptr<Entity>> _coins;
    std::vector<std::shared_ptr<Entity>> _enemies;
    std::shared_ptr<Entity> _door;
    std::shared_ptr<Entity> _lever;
public:
    LevelTwo() = default;
    ~LevelTwo() override = default;

    void Load() override;
    void Update(const double& dt) override;
    void Render() override;
};