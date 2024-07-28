#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cmath>
#include <iostream>

/// OpenCV-only version.
int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture cam;
    std::vector<cv::Mat> channels_vec;
    int pressed_key;

    float a_mod = 0.0f;
    float b_mod = 0.33f;
    float c_mod = 0.66f;

    // cam.open(0);
    cam.open(0);
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

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
        cam.read(frame);
        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        // Split channels.
        cv::split(frame, channels_vec);

        // Update channel values.
        channels_vec[0] *= a_mod;
        channels_vec[1] *= b_mod;
        channels_vec[2] *= c_mod;

        // Merge updated channels.
        cv::merge(channels_vec, frame);

        cv::imshow("badcam", frame);
        pressed_key = cv::waitKey(25);

        if (((char) pressed_key) == 27) {
            // ESC key was pressed.
            break;
        }

        // Unconditionally try and update the window to fullscreen.
        cv::setWindowProperty("badcam", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    }

    return 0;
}