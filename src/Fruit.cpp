#include "../headers/Fruit.hpp"
#include "../headers/Constants.hpp"

std::string Fruit::getImage() const{
    return this->image;
}

Fruit::Fruit(int points, const std::string& image, int xVelocity, int yVelocity) {
    this->points = points;
    this-> image = image;
    this->xVelocity = xVelocity;
    this->yVelocity= yVelocity;
    this->x = 100;
    this->y = 100;
}

void Fruit::move() {
    this->x += this->xVelocity;
    this->y += this->yVelocity;

    this->yVelocity += Constants::DOWNWARD_ACCELERATION;
}

void Fruit::slice() {

}

int Fruit::getX() const{
    return  this->x;
}

int Fruit::getY() const{
    return this->y;
}

 unsigned int Fruit::getPoints() const {
    return this->points;
}

int Fruit::getXVelocity() const{
    return this->xVelocity;
}

int Fruit::getYVelocity() const{
    return this->yVelocity;
}
