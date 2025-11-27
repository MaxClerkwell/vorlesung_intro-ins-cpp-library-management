#ifndef CAR_HPP
#define CAR_HPP

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

#endif