//
// Created by arielhirsch on 7/2/25.
//

#pragma once

#include <opencv2/opencv.hpp>
#include "Fruit.hpp"


class Game {
    public:
        Game();
        void loop();
    private:
        bool isConfig;
        cv::Mat screen,hsvImage,maskImage;
        cv::VideoCapture cap;
        cv::Scalar lower;
        cv::Scalar higher;
        std::vector<Fruit> fruits;
        unsigned int round;
        unsigned int hp;
        void startRound();
        void renderFruits();
        static void onMouseCallBack(int event,int x,int y,int,void*);
};





