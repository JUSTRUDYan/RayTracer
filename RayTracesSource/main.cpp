#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Camera.h"
#include "HittableList.h"

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(Vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(Vec3(0, -100.5, -1), 100));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400;
    cam.samplesPerPixel = 100;
    cam.max_depth = 50;

    std::ofstream outputFile(filePath);
    cam.render(outputFile, world);
    outputFile.close();
    return 0;
}