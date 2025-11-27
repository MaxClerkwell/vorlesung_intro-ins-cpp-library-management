#include "library/Car.hpp"

Car::Car(int initialSpeed) : speed(initialSpeed) {}

void Car::accelerate(int amount) {
    speed += amount;
}

int Car::getSpeed() const {
    return speed;
}