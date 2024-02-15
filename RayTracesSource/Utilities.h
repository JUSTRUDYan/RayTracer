#pragma once

#include <fstream>
#include <cmath>
#include <random>

#include "Interval.h"

const std::string directoryPath = "C:\\Users\\steam\\";
const std::string filePath = directoryPath + "gradient.ppm";

const int thickness = 15;

const double pi = 3.1415926535897932385;

double knowDiscriminant(double a, double b, double c);
double degrees_to_radians(double degrees);

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

class Vec3 {
public:
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    double length() const {
        return sqrt(lengthSquared());
    }

    static double dot(const Vec3& u, const Vec3& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    static Vec3 unitVector(const Vec3& v) {
        return v / v.length();
    }

    static Vec3 randomInUnitSphere() {
        while (true) {
            auto p = Vec3::random(-1, 1);
            if (p.lengthSquared() < 1)
                return p;
        }
    }

    static Vec3 randomUnitVector() {
        return unitVector(randomInUnitSphere());
    }

    inline Vec3 randomOnHemisphere(const Vec3& normal) {
        Vec3 onUnitSphere = randomUnitVector();
        if (dot(onUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return onUnitSphere;
        else
            return -onUnitSphere;
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

    double lengthSquared() const {
        return x * x + y * y + z * z;
    }

    static Vec3 random() {
        return Vec3(random_double(), random_double(), random_double());
    }

    static Vec3 random(double min, double max) {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
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

    Vec3 operator-() const {
        return Vec3(-x, -y, -z);
    }
};

class Color : public Vec3 {
public:
    Color(const Vec3& vec) : Vec3(vec) {}

    Color(double r, double g, double b) : Vec3(r, g, b) {}

    Color& setColor(double r, double g, double b) {
        x = r;
        y = g;
        z = b;
        return *this;
    }

    Color& setColor(Color color) {
        x = color.x;
        y = color.y;
        z = color.z;
        return *this;
    }

    Color operator+(const Color& other) const {
        return Color(x + other.x, y + other.y, z + other.z);
    }

    Color operator-(const Color& other) const {
        return Color(x - other.x, y - other.y, z - other.z);
    }

    Color operator*(double scalar) const {
        return Color(x * scalar, y * scalar, z * scalar);
    }

    friend Color operator*(double scalar, const Color& color) {
        return Color(color.x * scalar, color.y * scalar, color.z * scalar);
    }

    Color operator/(double scalar) const {
        return Color(x / scalar, y / scalar, z / scalar);
    }
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

