#pragma once
#include "Ray.h"

typedef struct Camera
{
	Vec3 origin;
	Vec3 lower_left;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	float lens_radius;
} Camera;

/* Creates a camera with the given parameters */
Camera cam_create(Vec3 position, Vec3 target, Vec3 up, float vfov, float aspect, float aperture, float focus_dist);
/* Get a ray for a given u and v */
Ray cam_get_ray(Camera* cam, float u, float v);
