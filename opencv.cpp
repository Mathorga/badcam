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
    cv::VideoCapture preview;
    std::vector<cv::Mat> channels_vec;
    char pressed_key;
    std::chrono::system_clock::time_point time;
    uint64_t millis_since_epoch;

    uint16_t preview_width = 320;
    uint16_t preview_height = 240;

    float a_mod = 0.0f;
    float b_mod = 0.33f;
    float c_mod = 0.66f;

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
        // Update modifiers.
        a_mod += 0.01f;
        if (a_mod > 1.0f) {
            a_mod = 0.0f;
        }
        b_mod += 0.01f;
        if (b_mod > 1.0f) {
            b_mod = 0.0f;
        }
        c_mod += 0.01f;
        if (c_mod > 1.0f) {
            c_mod = 0.0f;
        }

        // Read videocapture feed and make sure it's not empty.
        preview.read(frame);
        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        // Split channels.
        // cv::split(frame, channels_vec);

        // Update channel values.
        // channels_vec[0] *= a_mod;
        // channels_vec[1] *= b_mod;
        // channels_vec[2] *= c_mod;

        // Merge updated channels.
        // cv::merge(channels_vec, frame);

        cv::imshow("badcam", frame);
        pressed_key = (char) cv::waitKey(25);

        if (pressed_key == 27) {
            // ESC key was pressed.
            break;
        }

        if (pressed_key == 32) {
            // Capture time to generate file name.
            time = std::chrono::system_clock::now();
            millis_since_epoch = time.time_since_epoch().count();

            // Save frame to file.
            cv::imwrite("/home/luka/Desktop/capture" + std::to_string(millis_since_epoch) + ".jpg", frame);
        }

        // Unconditionally try and update the window to fullscreen.
        cv::setWindowProperty("badcam", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    }

    return 0;
}
