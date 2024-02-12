#pragma once

#include <iostream>
#include <cstdint>
#include <cmath>
#include <fstream>

#include "RayTracer.h"
#include "Utilities.h"

class Vec2 {
public:
    Vec2(int x, int y) : x(x), y(y) {}

    int x;
    int y;
};

class Vec3 {
public:
    Vec3(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    int x;
    int y;
    int z;
};

class Vec4 {
public:
    Vec4(int r = 0, int g = 0, int b = 0, int w = 0) : r(r), g(g), b(b), w(w) {}

    int r;
    int g;
    int b;
    int w;
};

class Color {
public:
    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {}

    // Set color(0-255) based on one coordinate(∞)
    void setColorBasedOnY(int y) {
        setColor(Color(
            static_cast<uint8_t>(255.999 * y / (imageHeight - 1)),
            static_cast<uint8_t>(255.999 * y / (imageHeight - 1)),
            static_cast<uint8_t>(255.999 * y / (imageHeight - 1))
        ));
    }

    void setColorBasedOnX(int x) {
        setColor(Color(
            static_cast<uint8_t>(255.999 * x / (imageWidth - 1)),
            static_cast<uint8_t>(255.999 * x / (imageWidth - 1)),
            static_cast<uint8_t>(255.999 * x / (imageWidth - 1))
        ));
    }

    Color setColor(const Color& otherColor) {
        r = otherColor.r;
        g = otherColor.g;
        b = otherColor.b;
        return *this;
    }

    std::ofstream& outPut(std::ofstream& outputFile) {
        outputFile << static_cast<int>(r) << " " << static_cast<int>(g) << " " << static_cast<int>(b) << " " << std::endl;
        return outputFile;
    }

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
