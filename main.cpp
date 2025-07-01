#include <opencv2/opencv.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Cannot open camera" << std::endl;
    }

    while (true) {

        cv::Mat frame;
        cap.read(frame);

        cv::imshow("frame", frame);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }
}
