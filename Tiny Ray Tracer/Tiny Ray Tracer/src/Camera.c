#include "Camera.h"

Camera cam_create(Vec3 origin, Vec3 lower_left, Vec3 horizontal, Vec3 vertical)
{
	return (Camera) {origin, lower_left, horizontal, vertical};
}

Camera cam_create_def()
{
	return cam_create(vec3_create_val(0.0f), vec3_create(-2, -1, -1),
		vec3_create(4, 0, 0), vec3_create(0, 2, 0));
}

Ray cam_get_ray(Camera* cam, float u, float v)
{
	Vec3 d1 = cam->horizontal;
	vec3_muls(&d1, u);
	vec3_add(&d1, &cam->lower_left);
	Vec3 d2 = cam->vertical;
	vec3_muls(&d2, v);
	vec3_add(&d1, &d2);
	vec3_sub(&d1, &cam->origin);

	return ray_create(cam->origin, d1);
}

