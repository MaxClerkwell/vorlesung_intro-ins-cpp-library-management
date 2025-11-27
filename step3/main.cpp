#include "library/Car.hpp"
#include <iostream>

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}