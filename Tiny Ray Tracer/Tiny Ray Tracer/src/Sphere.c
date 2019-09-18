#include "Sphere.h"
#include "util.h"
#include <math.h>

int sphere_hit(void* sphere_ptr, const Ray* ray, float tmin, float tmax, HitRecord* record);

Sphere sphere_create(Vec3 center, float radius, Material* material)
{
	return (Sphere) { sphere_hit, center, radius, material};
}

Vec3 random_point_in_unit_sphere()
{
	Vec3 point;
	do
	{
		vec3_set(&point, randf(), randf(), randf());
		vec3_muls(&point, 2.0f);
		vec3_subs(&point, 1.0f);
	} while(vec3_sqrtlen(&point) >= 1.0f);

	return point;
}
inline void set_record(float t, HitRecord* record, const Ray* ray, const Sphere* sphere)
{
	record->t = t;
	record->material = sphere->material;
	ray_get_point_at(ray, t, &record->p);
	vec3_divs(vec3_sub_c(&record->p, &sphere->center, &record->normal), sphere->radius);
}

int sphere_hit(void* sphere_ptr, const Ray* ray, float tmin, float tmax, HitRecord* record)
{
	Sphere* sphere = (Sphere*)sphere_ptr;

	Vec3 oc;
	vec3_sub_c(&ray->origin, &sphere->center, &oc);

	float a = vec3_dot(&ray->direction, &ray->direction);
	float b = vec3_dot(&oc, &ray->direction);
	float c = vec3_dot(&oc, &oc) - sphere->radius * sphere->radius;

	float discriminant = b * b - a * c;

	if(discriminant > 0)
	{
		float t = (-b - sqrt(discriminant)) / a;
		if(t < tmax && t > tmin)
		{
			set_record(t, record, ray, sphere);
			return TRUE;
		}
		
		t = (-b + sqrt(discriminant)) / a;
		if(t < tmax && t > tmin)
		{
			set_record(t, record, ray, sphere);
			return TRUE;
		}
	}

	return FALSE;
}