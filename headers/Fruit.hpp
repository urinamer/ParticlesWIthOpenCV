//
// Created by arielhirsch on 7/5/25.
//
#pragma once
#include <iostream>


class Fruit {
    public:
        Fruit(int points,const std::string& image,double xVelocity, double yVelocity);
        void move();
        void slice();
        std::string getImage() const;
        double getX() const;
        double getY() const;
        double getXVelocity() const;
        double getYVelocity() const;
        unsigned int getPoints() const;
    private:
        unsigned int points;
        std::string image;
        double x;
        double y;
        double xVelocity;
        double yVelocity;

};
