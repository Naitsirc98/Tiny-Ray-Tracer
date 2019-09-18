#include <stdio.h>
#include "Image.h"
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define IMAGE_FILENAME "output_image.png"

Vec3 get_color(const Ray* ray, Hitable* world);

int main()
{
	Image image;

	img_init(&image, 200, 100, IMG_CHANNELS_RGB);

	int offset = 0;

	Vec3 lower_left_corner = vec3_create(-2.0f, -1.0f, -1.0f);
	Vec3 horizontal = vec3_create(4.0f, 0.0f, 0.0f);
	Vec3 vertical = vec3_create(0.0f, 2.0f, 0.0f);
	Vec3 origin = vec3_create_val(0.0f);

	Hitable* list[2];

	Sphere s1 = sphere_create(vec3_create(0, 0, -1), 0.5f);
	Sphere s2 = sphere_create(vec3_create(0, -100.5f, -1), 100.0f);

	list[0] = (Hitable*)&s1;
	list[1] = (Hitable*)&s2;

	HitableList world = hlist_create(list, 2);

	for(int i = image.height - 1;i >= 0;--i)
	{
		for(int j = 0;j < image.width;++j)
		{
			float u = (float)j / (float)image.width;
			float v = (float)i / (float)image.height;

			Vec3 d1 = vec3_copy(&horizontal);
			vec3_muls(&d1, u);
			vec3_add(&d1, &lower_left_corner);
			Vec3 d2 = vec3_copy(&vertical);
			vec3_muls(&d2, v);
			vec3_add(&d1, &d2);

			Ray ray = ray_create(origin, d1);

			Vec3 p = ray_point_at(&ray, 2.0f);

			Vec3 color = get_color(&ray, &world);

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

Vec3 get_color(const Ray* ray, Hitable* world)
{
	HitRecord record;

	if(world->hit(world, ray, 0.0f, FLT_MAX, &record))
	{
		return *vec3_muls(vec3_adds(&record.normal, 1.0f), 0.5f);
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