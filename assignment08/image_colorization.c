/*
Compile: make image_colorization
Run: ./image_colorization
*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#undef assert

#include "base.h" // http://hci.uni-hannover.de/files/prog1lib/base_8h.html

typedef struct {
    int red;    // 0..255
    int green;  // 0..255
    int blue;   // 0..255
} Color;

Color make_color(int red, int green, int blue) {
    Color c = { red, green, blue };
    return c;
}

typedef struct {
    int width; // in pixels
    int height; // in pixels
    int bytes_per_pixel; // grayscale: 1 byte per pixel, 3 bytes per pixel (r, g, b)
    Byte *data; // dynamically allocated image data
} Image;

void clear_image(Image *image) {
    memset(image->data, 255, image->bytes_per_pixel * image->width * image->height);
}

/**
Creates a white image of the given pixel depth. The header and data of the image are both dynamically allocated.
@param[in] width width in pixels
@param[in] height height in pixels
@param[in] bytes_per_pixel color depth (1 for grayscale, 3 for color)
@return the created white image
*/
Image *make_image(int width, int height, int bytes_per_pixel) {
    assert(bytes_per_pixel == 1 || bytes_per_pixel == 3);
    Image* result = xmalloc(sizeof(Image));
    result->data = xmalloc(bytes_per_pixel * width * height);
    result->height = height;
    result->width = width;
    result->bytes_per_pixel = bytes_per_pixel;
    return result;
}

/**
Free the image.
@param[inout] image the image to free
*/
void free_image(Image *image) {
    free(image->data);
    free(image);
}

/**
Load an image from the given file/path name. Stop the program if the image could not be loaded for any reason.
@param[in] file file name of image (png and jpg possible)
@param[in] bytes_per_pixel color depth (1 for grayscale, 3 for color)
@return the loaded image
*/
Image *load_image(String file, int bytes_per_pixel) {
    int width, height, channels;
    Byte *data = stbi_load(file, &width, &height, &channels, bytes_per_pixel);
    // printf("w = %d, h = %d, c = %d, data = %p\n", width, height, channels, data);
    if (data == NULL) {
        printf("Could not load %s, sorry.\n", file);
        exit(1);
    }
    Image *image = make_image(width, height, bytes_per_pixel);
    if (image != NULL && image->data != NULL) {
        memcpy(image->data, data, bytes_per_pixel * width * height);
    }
    stbi_image_free(data);
    return image;
}

/**
Save the image in png format. If it exists, the output file will be overwritten.
@param[in] file file name of image (png)
@param[in] image the image to save
*/
void save_image(String file, Image *image) {
    if (image == NULL || image->data == NULL) return;
    stbi_write_png(file, image->width, image->height,
        image->bytes_per_pixel,
        image->data,
        image->bytes_per_pixel * image->width);
}

/**
Create a color map that only uses the red color channel.
@return a (dynamically allocated) array of 256 Colors
*/
Color *make_map_red(void) {
    Color* result = xmalloc(256*sizeof(Color));
    for(int i = 0; i < 256; i++) {
        result[i] = make_color(i, 0, 0);
    }
    return result;
}

/**
Create a color map by scanning the given image horizontally. The image must be 256 pixels wide and must have a color depth of 3 bytes per pixel (red, green, blue).
@param[in] file name of a colormap image of 256 pixels width
@return a (dynamically allocated) array of 256 Colors
*/
Color *make_map(String file) {
    Image *map = load_image(file, 3);
    assert(map->width >= 256);

    int bpp = map->bytes_per_pixel;
    int byte_width = bpp * map->width;
    Color* result = xmalloc(256 * sizeof(Color));
    for(int i = 0; i < 256; i++) {
        int first_byte = i * byte_width / 256;
        first_byte = first_byte - first_byte % bpp;
        result[i] = make_color(
                               map->data[first_byte + 0],
                               map->data[first_byte + 1],
                               map->data[first_byte + 2]
                               );
    }

    return result;
}

/**
Colorize the image with the colormap.
@param[in] in grayscale input image
@param[in] map colormap, an array of 256 Colors
@return the colorized output image
*/
Image *colorize(Image *in, Color *map) {
    assert(in->bytes_per_pixel == 1);
    Image* result = make_image(in->width, in->height, 3);
    for(int i = 0; i < in->height * in->width; i++) {
        assert(in->data[i] < 256);
        Color color = map[in->data[i]];
        result->data[3*i + 0] = color.red;
        result->data[3*i + 1] = color.green;
        result->data[3*i + 2] = color.blue;
    }
    return result;
}

void image_colorization_test(void) {
    Image *in = load_image("pebbles.png", 1);

    Color *map1 = make_map_red();
    Image *out1 = colorize(in, map1);
    save_image("out-map1.png", out1);
    free_image(out1);
    free(map1);

    Color *map2 = make_map("terrain.png");
    Image *out2 = colorize(in, map2);
    save_image("out-map2.png", out2);
    free_image(out2);
    free(map2);

    Color *map3 = make_map("rainbow.png");
    Image *out3 = colorize(in, map3);
    save_image("out-map3.png", out3);
    free_image(out3);
    free(map3);

    Color *map4 = make_map("infrared.png");
    Image *out4 = colorize(in, map4);
    save_image("out-map4.png", out4);
    free_image(out4);
    free(map4);

    free_image(in);
}



int main(void) {
    base_init();
    base_set_memory_check(true);
    image_colorization_test();
    return 0;
}
