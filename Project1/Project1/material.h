#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "hittable.h"
class material {
public:
	virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation,ray &scattered)const =0;//ray is the ray that hit the hitpoint,rec is the hitpoint ,also record the hitnorm,attenuation is the material attenuation rate,scatered and attenuation is output
};
class lambertian :public material {
public:
	lambertian(){}
	lambertian(const color& a) :albedo(a){
	}
	virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation,ray &scattered)const override {//the standard scatter situation
		vec3 target = rec.hitpoint + rec.normal + random_in_hemisphere(rec.normal);
		vec3 dir = target - rec.hitpoint;
		if (dir.near_zero()) {
			dir = rec.normal;
		}
		vec3 origin = rec.hitpoint;
		scattered = ray(origin, dir);
		attenuation = albedo;
		return true;
	}
public:
	color albedo;
};
class metal :public lambertian {
public:
	metal(const color &a,double f):lambertian(a),fuzz(f<1?f:1){}
	virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const override
	{
		vec3 dir = reflect(unit_vector(r.dir), rec.normal);
		scattered = ray(rec.hitpoint, dir+fuzz*random_vecinsphere());
		attenuation = albedo;
		return (dot(dir, rec.normal) > 0);

	}
public:
	 double fuzz;
};
class dielectric :public material {
public:
	dielectric(double index_of_refraction):ir(index_of_refraction){}

	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scatter)const override {
		attenuation = color(1, 1, 1);
		double refraction_ratio = rec.front_face ? (1 / ir) : ir; //n/nprime
		vec3 unit_dir = unit_vector(r.dir);
		double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		vec3 raydir;
		if (refraction_ratio * sin_theta > 1.0||reflectance(cos_theta,refraction_ratio)>random_double()) {
			raydir = reflect(unit_dir, rec.normal);
		}
		else {
			raydir = refract(unit_dir, rec.normal, refraction_ratio);
		}
		scatter = ray(rec.hitpoint, raydir);
		return true;
	}
private:
	double ir;
	static double reflectance(double cosine,double ref_idx) {
		double r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};
#endif
