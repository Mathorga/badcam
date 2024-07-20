#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture cam(0);

    // cam.open(0);
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    // Create a window for display.
    cv::namedWindow("badcam", cv::WINDOW_AUTOSIZE);

    while (cam.read(frame)) {
        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        cv::imshow("badcam", frame);
        cv::waitKey(1);
    }

    return 0;
}