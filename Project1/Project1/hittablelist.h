#pragma once
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include "hittable.h"
#include <memory>
#include <vector>
using std::shared_ptr;
using std::make_shared;
class hittable_list :public hittable {
public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }
	void add(shared_ptr<hittable> object) { objects.push_back(object); }
	virtual bool hit(const ray& r, double t_min, double t_max,hit_record & rec)const override;
	void clear() { objects.clear(); }
public:
	std::vector<shared_ptr<hittable>> objects;

};
bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record temp;
	bool hitted = false;
	double currentmax = t_max;
	for (const auto& object : objects) {//record the first object ray tracing meets,and rec them,also record the t
		if (object->hit(r, t_min, currentmax, temp)) {
			hitted = true;
			currentmax = temp.t;
			rec = temp;
		}
	}
	return hitted;
}
#endif