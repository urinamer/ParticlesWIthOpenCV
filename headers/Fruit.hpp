//
// Created by arielhirsch on 7/5/25.
//
#pragma once
#include <iostream>


class Fruit {
    public:
        Fruit(int points,const std::string& image,int xVelocity, int yVelocity);
        void move();
        void slice();
        std::string getImage() const;
        int getX() const;
        int getY() const;
        int getXVelocity() const;
        int getYVelocity() const;
        unsigned int getPoints() const;
    private:
        unsigned int points;
        std::string image;
        int x;
        int y;
        unsigned int xVelocity;
        unsigned int yVelocity;

};
