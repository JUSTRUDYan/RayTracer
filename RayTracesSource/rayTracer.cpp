#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Utilities.cpp" 
#include "functions.cpp"

std::ofstream& generationLinearFunction(std::ofstream& outputFile) {
    Color vector;
    LinearFunction linear(1.0, 0.0);

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            if (linear.belongsToFunction(y, x)) {
                vector.setColor(Color(0, 0, 0));
                vector.outPut(outputFile);
            }
            else {
                vector.setColor(Color(255, 255, 255));
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

std::ofstream& generationCircleFunction(std::ofstream& outputFile) {
    Color vector;
    CircleFunction circle(Vec2(128, 128), 50.0);
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            if (circle.isInCircle(x, y)) { //or belongsToFunction
                vector.setColorBasedOnY(y);
                vector.outPut(outputFile);
            }
            else {
                vector.setColorBasedOnY(255 - y);
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

std::ofstream& generationSphereFunction(std::ofstream& outputFile) {
    Color vector;
    SphereFunction sphere(Vec3(128, 128, 128), 50.0);
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
                if (sphere.isSphere(x, y, 128)) {
                    vector.setColor(Color(0, 0, 0));
                    vector.outPut(outputFile);
                }
                else {
                    vector.setColor(Color(255, 255, 255));
                    vector.outPut(outputFile);
                }
        }
    }
    return outputFile;
}

std::ofstream& generationParabolaFunction(std::ofstream& outputFile) {
    Color vector;
    ParabolaFunction Parabola(1, imageWidth / 2);
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            if (Parabola.belongsToReversedFunction(x, y)) {
                vector.setColor(0);
                vector.outPut(outputFile);
            }
            else {
                vector.setColor(Color(255,255,255));
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

std::ofstream& generationGradient(std::ofstream& outputFile) {
    Color colorOfPixel;
    LinearFunction linear(1.0, 0.0);
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            if (linear.belongsToReversedFunction(x, y)) {
                colorOfPixel.setColorBasedOnX(255-x);
                colorOfPixel.outPut(outputFile);
            }
            else {
                colorOfPixel.setColorBasedOnX(x);
                colorOfPixel.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

int main() {

    std::ofstream outputFile(filePath);

    outputFile << "P3\n" << imageWidth << " " << imageHeight<< "\n255\n";
    int choose;
    std::cout << "1: line" << std::endl 
        << "2: parabola" << std::endl 
        << "3: circle" << std::endl 
        << "4: gradient" << std::endl
        << "5: sphere" << std::endl;

    std::cin >> choose;

    if(choose == 1)
        generationLinearFunction(outputFile);
    else if (choose == 2)
        generationParabolaFunction(outputFile);
    else if (choose == 3)
        generationCircleFunction(outputFile);
    else if (choose == 4)
        generationGradient(outputFile);
    else if (choose == 5)
        generationSphereFunction(outputFile);

    outputFile.close();

    std::cout << "Image created successfully!\n";


    return 0;
}
