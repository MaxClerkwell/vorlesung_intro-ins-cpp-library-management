#ifndef CAR_HPP
#define CAR_HPP

class Car {
private:
    int speed;
public:
    Car(int initialSpeed);
    void accelerate(int amount);
    int getSpeed() const;
};

#endif