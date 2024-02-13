#pragma once
#include <iostream>
#include <cstdint>
#include <cmath>

//kx+b
class LinearFunction {
public:
    LinearFunction(double slope, double offset)
        : k(slope), b(offset) {}

    double evaluateLinearFunction(double x) const {
        return k * x + b;
    }

    double reversedEvaluateLinearFunction(double x) const {
        return k * -x + imageHeight + b;
    }


    bool belongsToFunction(double x, double y) const {
        return std::abs(y - evaluateLinearFunction(x)) <= double(thickness / 2);
    }

    bool belongsToReversedFunction(double x, double y) const {
        return std::abs(y - reversedEvaluateLinearFunction(x)) <= double(thickness / 2);
    }

private:
    double k;
    double b;
};

//(x-a)^2 + (y-b)^2 = r^2
class CircleFunction {
public:
    CircleFunction(Vec2 center, double radius)
        : center(center), radius(radius) {}

    double evaluateCircleFunction(double x) const {
        return center.y + std::sqrt(radius * radius - std::pow((x - center.x), 2));
    }

    bool belongsToFunction(double x, double y) const {
        double distanceSquared = std::pow((x - center.x), 2) + std::pow((y - center.y), 2);
        double radiusSquared = std::pow(radius, 2);
        double difference = std::abs(distanceSquared - radiusSquared);

        return difference <= double(thickness / 2);
    }

    bool isInCircle(double x, double y) const {
        return pow(x - center.x, 2) + pow(y - center.y, 2) > pow(radius, 2);
    }


private:
    Vec2 center;
    double radius;
};

//(a(x-offset))^2
class ParabolaFunction {
public:
    ParabolaFunction(double size, double offset)
        : a(size), offset(offset) {}

    double evaluateParabolaFunction(double x) const {
        return pow((a * (x - offset)), 2);
    }

    double evaluateReversedParabolaFunction(double x) const {
        return -pow((a * (x - offset)), 2) + imageHeight - 1;
    }

    //вітки вниз
    bool belongsToFunction(double x, double y) {
        return std::abs(y - evaluateParabolaFunction(x)) <= double(thickness / 2);
    }


    //вітки вгору
    bool belongsToReversedFunction(double x, double y) const {
        return std::abs(y - evaluateReversedParabolaFunction(x)) <= double(thickness / 2);
    }

private:
    double a;
    double offset;
};

class SphereFunction {
public:
    SphereFunction(Vec3 center, double radius)
        : center(center), radius(radius) {}

    double evaluateSphereFunction(int x, int y, int z) const {
        return pow((x - center.x), 2) + pow((y - center.y), 2) + pow((z - center.z), 2);
    }

    bool isSphere(int x, int y, int z) const {
        return evaluateSphereFunction(x, y, z) == pow(radius, 2);
    }


private:
    Vec3 center;
    double radius;
};