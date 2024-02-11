#pragma once

#include <iostream>
#include <cstdint>
#include <cmath>
#include <fstream>

#include "rayTracer.h"

class Vec2 {
public:
    Vec2(int x, int y) : x(x), y(y) {}

    int x;
    int y;
};

class Vec3 {
public:
    Vec3(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
private:
    int x;
    int y;
    int z;
};

class Vec4 {
public:
    Vec4(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0) : r(r), g(g), b(b), w(w) {}

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t w;
};

class Color {
public:
    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {}

    Color& setBrightness(int brightnessKoef) {
        setAllColor(static_cast<uint8_t>(255.999 * brightnessKoef / (imageSize - 1)));
        return *this;
    }

    Color setAllColor(int color) {
        r = color;
        g = color;
        b = color;
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