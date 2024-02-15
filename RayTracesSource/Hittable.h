#pragma once

#include "Interval.h"
#include "Utilities.h"

class hitRecord {
public:
    Vec3 p;
    Vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = r.direction.ScalaringWith(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const Ray& r, interval ray_t, hitRecord& rec) const = 0;
};

class sphere : public hittable {
public:
    sphere(Vec3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const Ray& r, interval rayT, hitRecord& rec) const override {
        Vec3 oc = r.origin - center;
        double a = r.direction.lengthSquared();
        double half_b = oc.ScalaringWith(r.direction);
        double c = oc.lengthSquared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!rayT.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.pointAtParameter(rec.t);
        Vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    Vec3 center;
    double radius;
};
