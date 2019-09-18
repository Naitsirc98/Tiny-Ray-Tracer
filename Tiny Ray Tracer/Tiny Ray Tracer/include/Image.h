#ifndef NAITSIRC98_IMAGE_T
#define NAITSIRC98_IMAGE_T

#define IMG_CHANNELS_RGB 3
#define IMG_CHANNELS_RGBA 4

#define BYTE unsigned char

typedef enum 
{
    PNG, BMP, TGA, JPEG, HDR
} ImageFormat;

typedef struct 
{
    unsigned int width;
    unsigned int height;
    unsigned int channels;
    BYTE* data;
} Image;

/* Initializes the image data buffer */
Image* img_init(Image* img, int w, int h, int channels);
/* Writes the entire image to a given file */
int img_write_file(Image* img, const char* filename, ImageFormat format);
/* Frees the data buffer of the given image */
void img_free(Image* img);

#endif