#pragma once

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

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator*(double scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }
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

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& origin, const Vec3& direction)
        : origin(origin), direction(direction) {}

    Vec3 pointAtParameter(double t) const {
        return origin + direction * t;
    }
};