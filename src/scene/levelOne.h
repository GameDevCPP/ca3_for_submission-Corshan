#pragma once

#include "engine.h"
#include "../components/cmp_text.h"

class LevelOne: public Scene {
protected:
    std::shared_ptr<Entity> _player;
    std::shared_ptr<Entity> _HUD;
    std::vector<std::shared_ptr<Entity>> _coins;
    std::shared_ptr<Entity> _door;
    std::shared_ptr<Entity> _lever;
public:
    LevelOne() = default;
    ~LevelOne() override = default;

    void Load() override;
    void Update(const double& dt) override;
    void Render() override;
    void UnLoad() override;
};