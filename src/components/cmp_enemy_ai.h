#pragma once

#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;
  std::vector<sf::Vector2f> _waypoints;
  unsigned int _index = 0;
  sf::Vector2f _target;

public:
  void update(double dt) override;

  explicit EnemyAIComponent(Entity* p, std::vector<sf::Vector2f> waypoints);

  EnemyAIComponent() = delete;

  sf::Vector2f getDirection();
};
