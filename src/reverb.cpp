#include <stdio.h>
#include <stdint.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cmath>
#include <iostream>
#include <chrono>
#include <list>

/// OpenCV-only version.
int main(int argc, char **argv) {
    std::string window_title = "badcam";
    uint8_t reverb_size = 4;
    std::list<cv::Mat> reverb_frames;
    // cv::Mat prev_frame;
    cv::Mat curr_frame;
    cv::Mat blend_frame;
    cv::Mat display_frame;
    cv::VideoCapture preview;
    char pressed_key;
    std::chrono::system_clock::time_point time;

    uint16_t preview_width = 320;
    uint16_t preview_height = 240;

    uint16_t screen_width = 720;
    uint16_t screen_height = 480;

    preview.open(0);
    if (!preview.isOpened()) {
        printf("ERROR! Unable to open camera for preview\n");
        return -1;
    }

    // Set camera resolution.
    preview.set(cv::CAP_PROP_FRAME_WIDTH, preview_width);
    preview.set(cv::CAP_PROP_FRAME_HEIGHT, preview_height);

    // Create a window to display images on screen.
    cv::namedWindow(window_title, cv::WINDOW_NORMAL);
    cv::setWindowProperty(window_title, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

    for (;;) {
        // Read videocapture feed and make sure it's not empty.
        preview.read(curr_frame);
        if (curr_frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        // Copy the current frame to the blend frame.
        curr_frame.copyTo(blend_frame);

        // Loop through reverb frames and add them one by one.
        for (cv::Mat frame : reverb_frames) {
            cv::addWeighted(frame, 0.5, blend_frame, 0.5, 0.0, blend_frame);
        }

        cv::resize(blend_frame, display_frame, cv::Size(screen_width, screen_height));
        cv::imshow(window_title, display_frame);
        pressed_key = (char) cv::waitKey(25);

        if (pressed_key == 27 || pressed_key == 113) {
            // ESC or Q key was pressed.
            break;
        }

        // Push the current frame in reverb.
        reverb_frames.push_back(curr_frame.clone());

        // Pop the first reverb frame out if reverb size is exceeded.
        if (reverb_frames.size() > reverb_size) {
            reverb_frames.pop_front();
        }
    }

    return 0;
}
