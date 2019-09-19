#include "Material.h"
#include "Sphere.h"
#include "util.h"

inline Vec3 reflect(const Vec3* v, const Vec3* normal)
{
	Vec3 result;
	vec3_muls_c(normal, 2.0f * vec3_dot(v, normal), &result);
	return *vec3_sub_c(v, &result, &result);
}

inline int refract(const Vec3* v, const Vec3* n, float ni_over_nt, Vec3* refracted)
{
	Vec3 uv;
	vec3_normalize_c(v, &uv);

	float dt = vec3_dot(&uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);

	if(discriminant > 0)
	{
		Vec3 ndt;
		Vec3 nsqrt;
		vec3_muls_c(n, dt, &ndt);
		vec3_muls_c(n, sqrt(discriminant), &nsqrt);
		vec3_muls(vec3_sub_c(&uv, &ndt, refracted), ni_over_nt);
		vec3_sub(refracted, &nsqrt);

		return TRUE;
	}

	return FALSE;
}

inline float schlick(float cosine, float refractive_index)
{
	float r0 = (1 - refractive_index) / (1 + refractive_index);
	r0 *= r0;
	return r0 + (1 - r0) * powf(1 - cosine, 5);
}

int lamb_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray);
int metal_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray);
int diel_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray);

Lambertian mat_create_lamb(Vec3 albedo)
{
	return (Lambertian) {lamb_scatter, albedo};
}

Lambertian* mat_new_lamb(Vec3 albedo)
{
	Lambertian* lamb = ALLOC_NEW(Lambertian, 1);
	lamb->scatter = lamb_scatter;
	lamb->albedo = albedo;
	return lamb;
}

Metal mat_create_metal(Vec3 albedo, float fuzz)
{
	return (Metal) {metal_scatter, albedo, fuzz};
}

Metal* mat_new_metal(Vec3 albedo)
{
	Metal* metal = ALLOC_NEW(Metal, 1);
	metal->scatter = metal_scatter;
	metal->albedo = albedo;
	return metal;
}

Dielectric mat_create_diel(float refractive_index)
{
	return (Dielectric) {diel_scatter, refractive_index};
}

Dielectric* mat_new_diel(float refractive_index)
{
	Dielectric* diel = ALLOC_NEW(Dielectric, 1);
	diel->scatter = diel_scatter;
	diel->refractive_index = refractive_index;
	return diel;
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

int diel_scatter(const Ray* in_ray, const HitRecord* record, Vec3* attenuation, Ray* out_ray)
{
	Dielectric* diel = (Dielectric*)record->material;

	Vec3 outward_normal;
	Vec3 reflected = reflect(&in_ray->direction, &record->normal);
	float ni_over_nt;
	vec3_set(attenuation, 1.0f, 1.0f, 1.0f);
	Vec3 refracted;
	float reflect_prob;
	float cosine;

	if(vec3_dot(&in_ray->direction, &record->normal) > 0)
	{
		vec3_negate_c(&record->normal, &outward_normal);
		ni_over_nt = diel->refractive_index;
		cosine = diel->refractive_index * vec3_dot(&in_ray->direction, &record->normal);
		cosine /= vec3_length(&in_ray->direction);
	}
	else
	{
		outward_normal = record->normal;
		ni_over_nt = 1.0f / diel->refractive_index;
		cosine = -vec3_dot(&in_ray->direction, &record->normal);
		cosine /= vec3_length(&in_ray->direction);
	}

	if(refract(&in_ray->direction, &outward_normal, ni_over_nt, &refracted))
	{
		reflect_prob = schlick(cosine, diel->refractive_index);
	}
	else
	{
		reflect_prob = 1.0f;
	}

	if(randf() < reflect_prob)
	{
		*out_ray = ray_create(record->p, reflected);
	}
	else
	{
		*out_ray = ray_create(record->p, refracted);
	}

	return TRUE;
}
