#include <stdio.h>
#include "Image.h"

#define IMAGE_FILENAME "output_image.png"

int main()
{

	Image image;

	img_init(&image, 200, 100, IMG_CHANNELS_RGB);

	int offset = 0;

	for(int i = image.height - 1;i >= 0;--i)
	{
		for(int j = 0;j < image.width;++j)
		{
			float r = (float)j / (float)image.width;
			float g = (float)i / (float)image.height;
			float b = 0.2f;

			BYTE ir = (BYTE)(255.99f * r);
			BYTE ig = (BYTE)(255.99f * g);
			BYTE ib = (BYTE)(255.99f * b);

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

	system("pause");

	return 0;
}