//
// Created by arielhirsch on 7/2/25.
//

#pragma once

#include <opencv2/opencv.hpp>
#include <memory>
#include "Fruit.hpp"
#include "TrailEffect.hpp"
#include <vector>



class Game {
    public:
        Game();
        void loop();
    private:
        bool isConfig;
        cv::Mat screen,bluredImage,hsvImage,maskImage;
        cv::VideoCapture cap;
        cv::Scalar lower;
        cv::Scalar higher;
        std::vector<Fruit> fruits;
        std::vector<std::unique_ptr<FingerTrail>> fingerTrails;//uses memory allocation
        unsigned int fingerMiddleX;
        unsigned int fingerMiddleY;
        cv::Rect fingerRect;
        unsigned int round;
        unsigned int hp;
        void startRound();
        void renderFruits();
        void detectFinger();
        void drawSliceEffect(int x,int y);
        void checkColisions();
        static void onMouseCallBack(int event,int x,int y,int,void*);
};





