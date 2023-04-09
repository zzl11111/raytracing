#pragma once
#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include <iostream>
#include "rtinoneweekconstant.h"
void write_color(std::ostream& out, color pixel_color,int numberofsample) {
	//get the origin pixel_color
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	//use gamme to correct them
	r = sqrt(r * 1 / numberofsample);
	g = sqrt(g* 1 / numberofsample);
	b = sqrt(b * 1 / numberofsample);
	//clamp to 0,0.999
	r = clamp(r, 0, 0.999);
	g = clamp(g, 0, 0.999);
	b = clamp(b, 0, 0.999);
	out << static_cast<int>(256*r) << " " << static_cast<int>(256 * g) << " " << static_cast<int>(256*b) << "\n";
//write the color from (0,1)->(0,255)
}
#endif