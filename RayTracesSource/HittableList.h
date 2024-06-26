#pragma once

#include "hittable.h"
#include "Utilities.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, interval rayT, hitRecord& rec) const override {
        hitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = rayT.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(rayT.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};