#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
#include "rtinoneweekconstant.h"
#include "ray.h"
//define the class of sphere
class sphere :public hittable {
public:
	sphere() {}
	sphere(point3 c, double r,shared_ptr<material> m) :center(c),radius(r),mat_ptr(m){};
	virtual bool hit(const ray& r, double t_min,double t_max,hit_record &hit) const override;
public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& hit)const {
	vec3 dcenter = r.orig - center;
	double a = dot(r.dir, r.dir);
	double b = 2 * dot(r.dir, dcenter);
	double c = dot(dcenter, dcenter) - radius * radius;
	double delta = b * b - 4 * a * c;

	if (delta < 0) {
		return false;
	}
	
	double root =( -b - sqrt(delta)) / (2 * a);//suppose the nearest
	if (root<t_min || root>t_max) {
		//change the root
		root = (-b + sqrt(delta)) / (2 * a);
		if (root<t_min || root>t_max) {
			
			return false;
		}
	}
	hit.t = root;
	hit.hitpoint = r.at(hit.t);
	hit.mat_ptr = mat_ptr;
	vec3 outnormal = unit_vector(hit.hitpoint - center);
	hit.set_face_normal(r, outnormal);
	
	return true;

}
#endif