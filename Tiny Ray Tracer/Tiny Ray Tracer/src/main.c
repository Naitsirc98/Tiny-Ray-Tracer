#include <stdio.h>
#include "util.h"
#include "Image.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include <time.h>

#define IMAGE_FILENAME "output_image.png"

HitableList* create_world();

Vec3 get_color(const Ray* ray, Hitable* world);

int main()
{

	puts("Tiny Ray Tracer, by Cristian Daniel Herrera Herrera");
	puts("This is a C port of 'Ray Tracing in One Weekend' by Peter Shirley\n");

	srand(time(NULL));

	Image image;

	// Antialiasing samples
	unsigned int samples = 64;
	printf(">> Using %i samples per pixel\n", samples);
	
	// Gamma correction
	float gamma = 2.2f;
	printf(">> Using gamma correction of %.2f\n", gamma);

	img_init(&image, 1920, 1080, IMG_CHANNELS_RGB);
	printf(">> Output Image:\n{\n\twidth: %i\n\theight: %i\n\tchannels: %i\n}\n",
		image.width, image.height, image.channels);

	float aspect = (float)image.width / (float)image.height;

	Vec3 cam_pos = vec3_create(13, 2, 3);
	Vec3 cam_target = vec3_create(0, 0, 0);
	Vec3 cam_up = vec3_create(0, 1, 0);
	float dist_to_focus = 10;
	float aperture = 0.1f;
	float fov = 20.0f;

	Camera camera = cam_create(cam_pos, cam_target, cam_up, fov, aspect, aperture, dist_to_focus);
	
	HitableList* world = create_world();
	printf(">> World created with %i objects\n", world->size);

	puts(">> Rendering started");

	float total_pixels = image.width * image.height;
	float pixel_index = 0;

	time_t progress_timer = time(NULL);

	time_t start_time = time(NULL);

	for(int i = image.height - 1, pixel_offset = 0;i >= 0;--i)
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

				Vec3 tmp_color = get_color(&ray, world, 0);

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

			image.data[pixel_offset + 0] = ir;
			image.data[pixel_offset + 1] = ig;
			image.data[pixel_offset + 2] = ib;
			
			pixel_offset += image.channels;

			++pixel_index;

			time_t now = time(NULL);

			if(now - progress_timer >= 15)
			{
				printf("  >> [%is]: %.4f%% complete\n", (int)(now - start_time),
					100.0f * (pixel_index / total_pixels));
				progress_timer += 15;
			}

		}
	}

	time_t end_time = time(NULL);

	printf(">> Rendering finished in %i seconds\n", end_time - start_time);


	puts(">> Saving image to disk...");

	if(!img_write_file(&image, IMAGE_FILENAME, PNG))
	{
		printf(">> ERROR: could not write image to %s\n", IMAGE_FILENAME);
		printf(">> Image data:\n\twidth: %i\n\theight: %i\n\tchannels: %i\n\tdata address: %#08x\n",
			image.width, image.height, image.channels, (int)image.data);
		
		getchar();
		return -1;
	}
	puts(">> Image saved");

	puts(">> Freeing resources...");
	world->free(world);
	img_free(&image);

	puts(">> Ray Tracing completed!");

	getchar();

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

HitableList* create_world()
{
	int size = 488;
	HitableList* world = hlist_new(size);
	Hitable** list = world->list;

	list[0] = sphere_new(vec3_create(0, -1000, 0), 1000, mat_new_lamb(vec3_create(0.5f, 0.5f, 0.5f)));

	Vec3 v = vec3_create(4, 0.2f, 0);
	int i = 1;

	for(int a = -11;a < 11;++a)
	{
		for(int b = -11;b < 11;)
		{
			float choose_mat = randf();
			Vec3 center = vec3_create(a+0.9f*randf(), 0.2f, b+0.9*randf());
			
			if(vec3_length(&center, &v) > 0.9f)
			{
				if(choose_mat < 0.8f) // Diffuse
				{
					Vec3 albedo = vec3_create(randf()*randf(), randf()*randf(), randf()*randf());
					list[i++] = sphere_new(center, 0.2f, mat_new_lamb(albedo));
				}
				else if(choose_mat < 0.95f) // Metal
				{
					Vec3 albedo = vec3_create(0.5f*(1+randf()), 0.5f*(1+randf()), 0.5f*(1+randf()));
					list[i++] = sphere_new(center, 0.2f, mat_new_metal(albedo, 0.5f*randf()));
				}
				else // Glass
				{
					list[i++] = sphere_new(center, 0.2f, mat_new_diel(1.5f));
				}

				++b;
			}

		}
	}

	list[i++] = sphere_new(vec3_create(0, 1, 0), 1.0f, mat_new_diel(1.5f));
	list[i++] = sphere_new(vec3_create(-4, 1, 0), 1.0f, mat_new_lamb(vec3_create(0.4f, 0.2f, 0.1f)));
	list[i++] = sphere_new(vec3_create(4, 1, 0), 1.0f, mat_new_metal(vec3_create(0.7f, 0.6f, 0.5f), 0));

	return world;
}
