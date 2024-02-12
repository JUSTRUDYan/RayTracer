#pragma once
#include <string>
#include <fstream>

const std::string directoryPath = "C:\\Users\\steam\\";
const std::string filePath = directoryPath + "gradient.ppm";
const int imageWidth = 160;
const int imageHeight = 90;
const int thickness = 15;

std::ofstream& generationLinearFunction(std::ofstream& outputFile);
std::ofstream& generationCircleFunction(std::ofstream& outputFile);
std::ofstream& generationParabolaFunction(std::ofstream& outputFile);
std::ofstream& generationGradient(std::ofstream& outputFile);
std::ofstream& generationSphereFunction(std::ofstream& outputFile);