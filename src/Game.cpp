

#include "../headers/Game.hpp"
#include "../headers/Constants.hpp"
#include <opencv2/opencv.hpp>

Game::Game() {
    this->cap = cv::VideoCapture(0);
    this->isConfig = true;
    this-> lower = cv::Scalar(0,0,0);
    this-> higher = cv::Scalar(0,0,0);

    cv::namedWindow("Image");
    if (!cap.isOpened()) {
        std::cerr << "can not open camera";
    }
}

//called every time the mouse is moved or interacted with
void Game::onMouseCallBack(int event,int x, int y,int,void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        Game* self = static_cast<Game*>(userdata);//user data is the Game object in the form of a generic void pointer, and we cast it back to Game so we have the data.

        cv::Vec3b hsvVec = self->hsvImage.at<cv::Vec3b>(y,x);
        int h = hsvVec[0];
        int s = hsvVec[1];
        int v = hsvVec[2];

        self->lower = cv::Scalar(std::max(0,h-Constants::H_PAD),std::max(0,s-Constants::S_PAD),std::max(0,v-Constants::V_PAD));
        self->higher = cv::Scalar(std::min(179,h+Constants::H_PAD),std::min(255,s+Constants::S_PAD),std::min(255,v+Constants::V_PAD));
    }
}


void Game::loop() {

    cv::setMouseCallback("Image",onMouseCallBack,this);
    while (true) {
        cap.read(this->screen);
        cv::cvtColor(this->screen,this->hsvImage,cv::COLOR_BGR2HSV);
        cv::inRange(this->hsvImage,this->lower,this->higher,this->maskImage);

        if (this->isConfig) {
            cv::putText(this->screen, "Click your hand to calibrate. Press 's' to start game.",
                            {20, 40}, cv::FONT_HERSHEY_SIMPLEX, 0.7, {0, 255, 255}, 2);

            cv::imshow("Image",this->screen);
            cv::imshow("maskImage",this->maskImage);
            if (cv::waitKey(1) == 's') {
                this->isConfig = false;
            }
            continue;
        }

        //Game logic
        cv::imshow("maskImage",this->maskImage);
        cv::imshow("Image",this->screen);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
}

