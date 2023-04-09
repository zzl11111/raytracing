#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>
#include <random>
const auto s = 1e-8;
class vec3 {
public:
	vec3() :r{ 0,0,0 } {}
	vec3(double r0, double r1, double r2) :r{r0,r1,r2}{}
	vec3(const vec3& v) :r{ v.x(),v.y(),v.z() } {}
	double x()const { return r[0]; }
	double y()const { return r[1]; }
	double z() const { return r[2]; }
	vec3 operator-() const { return vec3(-r[0], -r[1], -r[2]); }
	double operator[](int i)const { return r[i]; }
	double& operator[](int i) { return r[i]; }
	bool near_zero()const {
		if (fabs(r[0] < s) && fabs(r[1]) < s && fabs(r[2]) < s) {
			return true;
		}
		return false;
	}
	vec3 operator *(const vec3& v) { return vec3(r[0] * v.r[0], r[1] * v.r[1], r[2] * v.r[2]); }
	vec3& operator +=(const vec3& v) {

		r[0] += v.r[0];
		r[1] += v.r[1];
		r[2] += v.r[2];
		return *this;
	}
	vec3 operator+(const vec3& v)const { return vec3(r[0] + v.x(), r[1] + v.y(), r[2] + v.z()); }

	vec3& operator *=(const double t) { r[0] *= t; r[1] *= t, r[2] *= t; return *this; }
	vec3& operator/=(const double t) {
		return *this *= 1 / t;
	}
	double length() const {
		return std::sqrt(squared());
	}
	double squared()const {
		return r[0] * r[0] + r[1] * r[1] + r[2] * r[2];
	}
private:
	double r[3];
};
inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return v1 + -(v2);
}
inline vec3 operator*(const vec3& v, double t) {
	return vec3(v.x() * t, v.y() * t, v.z() * t);


}
inline vec3 operator*(double t, const vec3& v) {
	return v * t;
}//reload the operator *
inline vec3 operator/(vec3 v, double t) {
	return v * (1 / t);
}
inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x());
}
inline double dot(const vec3& v1, const vec3& v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}
inline vec3 refract(const vec3& dir, const vec3& n, double etaidivideetaprime) {
	auto cos_theta = fmin(dot(-dir, n), 1.0);
	vec3 r_perp = etaidivideetaprime * (dir + cos_theta * n);
	vec3 r_parallel = -sqrt(fabs(1 - r_perp.squared()))*n;
	return r_perp + r_parallel;
}
inline double random_double() {
	static std::uniform_real_distribution<double>  distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}
inline double random_double(double min, double max) {
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}

inline static vec3 random() {
	return vec3(random_double(), random_double(), random_double());//random return a vector
}
inline static vec3 random(double min, double max) {
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}
inline vec3 reflect(const vec3& v,  const vec3& normal) {
	return v - 2 * dot(v, normal) * normal;
}
inline static vec3 random_vecinsphere() {
	auto p = random(-1, 1);
	while (p.length() >= 1) {
		p = random(-1, 1);
	}
	return p;
}
inline static vec3 random_in_hemisphere(const vec3& normal) {
	vec3 temp = random_vecinsphere();
	if (dot(temp, normal) > 0.0)return temp;
	return -temp;

}

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	out << v.x() << " " << v.y() << " " << v.z();
	return out;
}


inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}
//normalize the vector
using point3 = vec3;
using color = vec3;
#endif