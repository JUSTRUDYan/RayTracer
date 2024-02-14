#include <iostream>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Utilities.h"
#include "main.h"

double isSphereHit(const Vec3& center, double radius, const Ray& r) {
	Vec3 oc = r.origin - center;
	double a = r.direction.ScalaringWith(r.direction);
	double half_b = oc.ScalaringWith(r.direction);
	auto c = oc.ScalaringWith(oc) - radius * radius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-half_b - sqrt(discriminant)) / -a;
	}
}


Color rayColor(const Ray& r) {
	double t = isSphereHit(Vec3(0.0, 0.0, 1.0), 0.5, r);
	if (t > 0.0) {
		Vec3 N = (r.pointAtParameter(t) - Vec3(0, 0, -1).unitVector());
		return Color(N.x + 1, N.y + 1, N.z + 1) * 0.5;
	}

	// Нормалізуємо напрямок променю
	Vec3 unitDirection = r.direction.unitVector();

	// Обчислюємо параметр 'a' для створення градієнту
	double a = 0.5 * (unitDirection.y + 1.0);

	// Лінійно змішуємо білий колір і синій колір відповідно до параметру 'a'
	return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
}

std::ofstream& render(std::ofstream& outputFile) {
	for (int j = 0; j < imageHeight; ++j) {
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i) {
			Vec3 pixelCenter = pixel00Loc + (pixelDeltaU * i) + (pixelDeltaV * j);
			Vec3 rayDirection = pixelCenter - cameraCenter;
			Ray r(cameraCenter, rayDirection);

			Color pixel_color = rayColor(r);
			pixel_color.writeColor(outputFile);
		}
	}
	    return outputFile;
}