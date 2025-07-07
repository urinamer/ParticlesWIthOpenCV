#include "../headers/Game.hpp"




int main() {
    Game game;
    game.loop();
}
/*
cv::Mat hsvImage;
int lH = 106,lS = 46,lV = 72;
int hH = 179,hS = 255,hV = 255 ;

void onMouseCallBack(int event,int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDBLCLK) {
        if (x >= 0 && x < hsvImage.cols && y >= 0 && y < hsvImage.rows) {
            cv::Vec3b hsvVector = hsvImage.at<cv::Vec3b>(y,x);
            int h = hsvVector[0];
            int s = hsvVector[1];
            int v = hsvVector[2];

            lH = std::max(0,h - 10);
            lS = std::max(0,s - 40);
            lV = std::max(0,v - 40);
            hH = std::min(179,h + 10);
            hS = std::min(255,s + 30);
            hV = std::min(255,v + 40);

            cv::setTrackbarPos("L-H","TrackBar",lH);
            cv::setTrackbarPos("L-S","TrackBar",lS);
            cv::setTrackbarPos("L-V","TrackBar",lV);
            cv::setTrackbarPos("H-H","TrackBar",hH);
            cv::setTrackbarPos("H-S","TrackBar",hS);
            cv::setTrackbarPos("H-V","TrackBar",hV);
        }
    }
}


int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Cannot open camera" << std::endl;
    }


    cv::namedWindow("TrackBar");
    cv::createTrackbar("L-H","TrackBar",&lH,179);
    cv::createTrackbar("L-S","TrackBar",&lS,255);
    cv::createTrackbar("L-V","TrackBar",&lV,255);
    cv::createTrackbar("H-H","TrackBar",&hH,179);
    cv::createTrackbar("H-S","TrackBar",&hS,255);
    cv::createTrackbar("H-V","TrackBar",&hV,255);

    cv::Mat image,skinMaskImage;
    while (true) {
        lH = cv::getTrackbarPos("L-H","TrackBar");
        lS = cv::getTrackbarPos("L-S","TrackBar");
        lV = cv::getTrackbarPos("L-V","TrackBar");
        hH = cv::getTrackbarPos("H-H","TrackBar");
        hS = cv::getTrackbarPos("H-S","TrackBar");
        hV = cv::getTrackbarPos("H-V","TrackBar");

        cap.read(image);

        cv::GaussianBlur(image,image,cv::Size(7,7),0);
        cv::cvtColor(image,hsvImage,cv::COLOR_RGB2HSV);
        cv::Scalar lower(lH,lS,lV);
        cv::Scalar higher(hH,hS,hV);
        cv::inRange(hsvImage,lower,higher,skinMaskImage);


        cv::namedWindow("Image");
        cv::setMouseCallback("Image",onMouseCallBack);






        cv::imshow("Image",image);
        cv::imshow("maskImage",skinMaskImage);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
}
*/
