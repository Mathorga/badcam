#include <stdio.h>
#include <raylib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cmath>
#include <iostream>

int main(int argc, char **argv) {
    cv::Mat frame;
    cv::VideoCapture cam;
    std::vector<cv::Mat> channels_vec;

    float a_mod = 0.0f;
    float b_mod = 0.33f;
    float c_mod = 0.66f;

    cam.open(0);
    // cam.open("/home/luka/pictures/vid.mp4");
    if (!cam.isOpened()) {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    // Create a window to display textures on screen.
    InitWindow(1920, 1080, "badcam");
    ToggleFullscreen();

    const int current_screen = GetCurrentMonitor();
    const float screen_width = GetMonitorWidth(current_screen);
    // const float screen_width = GetScreenWidth();
    const float screen_height = GetMonitorHeight(current_screen);
    // const float screen_height = GetScreenHeight();

    std::cout << screen_width << std::endl;
    std::cout << screen_height << std::endl;

    Image image;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
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

        // Convert color space.
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        // Split channels.
        cv::split(frame, channels_vec);

        // Update channel values.
        channels_vec[0] *= a_mod;
        channels_vec[1] *= b_mod;
        channels_vec[2] *= c_mod;

        // Merge updated channels.
        cv::merge(channels_vec, frame);

        // Copy opencv mat to raylib image and then to texture.
        image.data = frame.ptr();
        image.height = frame.rows;
        image.width = frame.cols;
        image.format = 4;
        image.mipmaps = 1;
        Texture2D texture = LoadTextureFromImage(image);

        // Compute texture scaling in order to fit it to the current window.
        float h_ratio = screen_width / image.width;
        float v_ratio = screen_height / image.height;
        float scale = std::min(h_ratio, v_ratio);
        float final_width = image.width * scale;
        float final_height = image.height * scale;

        BeginDrawing();
            ClearBackground(Color());
            DrawTexturePro(
                texture,
                // Source area (all the texture).
                Rectangle{0, 0, (float) image.width, (float) image.height},
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

        UnloadTexture(texture);
    }

    UnloadImage(image);
    CloseWindow();

    return 0;
}