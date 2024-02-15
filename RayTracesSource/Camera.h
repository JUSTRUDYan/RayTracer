#pragma once

#include <fstream>
#include <cmath>
#include <limits>
#include <memory>

#include "Utilities.h"
#include "HittableList.h"

std::ostream& writeColor(std::ostream& outPutFile, Color pixelColor, int samples_per_pixel) {
	auto r = pixelColor.x;
	auto g = pixelColor.y;
	auto b = pixelColor.z;

	// Divide the color by the number of samples.
	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write the translated [0,255] value of each color component.
	static const interval intensity(0.000, 0.999);
	outPutFile << static_cast<int>(256 * intensity.clamp(r)) << ' '
		<< static_cast<int>(256 * intensity.clamp(g)) << ' '
		<< static_cast<int>(256 * intensity.clamp(b)) << '\n';
	return outPutFile;
}

class Camera {
public:
	double	aspectRatio;
	int		imageWidth; 
	int		samplesPerPixel;
	int		max_depth;

	std::ofstream& render(std::ofstream& outputFile, hittable_list world) {
		initialize();

		outputFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = 0; j < imageHeight; ++j) {
			std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
			for (int i = 0; i < imageWidth; ++i) {
				Color pixelColor(0, 0, 0);
				for (int sample = 0; sample < samplesPerPixel; ++sample) {
					Ray r = getRay(i, j);
					pixelColor = pixelColor + rayColor(r, max_depth, world);
				}
				writeColor(outputFile, pixelColor, samplesPerPixel);
			}
		}

		std::clog << "\rDone.                 \n";
		return outputFile;
	}

private:
	int		imageHeight;   // Rendered image height
	Vec3	cameraCenter;         // Camera center
	Vec3	pixel00Loc;    // Location of pixel 0, 0
	Vec3	pixelDeltaU;  // Offset to pixel to the right
	Vec3	pixelDeltaV;  // Offset to pixel below

	void initialize() {
		imageHeight = static_cast<int>(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		cameraCenter = Vec3(0, 0, 0);

		// Determine viewport dimensions.
		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (static_cast<double>(imageWidth) / imageHeight);

		// Calculate the vectors across the horizontal and down the vertical viewport edges.
		auto viewport_u = Vec3(viewport_width, 0, 0);
		auto viewport_v = Vec3(0, -viewport_height, 0);

		// Calculate the horizontal and vertical delta vectors from pixel to pixel.
		pixelDeltaU = viewport_u / imageWidth;
		pixelDeltaV = viewport_v / imageHeight;

		// Calculate the location of the upper left pixel.
		auto viewport_upper_left = cameraCenter - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
		pixel00Loc = viewport_upper_left + (pixelDeltaU + pixelDeltaV) * 0.5;
	}

	Ray getRay(int i, int j) const {
		// Get a randomly sampled camera ray for the pixel at location i,j.

		auto pixel_center = pixel00Loc + (pixelDeltaU * i) + (pixelDeltaV * j);
		auto pixel_sample = pixel_center + pixelSampleSquare();

		auto ray_origin = cameraCenter;
		auto ray_direction = pixel_sample - ray_origin;

		return Ray(ray_origin, ray_direction);
	}

	Vec3 pixelSampleSquare() const {
		// Returns a random point in the square surrounding a pixel at the origin.
		auto px = -0.5 + random_double();
		auto py = -0.5 + random_double();
		return (pixelDeltaU * px) + (pixelDeltaV * py);
	}

	Color rayColor(const Ray& r, int depth, const hittable& world) const {
		hitRecord rec;

		// If we've exceeded the ray bounce limit, no more light is gathered.
		if (depth <= 0)
			return Color(0, 0, 0);

		if (world.hit(r, interval(0.001, infinity), rec)) {
			Vec3 direction = rec.normal + Vec3::randomUnitVector();
			return 0.5 * rayColor(Ray(rec.p, direction), depth - 1, world);
		}

		Vec3 unitDirection = Vec3::unitVector(r.direction);
		auto a = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}
};