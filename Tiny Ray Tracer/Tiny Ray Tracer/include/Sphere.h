#pragma once
#include "Hitable.h"

typedef struct
{
	HitFunction hit;
	Vec3 center;
	float radius;
} Sphere;

/* Creates a sphere with the given paramenters */
Sphere sphere_create(Vec3 center, float radius);
