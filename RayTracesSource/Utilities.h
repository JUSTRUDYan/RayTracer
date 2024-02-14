#pragma once

#include <fstream>

const std::string directoryPath = "C:\\Users\\steam\\";
const std::string filePath = directoryPath + "gradient.ppm";

const double aspect_ratio = 16.0 / 9.0;
const int imageWidth = 400;
const int imageHeight = static_cast<int>(imageWidth / aspect_ratio);
const double focalLength = 1.0;

const double viewport_height = 2.0;
const double viewport_width = viewport_height * (static_cast<double>(imageWidth) / imageHeight);

const int thickness = 15;


class Vec2 {
public:
    Vec2(int x, int y) : x(x), y(y) {}

    int x;
    int y;
};

class Vec3 {
public:
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 unitVector() const {
        double length = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / length, y / length, z / length);
    }

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator-(double scalar) const {
        return Vec3(x - scalar, y - scalar, z - scalar);
    }

    Vec3 operator*(double scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator*(Vec3 other) const {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    double ScalaringWith(Vec3 other) const {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    Vec3 operator/(double scalar) const {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    Vec3 operator^(double scalar) const {
        return Vec3(pow(x, scalar), pow(y, scalar), pow(z, scalar));
    }
};

class Color {
public:
    Color(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {}

    // Set color(0-255) based on one coordinate(∞)

    std::ofstream& writeColor(std::ofstream& outputFile) {
        // Write the translated [0,255] value of each color component.
        outputFile << static_cast<int>(255.999 * r) << ' '
            << static_cast<int>(255.999 * g) << ' '
            << static_cast<int>(255.999 * b) << '\n';
        return outputFile;
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

    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b);
    }

    Color operator-(const Color& other) const {
        return Color(r - other.r, g - other.g, b - other.b);
    }

    Color operator*(double scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color operator*(Color other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    Color operator/(double scalar) const {
        return Color(r / scalar, g / scalar, b / scalar);
    }

private:
    double r;
    double g;
    double b;
};

class Ray {
public:
    Ray(const Vec3& origin, const Vec3& direction)
        : origin(origin), direction(direction) {}

    Vec3 pointAtParameter(double t) const {
        return origin + direction * t;
    }

    Vec3 origin;
    Vec3 direction;
};

double knowDiscriminant(double a, double b, double c);