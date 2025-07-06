#include "../headers/Fruit.hpp"
#include "../headers/Constants.hpp"

std::string Fruit::getImage() const{
    return this->image;
}

Fruit::Fruit(int points, const std::string& image, double xVelocity, double yVelocity) {
    this->points = points;
    this-> image = image;
    this->xVelocity = xVelocity;
    this->yVelocity= yVelocity;
    this->x = Constants::SCREEN_WIDTH/2;
    this->y = Constants::SCREEN_HEIGHT+Constants::WIDTH_HEIGHT;
}

void Fruit::move() {
    this->x += this->xVelocity;
    this->y += this->yVelocity;

    this->yVelocity += Constants::DOWNWARD_ACCELERATION;
}

void Fruit::slice() {

}

double Fruit::getX() const{
    return  this->x;
}

double Fruit::getY() const{
    return this->y;
}

 unsigned int Fruit::getPoints() const {
    return this->points;
}

double Fruit::getXVelocity() const{
    return this->xVelocity;
}

double Fruit::getYVelocity() const{
    return this->yVelocity;
}
