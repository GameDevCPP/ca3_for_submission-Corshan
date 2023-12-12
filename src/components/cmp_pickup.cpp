#include "cmp_pickup.h"

void PickupComponent::update(double dt) {
}

PickupComponent::PickupComponent(Entity *p, float distance):
Component(p), _distance(distance), _isPickedUp(false) {}

bool PickupComponent::isCollide(sf::Vector2f pos) {
    return sf::distance(pos, _parent->getPosition()) <= _distance;
}

bool PickupComponent::isPickedUp() {
    return _isPickedUp;
}

void PickupComponent::setPickedUp(bool pickUp) {
    _isPickedUp = pickUp;
}