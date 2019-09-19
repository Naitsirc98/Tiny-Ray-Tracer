#pragma once
#include "Hitable.h"

typedef struct Material Material;

typedef struct
{
	HitFunction hit;
	FreeFunction free;
	Vec3 center;
	float radius;
	Material* material;
} Sphere;

/* Creates a sphere with the given paramenters */
Sphere sphere_create(Vec3 center, float radius, Material* material);
/* Creates a sphere on the heap. The returned pointer must be freed */
Sphere* sphere_new(Vec3 center, float radius, Material* material);
/* Frees the memory used by the given sphere */
void sphere_free(Sphere* sphere);
/* Computes a random point in a unit sphere */
Vec3 random_point_in_unit_sphere();