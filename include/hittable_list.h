//
// Created by Louis Jahn on 9/9/20.
//

#ifndef RAYTRACER___INTRO_HITTABLE_LIST_H
#define RAYTRACER___INTRO_HITTABLE_LIST_H

#include <vector>
#include "hittable.h"

class hittable_list : public hittable
{
public:
    hittable_list();
    hittable_list(const hittable_list &copy);

    virtual ~hittable_list();

    hittable_list &operator=(const hittable_list &copy);

    void add(hittable *elem);
    void clear();

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const;
public:
    std::vector<hittable *> objects;
};


#endif //RAYTRACER___INTRO_HITTABLE_LIST_H
