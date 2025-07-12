//
// Created by arielhirsch on 7/3/25.
//

#pragma once
#include <opencv2/opencv.hpp>

namespace Constants {
    //screen constants
    inline constexpr int SCREEN_WIDTH = 700;
    inline constexpr int SCREEN_HEIGHT = 500;
    //hsv constants
    inline constexpr int H_PAD = 10;
    inline constexpr int S_PAD = 40;
    inline constexpr int V_PAD = 40;

    //fruit constants
    inline constexpr int STARTER_VELOCITY = -3;
    inline constexpr int WIDTH_HEIGHT = 100;
    inline constexpr double DOWNWARD_ACCELERATION = 0.33;

    //trail constants
    inline constexpr double FINGER_TRAIL_DURATION = 0.5;// in seconds
    inline constexpr int FINGER_TRAIL_RADIUS= 3;
}