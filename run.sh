#!/bin/bash

g++ -std=c++17 -Wall -pedantic -g -I/usr/local/include -c ./badcam.cpp -o ./badcam.o -I/usr/include/opencv4
g++ -Wall ./badcam.o -o ./badcam -lm -lrt -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
./badcam