#include "Material.h"
#include "Sphere.h"

inline Vec3 reflect(const Vec3* v, const Vec3* normal)
{
	Vec3 result;
	vec3_muls_c(normal, 2.0f * vec3_dot(v, normal), &result);
	return *vec3_sub_c(v, &result, &result);
}

int lamb_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray);
int metal_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray);

Lambertian mat_create_lamb(Vec3 albedo)
{
	return (Lambertian) {lamb_scatter, albedo};
}

Metal mat_create_metal(Vec3 albedo, float fuzz)
{
	return (Metal) {metal_scatter, albedo, fuzz};
}

int lamb_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray)
{
	Lambertian* lamb = (Lambertian*)record->material;

	Vec3 random_point = random_point_in_unit_sphere();
	Vec3 target = record->p;
	vec3_add(vec3_add(&target, &record->normal), &random_point);

	*out_ray = ray_create(record->p, *vec3_sub(&target, &record->p));

	*attenuation = lamb->albedo;

	return TRUE;
}

int metal_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray)
{
	Metal* metal = (Metal*)record->material;

	Vec3 reflected;
	reflected = reflect(vec3_normalize_c(&in_ray->direction, &reflected), &record->normal);

	Vec3 random_point = random_point_in_unit_sphere();
	vec3_muls(&random_point, metal->fuzz);

	*out_ray = ray_create(record->p, *vec3_add(&reflected, &random_point));

	*attenuation = metal->albedo;

	return vec3_dot(&out_ray->direction, &record->normal) > 0.0f;
}
