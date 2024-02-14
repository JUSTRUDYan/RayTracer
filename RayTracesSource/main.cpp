#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Utilities.h"
#include "FunctionsTracer.h"
#include "RayTracer.h"

int main() {

    if (imageHeight < 0) {
        std::cout << "imageHeight < 0 - true";
        exit(0);
    }

    std::ofstream outputFile(filePath);

    outputFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    int choose;
    std::cout << "1: line" << std::endl
        << "2: parabola" << std::endl
        << "3: circle" << std::endl
        << "4: gradient" << std::endl
        << "5: sphere" << std::endl;


    //if (choose == 1)
    //    generationLinearFunction(outputFile);
    //else if (choose == 2)
    //    generationParabolaFunction(outputFile);
    //else if (choose == 3)
    //    generationCircleFunction(outputFile);
    //else if (choose == 4)
    //    generationGradient(outputFile);
    //else if (choose == 5)
    //    generationSphereFunction(outputFile);

    render(outputFile);

    outputFile.close();

    return 0;
}