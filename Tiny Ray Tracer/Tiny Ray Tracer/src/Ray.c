#include "Ray.h"

Ray ray_create(Vec3 origin, Vec3 direction)
{
	return (Ray) {origin, direction};
}

Vec3 ray_point_at(const Ray* ray, float t)
{
	Vec3 dest;
	return *ray_get_point_at(ray, t, &dest);
}

Vec3* ray_get_point_at(const Ray* ray, float t, Vec3* dest)
{
	return vec3_add_c(&ray->origin, vec3_muls_c(&ray->direction, t, dest), dest);
}
