#pragma once
#include "Hitable.h"

typedef struct Material Material;

typedef struct
{
	HitFunction hit;
	Vec3 center;
	float radius;
	Material* material;
} Sphere;

/* Creates a sphere with the given paramenters */
Sphere sphere_create(Vec3 center, float radius, Material* material);
/* Computes a random point in a unit sphere */
Vec3 random_point_in_unit_sphere();