#include <stdio.h>

#define IMAGE_FILENAME "output_image.ppm"


int main()
{
	FILE* image_file;

	fopen_s(&image_file, IMAGE_FILENAME, "wb+");

	const int nx = 200;
	const int ny = 100;

	fprintf(image_file, "P3\n%i %i\n255\n", nx, ny);

	for(int i = ny - 1;i >= 0;--i)
	{
		for(int j = 0;j < nx;++j)
		{
			float r = (float)j / (float)nx;
			float g = (float)i / (float)ny;
			float b = 0.2f;

			int ir = (int)(255.99f * r);
			int ig = (int)(255.99f * g);
			int ib = (int)(255.99f * b);

			fprintf(image_file, "%i %i %i\n", ir, ig, ib);
		}
	}

	fclose(image_file);

	return 0;
}