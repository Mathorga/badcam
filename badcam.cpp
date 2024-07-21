#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int main(int argc, char **argv) {
    cv::Mat frame;// = cv::imread("/home/luka/Pictures/Screenshots/Screenshotfrom2024-04-1723-33-43.png");
    cv::VideoCapture cam;
    std::string window_title = "badcam";

    cam.open(0);
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    // Create a window for display.
    cv::namedWindow(window_title, cv::WINDOW_NORMAL);
    std::cout << "Created window" << std::endl;
    cv::setWindowProperty(window_title, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    std::cout << "Set fullscreen" << std::endl;
    // cv::Rect screen_rect = cv::getWindowImageRect(window_title);
    // std::cout << "Captured screen rect" << screen_rect.width << std::endl;
    // cv::Size screen_size = screen_rect.size();
    // std::cout << screen_size.width << std::endl;

    while (true) {
        cam.read(frame);

        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        cv::Mat resized;
        cv::resize(frame, resized, cv::Size(720, 480));

        cv::imshow(window_title, resized);
        cv::waitKey(25);
    }

    return 0;
}