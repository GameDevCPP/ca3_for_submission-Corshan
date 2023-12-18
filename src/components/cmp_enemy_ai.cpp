#include "cmp_enemy_ai.h"

#include <utility>

using namespace std;
using namespace sf;

void EnemyAIComponent::update(double dt) {
    if (distance(_parent->getPosition(), _target) <= 30.f){
        _index++;
        if (_index == _waypoints.size()){
            _index = 0;
        }
        _target = _waypoints[_index];
        _direction *= -1.f;
    }

  auto mov = _direction * (float)(dt * _speed);
  mov.x += _direction.x * 16.f;

  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p, std::vector<sf::Vector2f> waypoints)
: ActorMovementComponent(p), _waypoints(std::move(waypoints)) {
  _speed = 100.0f;
  _target = _waypoints[0];
  _index = 0;

  _direction = (_target.x - _waypoints[_index].x < 0) ? sf::Vector2f {-1,0} : sf::Vector2f {1,0};
}

sf::Vector2f EnemyAIComponent::getDirection() {
    return _direction;
}
