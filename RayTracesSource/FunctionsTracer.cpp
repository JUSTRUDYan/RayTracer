#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>


#include "Utilities.h"
#include "Functions.h"

std::ofstream& generationLinearFunction(std::ofstream& outputFile) {
    Color colorOfPixel;
    LinearFunction linear(1.0, 0.0);

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            if (linear.belongsToFunction(y, x)) {
                colorOfPixel.setColor(Color(0, 0, 0));
                colorOfPixel.outPut(outputFile);
            }
            else {
                colorOfPixel.setColor(Color(255, 255, 255));
                colorOfPixel.outPut(outputFile);
            }
        }
    }
    std::cout << "Image created successfully!\n";
    return outputFile;
}

//std::ofstream& generationCircleFunction(std::ofstream& outputFile) {
//    Color colorOfPixel;
//    CircleFunction circle(Vec2(128, 128), 50.0);
//    for (int y = 0; y < imageHeight; y++) {
//        for (int x = 0; x < imageWidth; x++) {
//            if (circle.isInCircle(x, y)) { //or belongsToFunction
//                colorOfPixel.setColorBasedOnkoef(y);
//                colorOfPixel.outPut(outputFile);
//            }
//            else {
//                colorOfPixel.setColorBasedOnkoef(255 - y);
//                colorOfPixel.outPut(outputFile);
//            }
//        }
//    }
//    std::cout << "Image created successfully!\n";
//    return outputFile;
//}

std::ofstream& generationSphereFunction(std::ofstream& outputFile) {
    Color colorOfPixel;
    SphereFunction sphere(Vec3(imageWidth/2, imageHeight/2, 128), 50.0);
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
                if (sphere.isSphere(x, y, 128)) {
                    colorOfPixel.setColor(Color(0, 0, 0));
                    colorOfPixel.outPut(outputFile);
                }
                else {
                    colorOfPixel.setColor(Color(255, 255, 255));
                    colorOfPixel.outPut(outputFile);
                }
        }
    }
    std::cout << "Image created successfully!\n";
    return outputFile;
}

std::ofstream& generationParabolaFunction(std::ofstream& outputFile) {
    Color colorOfPixel;
    ParabolaFunction Parabola(1, imageWidth / 2);
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            if (Parabola.belongsToReversedFunction(x, y)) {
                colorOfPixel.setColor(0);
                colorOfPixel.outPut(outputFile);
            }
            else {
                colorOfPixel.setColor(Color(255,255,255));
                colorOfPixel.outPut(outputFile);
            }
        }
    }
    std::cout << "Image created successfully!\n";
    return outputFile;
}

//std::ofstream& generationGradient(std::ofstream& outputFile) {
//    Color colorOfPixel;
//    LinearFunction linear(1.0, 0.0);
//    for (int y = 0; y < imageHeight; y++) {
//        for (int x = 0; x < imageWidth; x++) {
//            if (linear.belongsToReversedFunction(x, y)) {
//                colorOfPixel.setColorBasedOnX(255-x);
//                colorOfPixel.outPut(outputFile);
//            }
//            else {
//                colorOfPixel.setColorBasedOnX(x);
//                colorOfPixel.outPut(outputFile);
//            }
//        }
//    }
//    std::cout << "Image created successfully!\n";
//    return outputFile;
//}
