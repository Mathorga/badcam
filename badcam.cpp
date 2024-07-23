#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.gpp>
#include <opencv2/imgcodecs.hpp>
#include <cmath>
#include <iostream>

/// OpenCV-only version.
int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture cam;
    std::vector<cv::Mat> channels_vec;

    float a_mod = 0.0f;
    float b_mod = 0.33f;
    float c_mod = 0.66f;

    // cam.open(0);
    cam.open("/home/luka/pictures/vid.mp4");
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    // Create a window to display textures on screen.
    cv::namedWindow("badcam", cv::WINDOW_NORMAL);

    std::cout << screen_width << std::endl;
    std::cout << screen_height << std::endl;

    for (;;) {
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

        // // Convert color space.
        // cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        // // Split channels.
        // cv::split(frame, channels_vec);

        // // Update channel values.
        // channels_vec[0] *= a_mod;
        // channels_vec[1] *= b_mod;
        // channels_vec[2] *= c_mod;

        // // Merge updated channels.
        // cv::merge(channels_vec, frame);

        // Compute texture scaling in order to fit it to the current window.
        float h_ratio = screen_width / image.width;
        float v_ratio = screen_height / image.height;
        float scale = std::min(h_ratio, v_ratio);
        float final_width = image.width * scale;
        float final_height = image.height * scale;

        cv::imshow("badcam", frame);
    }

    UnloadImage(image);
    CloseWindow();

    return 0;
}