#include <memory.h>
#include "Image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image* img_init(Image* img, int w, int h, int channels)
{
    img->width = w;
    img->height = h;
    img->channels = channels;
    img->data = (BYTE*) malloc(w * h * channels * sizeof(BYTE));
    return img;
}

int img_write_file(Image* img, const char* filename, ImageFormat format)
{

    switch(format)
    {
        case PNG:
            return stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * 3 * sizeof(BYTE));
        case BMP:
			return stbi_write_bmp(filename, img->width, img->height, img->channels, img->data);
        case TGA:
			return stbi_write_tga(filename, img->width, img->height, img->channels, img->data);
        case JPEG:
			return stbi_write_jpg(filename, img->width, img->height, img->channels, img->data, 100);
        case HDR:
			return stbi_write_hdr(filename, img->width, img->height, img->channels, (float*)img->data);
        default:
            assert(0 && "[ERROR]: Unknown image format");
    }

	return -1;
}

void img_free(Image* img)
{
    free(img->data);
}