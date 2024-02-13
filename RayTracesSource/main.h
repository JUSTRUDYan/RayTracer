#pragma once

#include <string>;

#include "Utilities.h"

Vec3 cameraCenter(0, 0, 0);

// Calculate the vectors across the horizontal and down the vertical viewport edges.
Vec3 viewport_u(viewport_width, 0, 0);
Vec3 viewport_v(0, -viewport_height, 0);

// Calculate the horizontal and vertical delta vectors from pixel to pixel.
Vec3 pixel_delta_u = viewport_u / imageWidth;
Vec3 pixel_delta_v = viewport_v / imageHeight;

// Calculate the location of the upper left pixel.
Vec3 viewport_upper_left = cameraCenter - Vec3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
Vec3 pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

std::ofstream& render(std::ofstream& outputFile);
