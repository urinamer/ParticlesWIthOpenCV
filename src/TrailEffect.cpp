

#include "../headers/TrailEffect.hpp"

#include "../headers/Constants.hpp"

FingerTrail::FingerTrail(std::chrono::high_resolution_clock::time_point  startTime,int x, int y) {
    this->startTime = startTime;
    this->x = x;
    this->y = y;
    this->duration = Constants::FINGER_TRAIL_DURATION;

}

std::chrono::high_resolution_clock::time_point  FingerTrail::getStartTime() const{
    return this->startTime;
}

int FingerTrail::getX() const{
    return  this->x;
}

int FingerTrail::getY() const{
    return this->y;
}

double FingerTrail::getDuration() const{
    return this->duration;
}

