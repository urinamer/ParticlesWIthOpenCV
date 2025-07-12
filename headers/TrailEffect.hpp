
#pragma once
#include <chrono>

struct FingerTrail {
    FingerTrail(std::chrono::high_resolution_clock::time_point startTime,int x, int y);
    std::chrono::high_resolution_clock::time_point  getStartTime() const;
    int getX() const;
    int getY() const;
    double getDuration() const;

    private:
    std::chrono::high_resolution_clock::time_point startTime;
    int x;
    int y;
    double duration;
};

