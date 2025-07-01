#include <opencv2/opencv.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>


cv::Mat hsvImage;


void onMouseCallBack(int event,int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_MOUSEMOVE) {
        if (x >= 0 && x < hsvImage.cols && y >= 0 && y < hsvImage.rows) {
            cv::Vec3b hsvVector = hsvImage.at<cv::Vec3b>(y,x);
            int h = hsvVector[0];
            int s = hsvVector[1];
            int v = hsvVector[2];

            std::cout << "h : " << h << " s: " << s << " v: " << v << "\n";
        }
    }
}


int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Cannot open camera" << std::endl;
    }
    std::cout << "start \n";

    int lH = 120,lS = 20,lV = 100 ;
    int hH = 130,hS = 255,hV = 255 ;
    cv::namedWindow("TrackBar");
    cv::createTrackbar("L-H","TrackBar",&lH,179);
    cv::createTrackbar("L-S","TrackBar",&lS,255);
    cv::createTrackbar("L-V","TrackBar",&lV,255);
    cv::createTrackbar("H-H","TrackBar",&hH,179);
    cv::createTrackbar("H-S","TrackBar",&hS,255);
    cv::createTrackbar("H-V","TrackBar",&hV,255);

    cv::Mat image,maskImage;
    while (true) {
        lH = cv::getTrackbarPos("L-H","TrackBar");
        lS = cv::getTrackbarPos("L-S","TrackBar");
        lV = cv::getTrackbarPos("L-V","TrackBar");
        hH = cv::getTrackbarPos("H-H","TrackBar");
        hS = cv::getTrackbarPos("H-S","TrackBar");
        hV = cv::getTrackbarPos("H-V","TrackBar");

        cap.read(image);
        cv::cvtColor(image,hsvImage,cv::COLOR_RGB2HSV);
        cv::Scalar lower(lH,lS,lV);
        cv::Scalar higher(hH,hS,hV);
        cv::inRange(hsvImage,lower,higher,maskImage);


        cv::namedWindow("Image");
        cv::setMouseCallback("Image",onMouseCallBack);




        cv::imshow("Image",image);
        cv::imshow("maskImage",maskImage);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }
}
