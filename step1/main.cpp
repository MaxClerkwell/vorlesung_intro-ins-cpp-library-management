#include <iostream>

class Car {
private:
    int speed;
public:
    Car(int initialSpeed) : speed(initialSpeed) {}
    void accelerate(int amount) {
        speed += amount;
    }
    int getSpeed() const {
        return speed;
    }
};

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}