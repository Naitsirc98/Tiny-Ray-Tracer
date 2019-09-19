#include <stdio.h>
#include "util.h"
#include "Image.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"

#define IMAGE_FILENAME "output_image.png"

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

	float aspect = (float)image.width / (float)image.height;

	int offset = 0;

	Lambertian lamb1 = mat_create_lamb(vec3_create(0.1f, 0.2f, 0.5f));
	Lambertian lamb2 = mat_create_lamb(vec3_create(0.8f, 0.8f, 0.0f));
	Metal metal1 = mat_create_metal(vec3_create(0.8f, 0.6f, 0.2f), 0.1f);
	Metal metal2 = mat_create_metal(vec3_create(0.8f, 0.8f, 0.8f), 0.3f);
	Dielectric diel1 = mat_create_diel(1.5f);

	Sphere s1 = sphere_create(vec3_create(0, 0, -1), 0.5f, &lamb1);
	Sphere s2 = sphere_create(vec3_create(0, -100.5f, -1), 100.0f, &lamb2);
	Sphere s3 = sphere_create(vec3_create(1, 0, -1), 0.5f, &metal1);
	Sphere s4 = sphere_create(vec3_create(-1, 0, -1), 0.5f, &diel1);
	Sphere s5 = sphere_create(vec3_create(-1, 0, -1), -0.45f, &diel1);

	Hitable* list[5];
	list[0] = (Hitable*)&s1;
	list[1] = (Hitable*)&s2;
	list[2] = (Hitable*)&s3;
	list[3] = (Hitable*)&s4;
	list[4] = (Hitable*)&s5;

	HitableList world = hlist_create(list, 5);

	Vec3 cam_pos = vec3_create(3, 3, 2);
	Vec3 cam_target = vec3_create(0, 0, -1);
	Vec3 cam_up = vec3_create(0, 1, 0);
	Vec3 pt = cam_pos;
	vec3_sub(&pt, &cam_target);
	float dist_to_focus = vec3_length(&pt);
	float aperture = 2.0f;

	float fov = 20.0f;

	Camera camera = cam_create(cam_pos, cam_target, cam_up, fov, aspect, aperture, dist_to_focus);

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

				Vec3 tmp_color = get_color(&ray, &world, 0);

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

Vec3 get_color(const Ray* ray, Hitable* world, int depth)
{
	HitRecord record;

	if(world->hit(world, ray, 0.001f, FLT_MAX, &record))
	{
		Ray scattered;
		Vec3 attenuation;
		if(depth < 50 && record.material->scatter(ray, &record, &attenuation, &scattered))
		{
			Vec3 color = get_color(&scattered, world, depth + 1);
			return *vec3_mul(&attenuation, &color);
		}
		return vec3_create_val(0.0f);
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