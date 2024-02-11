#pragma once
#include <iostream>
#include <cstdint>
#include <cmath>

#include "Utilities.cpp" 
#include "Functions.h" 
#include "rayTracer.h"

//kx+b
class LinearFunction {
public:
    LinearFunction(double slope, double offset)
        : k(slope), b(offset) {}

    double evaluateLinearFunction(double x) const {
        return k * x + b;
    }

    double reversedEvaluateLinearFunction(double x) const {
        return k * -x + imageSize + b;
    }


    bool belongsToFunction(double x, double y) const {
        return std::abs(y - evaluateLinearFunction(x)) <= thickness;
    }

    bool belongsToReversedFunction(double x, double y) const {
        return std::abs(y - reversedEvaluateLinearFunction(x)) <= thickness;
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

        return difference <= 50;
    }

    bool isInCircle(double x, double y) const {
        return pow(x - center.x, 2) + pow(y - center.y, 2) > pow(radius, 2);
    }


private:
    Vec2 center;
    double radius;
    const double epsilon = 1e-9; // Small value for floating-point comparison
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
        return -pow((a * (x - offset)), 2) + 255;
    }

    //вітки вниз
    bool belongsToFunction(double x, double y) {
        // Порівнюємо відстань між y пікселя та значенням параболи з половиною товщини
        return std::abs(y - evaluateParabolaFunction(x)) <= thickness;
    }


    //вітки вгору
    bool belongsToReversedFunction(double x, double y) const {
        return std::abs(y - evaluateReversedParabolaFunction(x)) <= thickness;
    }

private:
    double a;
    double offset;
};