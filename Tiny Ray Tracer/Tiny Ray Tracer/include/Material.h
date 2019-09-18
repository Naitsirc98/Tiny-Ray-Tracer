#pragma once
#include "Ray.h"
#include "Hitable.h"

typedef int (*ScatterFunction)(const Ray*, const HitRecord*, Vec3*, Ray*);

typedef struct Material
{
	ScatterFunction scatter;
	Vec3 albedo;
} Material;

typedef struct Lambertian
{
	ScatterFunction scatter;
	Vec3 albedo;
} Lambertian;

/* Creates a Lambertian Material with the given albedo color */
Lambertian mat_create_lamb(Vec3 albedo);

typedef struct Metal
{
	ScatterFunction scatter;
	Vec3 albedo;
	float fuzz;
} Metal;

/* Creates a Metal Material with the given albedo color and fuzz */
Metal mat_create_metal(Vec3 albedo, float fuzz);