#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H
#include <memory>
#include "ray.h"
using std::shared_ptr;
class material;
struct hit_record {
	point3 hitpoint;
	vec3 normal;
	double t;
	bool front_face;
	shared_ptr<material> mat_ptr;//hitpoint will tell you the hitpoint,the hitted normal,when to hit,whether outside or inside,and the hit material ,all thing updates after hit function
	inline void set_face_normal(const ray& r, const vec3& outward_normal);
};
class hittable {
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec)const = 0;
};
 void hit_record:: set_face_normal(const ray& r, const vec3& outward_normal) {
	front_face = dot(r.dir, outward_normal)<0;
	if (front_face) {
		normal = outward_normal;
	}
	else {
		normal = -outward_normal;
	}

}
#endif