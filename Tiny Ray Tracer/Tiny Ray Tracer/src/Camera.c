#include "Camera.h"
#include "util.h"

Camera cam_create(Vec3 position, Vec3 target, Vec3 up, float vfov, float aspect)
{
	Camera cam;

	float theta = vfov * (float)(M_PI / 180.0);
	float half_height = tanf(theta/2);
	float half_width = aspect * half_height;

	cam.origin = position;

	Vec3 u, v, w;
	vec3_normalize(vec3_sub_c(&position, &target, &w));
	vec3_normalize(vec3_cross_c(&up, &w, &u));
	vec3_cross_c(&w, &u, &v);

	vec3_muls(&u, half_width);
	vec3_muls(&v, half_height);
	vec3_sub(vec3_sub(vec3_sub_c(&cam.origin, &u, &cam.lower_left), &v), &w);

	vec3_muls_c(&u, 2, &cam.horizontal);
	vec3_muls_c(&v, 2, &cam.vertical);

	return cam;
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

