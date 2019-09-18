#pragma once
#include "Vec3.h"

typedef struct Ray
{
	Vec3 origin;
	Vec3 direction;
} Ray;

/* Creates a Ray with the given origin and direction vectors */
Ray ray_create(Vec3 origin, Vec3 direction);
/* Returns the point at the given t */
Vec3 ray_point_at(const Ray* ray, float t);
/* Computes the point at the given t and stores it in dest */
Vec3* ray_get_point_at(const Ray* ray, float t, Vec3* dest);