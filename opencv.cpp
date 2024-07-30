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
    cv::Mat frame;
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

    // Create a window to display textures on screen.
    cv::namedWindow("badcam", cv::WINDOW_NORMAL);

    for (;;) {
        // Read videocapture feed and make sure it's not empty.
        preview.read(frame);
        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        // Split channels.
        // cv::split(frame, channels_vec);

        // Update channel values.
        // TODO

        // Merge updated channels.
        // cv::merge(channels_vec, frame);

        cv::imshow("badcam", frame);
        pressed_key = (char) cv::waitKey(25);

        // Unconditionally try and update the window to fullscreen.
        cv::setWindowProperty("badcam", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);

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

            // Save frame to file.
            cv::imwrite("/home/luka/Desktop/capture" + std::to_string(millis_since_epoch) + ".jpg", capture_frame);
        }
    }

    return 0;
}
