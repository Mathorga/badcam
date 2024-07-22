#!/bin/bash

mkdir ./bld
mkdir ./bin

g++ -std=c++17 -Wall -pedantic -g -I/usr/local/include -c ./badcam.cpp -o ./bld/badcam.o -I/usr/include/opencv4
g++ -Wall -L/usr/local/lib ./bld/badcam.o -o ./bin/badcam -Wl,--copy-dt-needed-entries -lm -ldl -lrt -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lraylib
./bin/badcam
