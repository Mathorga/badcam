#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <raylib.h>
#include <iostream>

int main(int argc, char **argv) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    cv::Mat frame;// = cv::imread("/home/luka/Pictures/Screenshots/Screenshotfrom2024-04-1723-33-43.png");
    cv::VideoCapture cam;
    std::string window_title = "badcam";

    cam.open(0);
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    // Create a window for display.
    // cv::namedWindow(window_title, cv::WINDOW_NORMAL);
    // std::cout << "Created window" << std::endl;
    // cv::setWindowProperty(window_title, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    // std::cout << "Set fullscreen" << std::endl;
    // cv::Rect screen_rect = cv::getWindowImageRect(window_title);
    // std::cout << "Captured screen rect" << screen_rect.width << std::endl;
    // cv::Size screen_size = screen_rect.size();
    // std::cout << screen_size.width << std::endl;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image drawing");
    Texture2D texture();

    SetTargetFPS(60);

    while (true) {
        cam.read(frame);

        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        // cv::Mat resized;
        // cv::resize(frame, resized, cv::Size(720, 480));

        cvtColor(frame, frame, COLOR_BGR2RGB);
        texture.data = frame.ptr();
        texture.height = frame.rows;
        texture.width = frame.cols;
        texture.format = 4;
        texture.mipmaps = 1;

        // cv::imshow(window_title, resized);
        // cv::waitKey(25);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}