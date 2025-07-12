

#include "../headers/Game.hpp"
#include "../headers/Constants.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>
#include <memory>

Game::Game() {
    this->cap = cv::VideoCapture(0);
    this->isConfig = true;
    this-> lower = cv::Scalar(0,0,0);
    this-> higher = cv::Scalar(0,0,0);
    this->round = 0;
    this->hp;


    fruits.push_back(Fruit(10,"/home/arielhirsch/codingProjects/C++/ParticlesWIthOpenCV/images/watermelon.png",0.5,-18));

    cv::namedWindow("Image");
    cv::resizeWindow("Image",Constants::SCREEN_WIDTH,Constants::SCREEN_HEIGHT);
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
void Game::renderFruits() {

    //erases fruit who fall down under the screen
    fruits.erase(
        std::remove_if(fruits.begin(),fruits.end(),[&](const Fruit& fruit) {//We use remove_if to get a pointer to the end of the valid values and then erase deletes all the non-valid values. Remember how lambdas work
                    return fruit.getY() >= this->screen.rows && fruit.getYVelocity() > 0;
        }),fruits.end()
    );


    for (Fruit& fruit : fruits) {
        cv::Mat fruitOverlay = cv::imread(fruit.getImage());
        cv::resize(fruitOverlay,fruitOverlay,cv::Size(Constants::WIDTH_HEIGHT,Constants::WIDTH_HEIGHT));


        if (fruit.getX() < this->screen.cols && fruit.getY() < this->screen.rows) {//checks that the image is not out of bounds,safety check.
            double height = fruitOverlay.rows;
            if (this->screen.rows - fruit.getY() < fruitOverlay.rows) {
                height = this->screen.rows - fruit.getY();
                fruitOverlay = fruitOverlay(cv::Rect(0,0,fruitOverlay.cols,static_cast<int>(height)));//crops the image
            }
            if (static_cast<int>(height) > 0)
                fruitOverlay.copyTo(this->screen(cv::Rect(static_cast<int>(fruit.getX()),static_cast<int>(fruit.getY()),fruitOverlay.cols,static_cast<int>(height))));
        }
        fruit.move();
    }

}

void Game::loop() {

    cv::setMouseCallback("Image",onMouseCallBack,this);
    while (true) {
        cap.read(this->screen);
        cv::GaussianBlur(this->screen,this->bluredImage,cv::Size(7,7),0);//adjust for accuracy
        cv::cvtColor(this->bluredImage,this->hsvImage,cv::COLOR_BGR2HSV);
        cv::inRange(this->hsvImage,this->lower,this->higher,this->maskImage);
        //remove noise
        cv::erode(hsvImage,hsvImage,cv::Mat(),cv::Point(-1,-1),2);
        cv::dilate(hsvImage,hsvImage,cv::Mat(),cv::Point(-1,-1),2);

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
        detectFinger();
        renderFruits();//needs to be before the imshow so it will be on top of the image.

        cv::imshow("maskImage",this->maskImage);
        cv::imshow("Image",this->screen);



        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
}


void Game::detectFinger() {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(maskImage,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
    int largestContourIndex = 0;
    double maxArea = 0;
    for (int i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);

        if (area > maxArea) {
            largestContourIndex = i;
            maxArea = area;
        }
    }
    if (contours.empty()) {
        return;
    }
    cv::Rect handBox = cv::boundingRect(contours[largestContourIndex]);
    cv::Rect fingerRegion(handBox.x,handBox.y,handBox.width,handBox.height*0.3);

    cv::Mat fingerMask = maskImage(fingerRegion);
    std::vector<std::vector<cv::Point>> fingerContours;
    cv::findContours(fingerMask,fingerContours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);


    if (!fingerContours.empty()) {
        cv::Rect fingerRect = cv::boundingRect(fingerContours[0]);
        fingerRect.x += handBox.x;
        fingerRect.y += handBox.y;
        cv::rectangle(this->screen,fingerRect,cv::Scalar(255,0,0),3);
    }

    drawSliceEffect(handBox.x,handBox.y);
}

void Game::drawSliceEffect(int x, int y) {
    std::vector<std::unique_ptr<FingerTrail>> trailsToAdd;

    auto time = std::chrono::high_resolution_clock::now();

    if (this->fingerTrails.size() < 15) {
        std::unique_ptr<FingerTrail> trailPointer=  std::make_unique<FingerTrail>(time,x,y);
        this->fingerTrails.push_back(std::move(trailPointer));//moves ownership of the unique pointer to the vector
    }
    for (auto it = this->fingerTrails.begin();  it != fingerTrails.end();) {//uses a manual iterator because we are removing things

        //draws trail
        cv::circle(this->screen,cv::Point(it->get()->getX(),it->get()->getY()),Constants::FINGER_TRAIL_RADIUS,cv::Scalar(255,0,0),-1);

        double duration = std::chrono::duration<double>(time-it->get()->getStartTime()).count();//convert to double
        if (duration >= it->get()->getDuration()) {
            //remove trail
            it = this->fingerTrails.erase(it);//NOTE: EXPENSIVE OPERATION

            //creates new trail
            std::unique_ptr<FingerTrail> trailPointer=  std::make_unique<FingerTrail>(time,x,y);
            trailsToAdd.push_back(std::move(trailPointer));
        }
        else {
            ++it;//moves the iterator to the next "node"
        }

    }


    //adds the new trails
    for (int j = 0; j < trailsToAdd.size(); j++) {
        this->fingerTrails.push_back(std::move(trailsToAdd[j]));
    }


}










