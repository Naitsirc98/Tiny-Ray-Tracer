#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "Image.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include <time.h>

#define IMAGE_FILENAME "output_image.png"

inline float randf()
{
	return ((float)rand()/(float)(RAND_MAX));
}

Vec3 get_color(const Ray* ray, Hitable* world);

int main()
{
	srand(time(NULL));

	Image image;

	// Antialiasing samples
	unsigned int samples = 100;
	
	// Gamma correction
	float gamma = 2.2f;

	img_init(&image, 200, 100, IMG_CHANNELS_RGB);

	int offset = 0;

	Hitable* list[2];

	Sphere s1 = sphere_create(vec3_create(0, 0, -1), 0.5f);
	Sphere s2 = sphere_create(vec3_create(0, -100.5f, -1), 100.0f);

	list[0] = (Hitable*)&s1;
	list[1] = (Hitable*)&s2;

	HitableList world = hlist_create(list, 2);

	Camera camera = cam_create_def();

	for(int i = image.height - 1;i >= 0;--i)
	{
		for(int j = 0;j < image.width;++j)
		{
			Vec3 color = vec3_create_val(0.0f);

			for(int s = 0;s < samples;++s)
			{
				float u = (float)(j + randf()) / (float)image.width;
				float v = (float)(i + randf()) / (float)image.height;

				Ray ray = cam_get_ray(&camera, u, v);

				Vec3 p = ray_point_at(&ray, 2.0f);

				Vec3 tmp_color = get_color(&ray, &world);

				vec3_add(&color, &tmp_color);
			}
			// Get average color
			vec3_divs(&color, samples);
			// Gamma-correct the color
			color.r = powf(color.r, 1.0f / gamma);
			color.g = powf(color.g, 1.0f / gamma);
			color.b = powf(color.b, 1.0f / gamma);

			unsigned char ir = (unsigned char)(255.99f * color.r);
			unsigned char ig = (unsigned char)(255.99f * color.g);
			unsigned char ib = (unsigned char)(255.99f * color.b);

			image.data[offset + 0] = ir;
			image.data[offset + 1] = ig;
			image.data[offset + 2] = ib;
			
			offset += image.channels;
		}
	}

	if(!img_write_file(&image, IMAGE_FILENAME, PNG))
	{
		printf("ERROR: could not write image to %s\n", IMAGE_FILENAME);
		printf("Image data:\n\twidth: %i\n\theight: %i\n\tchannels: %i\n\tdata address: %#08x\n",
			image.width, image.height, image.channels, (int)image.data);
	}

	return 0;
}

Vec3 random_point_in_unit_sphere()
{
	Vec3 point;
	do
	{
		vec3_set(&point, randf(), randf(), randf());
		vec3_muls(&point, 2.0f);
		vec3_subs(&point, 1.0f);
	} while(vec3_sqrtlen(&point) >= 1.0f);

	return point;
}

Vec3 get_color(const Ray* ray, Hitable* world)
{
	HitRecord record;

	if(world->hit(world, ray, 0.001f, FLT_MAX, &record))
	{
		Vec3 target;
		Vec3 rand_point = random_point_in_unit_sphere();
		vec3_add(vec3_add_c(&record.p, &record.normal, &target), &rand_point);

		Ray new_ray = ray_create(record.p, *vec3_sub(&target, &record.p));
		Vec3 color = get_color(&new_ray, world);

		return *vec3_muls(&color, 0.5f);
	} 

	Vec3 unit_dir;
	vec3_normalize_c(&ray->direction, &unit_dir);

	float t = 0.5f * (unit_dir.y + 1.0f);

	Vec3 v1 = vec3_create_val(1.0f);
	Vec3 v2 = vec3_create(0.5f, 0.7f, 1.0f);

	vec3_muls(&v1, 1.0f - t);
	vec3_muls(&v2, t);

	return *vec3_add(&v1, &v2);
}