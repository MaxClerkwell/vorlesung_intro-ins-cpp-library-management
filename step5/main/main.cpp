#include <iostream>
#include "library/Car.hpp"

int main() {
    Car car(0);
    car.accelerate(50);
    std::cout << "Geschwindigkeit: " << car.getSpeed() << std::endl;
    return 0;
}