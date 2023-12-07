#pragma once

#include "engine.h"
#include "../components/cmp_text.h"

class LevelOne: public Scene {
public:
    LevelOne() = default;
    ~LevelOne() override = default;

    void Load() override;
    void Update(const double& dt) override;
    void Render() override;
};