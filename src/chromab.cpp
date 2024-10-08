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
#include <vector>

/// OpenCV-only version.
int main(int argc, char **argv) {
    std::string window_title = "badcam";
    std::vector<cv::Mat> old_frames;
    std::vector<cv::Mat> frame_channels;
    std::vector<cv::Mat> blend_channels;
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

        // Add the current frame to the blend list.
        old_frames.push_back(curr_frame.clone());

        // Split frame channels.
        cv::split(curr_frame, frame_channels);

        // Only start working on frames when there's at least three channels ready.
        if (old_frames.size() >= 3) {
            // Clear output vector.
            blend_channels.clear();

            // Loop through previous frames.
            for (uint8_t i = 0; i < old_frames.size(); i++) {
                // Split the current frame into its channels.
                cv::split(old_frames[i], frame_channels);

                // Add the ith channel to the output vector.
                blend_channels.push_back(frame_channels[i].clone());
            }

            // Remerge channels from the previous frames.
            cv::merge(blend_channels, blend_frame);

            cv::resize(blend_frame, display_frame, cv::Size(screen_width, screen_height));
            cv::imshow(window_title, display_frame);
            pressed_key = (char) cv::waitKey(100);

            if (pressed_key == 27 || pressed_key == 113) {
                // ESC or Q key was pressed.
                break;
	    }
        }

        // Pop the first reverb frame out if reverb size is exceeded.
        if (old_frames.size() > 2) {
            old_frames.erase(old_frames.begin());
        }
    }

    return 0;
}
