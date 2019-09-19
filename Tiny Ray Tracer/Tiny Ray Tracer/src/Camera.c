#include "Camera.h"
#include "util.h"

Vec3 random_point_in_unit_disk()
{
	Vec3 point;
	do
	{
		point = vec3_create(2 * randf(), 2 * randf(), 0.0f);
		--point.x;
		--point.y;
	} while(vec3_dot(&point, &point) >= 1.0f);
	return point;
}

Camera cam_create(Vec3 position, Vec3 target, Vec3 up, float vfov, float aspect, float aperture, float focus_dist)
{
	Camera cam;

	cam.lens_radius = aperture / 2.0f;

	float theta = vfov * (float)(M_PI / 180.0);
	float half_height = tanf(theta/2);
	float half_width = aspect * half_height;

	cam.origin = position;

	vec3_normalize(vec3_sub_c(&position, &target, &cam.w));
	vec3_normalize(vec3_cross_c(&up, &cam.w, &cam.u));
	vec3_cross_c(&cam.w, &cam.u, &cam.v);

	Vec3 w = cam.w;
	Vec3 u = cam.u;
	Vec3 v = cam.v;

	vec3_muls(&u, half_width * focus_dist);
	vec3_muls(&v, half_height * focus_dist);
	vec3_sub(vec3_sub(vec3_sub_c(&cam.origin, &u, &cam.lower_left), &v), vec3_muls(&w, focus_dist));

	vec3_muls_c(&u, 2, &cam.horizontal);
	vec3_muls_c(&v, 2, &cam.vertical);

	return cam;
}

Ray cam_get_ray(Camera* cam, float s, float t)
{
	Vec3 random_point = random_point_in_unit_disk();
	vec3_muls(&random_point, cam->lens_radius);

	Vec3 u = cam->u;
	vec3_muls(&u, random_point.x);
	Vec3 v = cam->v;
	vec3_muls(&v, random_point.y);
	
	Vec3 offset = *vec3_add(&u, &v);

	Vec3 ray_origin = cam->origin;
	vec3_add(&ray_origin, &offset);

	Vec3 ray_dir = cam->lower_left;
	Vec3 horizontal = cam->horizontal;
	vec3_muls(&horizontal, s);
	Vec3 vertical = cam->vertical;
	vec3_muls(&vertical, t);

	vec3_sub(vec3_sub(vec3_add(vec3_add(&ray_dir, &horizontal), &vertical) ,&cam->origin), &offset);

	return ray_create(ray_origin, ray_dir);
}

