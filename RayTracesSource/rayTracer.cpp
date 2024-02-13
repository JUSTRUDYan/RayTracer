#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Utilities.h"
#include "main.h"

Color ray_color(const Ray& r) {
	// Нормалізуємо напрямок променю
	Vec3 unit_direction = r.direction.unitVector();

	// Обчислюємо параметр 'a' для створення градієнту
	double a = 0.5 * (unit_direction.y + 1.0);

	// Лінійно змішуємо білий колір і синій колір відповідно до параметру 'a'
	return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}

std::ofstream& render(std::ofstream& outputFile) {
	for (int j = 0; j < imageHeight; ++j) {
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i) {
			Vec3 pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
			Vec3 ray_direction = pixel_center - cameraCenter;
			Ray r(cameraCenter, ray_direction);

			Color pixel_color = ray_color(r);
			pixel_color.writeColor(outputFile);
		}
	}
	    return outputFile;
}