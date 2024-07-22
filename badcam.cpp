#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <raylib.h>
#include <iostream>

int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture cam;

    float h_modifier = 0.5f;

    // cam.open(0);
    cam.open("/home/luka/pictures/vid.mp4");
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    InitWindow(100, 100, "raylib [textures] example - image drawing");
    ToggleFullscreen();
    const int current_screen = GetCurrentMonitor();
    const float screen_width = GetMonitorWidth(current_screen);
    const float screen_height = GetMonitorHeight(current_screen);

    std::cout << screen_width << std::endl;
    std::cout << screen_height << std::endl;
    Image image;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        h_modifier += 0.01f;
        if (h_modifier > 1.0f) {
            h_modifier = 0.0f;
        }

        // Read videocapture feed and make sure it's not empty.
        cam.read(frame);
        if (frame.empty()) {
            printf("ERROR! blank frame grabbed\n");
            break;
        }

        // Split HSV values.
        cv::Mat hsv_frame;
        std::vector<cv::Mat> hsv_vec;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);
        cv::split(hsv_frame, hsv_vec);

        // Update the hue value.
        hsv_vec[0] = 255.0f * h_modifier;

        // Merge the resulting channels.
        cv::merge(hsv_vec, hsv_frame);

        // Convert color space, since opencv and raylib use different default color spaces.
        cv::cvtColor(hsv_frame, frame, cv::COLOR_HSV2RGB);

        // Copy opencv mat to raylib image.
        image.data = frame.ptr();
        image.height = frame.rows;
        image.width = frame.cols;
        image.format = 4;
        image.mipmaps = 1;

        // Compute texture scaling in order to fit it to the current window.
        float h_ratio = screen_width / image.width;
        float v_ratio = screen_height / image.height;
        float scale = std::min(h_ratio, v_ratio);
        float final_width = image.width * scale;
        float final_height = image.height * scale;

        Texture2D texture = LoadTextureFromImage(image);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(
                texture,
                // Source area (all the texture).
                Rectangle{0, 0, image.width, image.height},
                // Destination area.
                Rectangle{
                    (screen_width / 2) - (final_width / 2),
                    (screen_height / 2) - (final_height / 2),
                    final_width,
                    final_height
                },
                Vector2{0, 0},
                0,
                WHITE
            );
        EndDrawing();

        // UnloadTexture(texture);
    }

    CloseWindow();

    return 0;
}