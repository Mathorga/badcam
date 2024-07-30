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

/// OpenCV-only version.
int main(int argc, char **argv) {
    std::string window_title = "badcam";
    cv::Mat preview_frame;
    cv::Mat capture_frame;
    cv::VideoCapture preview;
    // std::vector<cv::Mat> channels_vec;
    char pressed_key;
    std::chrono::system_clock::time_point time;
    uint64_t millis_since_epoch;

    uint16_t preview_width = 320;
    uint16_t preview_height = 240;

    uint16_t capture_width = 1280;
    uint16_t capture_height = 960;

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
        preview.read(preview_frame);
        if (preview_frame.empty()) {
            printf("ERROR! blank preview_frame grabbed\n");
            break;
        }

        // Split channels.
        // cv::split(preview_frame, channels_vec);

        // Update channel values.
        // TODO

        // Merge updated channels.
        // cv::merge(channels_vec, preview_frame);

        cv::imshow(window_title, preview_frame);
        pressed_key = (char) cv::waitKey(25);

        if (pressed_key == 27) {
            // ESC key was pressed.
            break;
        }

        if (pressed_key == 32) {
            // Capture time to generate file name.
            time = std::chrono::system_clock::now();
            millis_since_epoch = time.time_since_epoch().count();

            // Update the camera resolution for capture.
            preview.set(cv::CAP_PROP_FRAME_WIDTH, capture_width);
            preview.set(cv::CAP_PROP_FRAME_HEIGHT, capture_height);

            // Capture image in capture resolution.
            preview.read(capture_frame);

            // Reset camera resolution to preview.
            preview.set(cv::CAP_PROP_FRAME_WIDTH, preview_width);
            preview.set(cv::CAP_PROP_FRAME_HEIGHT, preview_height);

            // Save preview_frame to file.
            cv::imwrite("/home/luka/Desktop/capture" + std::to_string(millis_since_epoch) + ".jpg", capture_frame);
        }
    }

    return 0;
}
