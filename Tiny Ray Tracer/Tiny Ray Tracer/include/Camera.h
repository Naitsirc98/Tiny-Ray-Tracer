#pragma once
#include "Ray.h"

typedef struct Camera
{
	Vec3 origin;
	Vec3 lower_left;
	Vec3 horizontal;
	Vec3 vertical;
} Camera;

/* Creates a camera with the given parameters */
Camera cam_create(Vec3 origin, Vec3 lower_left, Vec3 horizontal, Vec3 vertical);
/* Creates a camera with default values */
Camera cam_create_def();
/* Get a ray for a given u and v */
Ray cam_get_ray(Camera* cam, float u, float v);