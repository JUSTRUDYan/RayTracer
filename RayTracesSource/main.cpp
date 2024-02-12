#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "RayTracer.h" 
#include "Utilities.h"
#include "Functions.h"

int main() {

    std::ofstream outputFile(filePath);

    outputFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    int choose;
    std::cout << "1: line" << std::endl
        << "2: parabola" << std::endl
        << "3: circle" << std::endl
        << "4: gradient" << std::endl
        << "5: sphere" << std::endl;

    std::cin >> choose;

    if (choose == 1)
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



    Vec3 origin(1.0, 2.0, 3.0);

    return 0;
}