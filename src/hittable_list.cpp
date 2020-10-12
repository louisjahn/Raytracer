//
// Created by Louis Jahn on 9/9/20.
//

#include "hittable_list.h"

hittable_list::hittable_list()
{

}

hittable_list::hittable_list(const hittable_list &copy)
{
    // Not copying content since pointers refer to abstract class
}

hittable_list::~hittable_list()
{
    for (hittable *elem: objects)
    {
        delete(elem);
    }
    objects.clear();
}

hittable_list &hittable_list::operator=(const hittable_list &copy)
{
    // Not copying content since pointers refer to abstract class
    return *this;
}

void hittable_list::add(hittable *elem)
{
    objects.push_back(elem);
}

void hittable_list::clear()
{
    for (hittable *elem: objects)
    {
        delete(elem);
    }
    objects.clear();
}

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
