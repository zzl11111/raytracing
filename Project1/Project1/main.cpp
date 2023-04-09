#include <iostream>
#include "vec3.h"
#include "sphere.h"
#include "hittablelist.h"
#include "color.h"
#include "ray.h"
#include "camera.h"
#include "rtinoneweekconstant.h"
#include "material.h"
using std::make_shared;
color ray_color(const ray& r,const hittable_list& hitlist,int depth)
{
	if (depth <= 0)
		return color(0, 0, 0);
	hit_record rec;
	double t;
	if (hitlist.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		vec3 attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * ray_color(scattered, hitlist, depth - 1);
		}
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.dir);
	 t = 0.5 * (unit_direction.y() + 1.0);
	color raycolor = (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	return raycolor;
}
hittable_list random_scene() {
	hittable_list hitlist;
	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	hitlist.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center( (a + 0, 9 * random_double()), 0.2, b + 0.9 * random_double());
			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;
				if (choose_mat < 0.8) {
					auto albedo = random(0,1)*random(0,1);
					sphere_material = make_shared<lambertian>(albedo);
					hitlist.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if(choose_mat<0.95){
					auto albedo = random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					hitlist.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					sphere_material = make_shared<dielectric>(1.5);
					hitlist.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}

		}
	}
	auto material1 = make_shared<dielectric>(1.5);
	hitlist.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	hitlist.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	hitlist.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	return hitlist;
}
int main() {
	const double aspect_ratio = 16.0 / 9.0;
	camera cam(point3(13,2,3),point3(0,0,0),vec3(0,1,0),20,aspect_ratio);
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width/aspect_ratio);
	const int numberofsample = 100;
	const int max_depth = 50;
	/*initialize the point*/
	/*add some sphere*/
	hittable_list hitlist=random_scene();
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	//initialize the image

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining:" << j << "\n " << std::flush;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color;//sample to calculate the ray color
			for (int k = 0; k < numberofsample; k++) {
				auto u = (double(i)+random_double()) / (image_width - 1);
				auto v =( double(j)+random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);//from the pixel to get the real ray
				pixel_color += ray_color(r, hitlist,max_depth);
			}

			write_color(std::cout,pixel_color,numberofsample);
		}
   }
	std::cerr << "\nDone.\n";
	return 0;
}