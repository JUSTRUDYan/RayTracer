#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "functions.h"
#include "rayTracer.h"

#include "Utilities.cpp" 
#include "functions.cpp"

std::ofstream& generationLinearFunction(std::ofstream& outputFile) {
    Color vector;
    LinearFunction linear(1.0, 0.0);

    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            if (linear.belongsToFunction(i, j)) {
                vector.setAllColor(0);
                vector.outPut(outputFile);
            }
            else {
                vector.setAllColor(255);
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}


std::ofstream& generationCircleFunction(std::ofstream& outputFile) {
    Color vector;
    CircleFunction circle(Vec2(128, 128), 50.0);
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            if (circle.isInCircle(j, i)) { //or belongsToFunction
                vector.setAllColor(i);
                vector.outPut(outputFile);
            }
            else {
                vector.setAllColor(255-i);
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

std::ofstream& generationParabolaFunction(std::ofstream& outputFile) {
    Color vector;
    ParabolaFunction Parabola(1, imageSize / 2);
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            if (Parabola.belongsToReversedFunction(j, i)) {
                vector.setAllColor(0);
                vector.outPut(outputFile);
            }
            else {
                vector.setAllColor(255);
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

std::ofstream& generationGradient(std::ofstream& outputFile) {
    Color vector;
    LinearFunction linear(1.0, 0.0);
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            if (linear.belongsToReversedFunction(j, i)) {
                vector.setBrightness((255 - j));
                vector.outPut(outputFile);
            }
            else {
                vector.setBrightness((j));
                vector.outPut(outputFile);
            }
        }
    }
    return outputFile;
}

int main() {

    std::ofstream outputFile(filePath);

    outputFile << "P3\n" << imageSize << " " << imageSize << "\n255\n";
    int choose;
    std::cout << "1: line" << std::endl 
        << "2: parabola" << std::endl 
        << "3: circle" << std::endl 
        << "4: gradient" << std::endl;

    std::cin >> choose;

    if(choose == 1)
        generationLinearFunction(outputFile);
    else if (choose == 2)
        generationParabolaFunction(outputFile);
    else if (choose == 3)
        generationCircleFunction(outputFile);
    else if (choose == 4)
        generationGradient(outputFile);

    outputFile.close();

    std::cout << "Image created successfully!\n";

    return 0;
}
