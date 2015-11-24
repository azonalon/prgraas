/*
Compile: make image
Run: ./image
*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// http://hci.uni-hannover.de/files/prog1lib/index.html
#undef assert
#include "base.h"
#include "array.h"
#include "byte_array.h"

/*
A grayscale image is represented by its pixel data, its width, and its height.
Each pixel is represented as a single byte. Byte value 0 represents black. Byte
value 127 represents a medium gray. Byte value 0xff = 255 represents white. The
uppermost pixel row is stored left-to-right at array indices [0, width). The
second pixel row is stored at indices [width, 2 * width). And so on. The whole
image consists of width * height pixels, which is also the length of the
Byte-Array.
*/

struct Image {
	Array pixels; // Byte-Array
	int width; // in pixels
	int height; // in pixels
};
typedef struct Image Image;

Image make_image(Array pixels, int width, int height) {
	Image i = { pixels, width, height };
	return i;
}

Image make_image_with_new_array(int width, int height) {
    Array pixels = ba_create(width * height, 0);
	Image i = { pixels, width, height };
	return i;
}

/*
Load an image from the given file/path name. Ends the program if the image could not be loaded for any reason.
(Caution: This is a helper function. It contains material not covered in the lecture yet.)
*/
Image load_image(String file) {
	int width, height, channels;
	Byte *data = stbi_load(file, &width, &height, &channels, 1);
	// printf("w = %d, h = %d, c = %d, data = %p\n", width, height, channels, data);
	if (data == NULL) {
		printf("Could not load %s, sorry.\n", file);
		exit(1);
	}
	Array pixels = a_of_buffer(data, width * height, 1);
	stbi_image_free(data);
	return make_image(pixels, width, height);
}

/*
Save the image in png format. If it exists, the output file will be overwritten.
(Caution: This is a helper function. It contains material not covered in the lecture yet.)
*/
void save_image(String file, Image image) {
	stbi_write_png(file, image.width, image.height, 1, image.pixels->a, image.width);
}
// Helper Functions

Byte image_get_pixel(Image image, int irow, int icolumn) {
    assert(irow < image.height);
    assert(icolumn < image.width);
    return ba_get(image.pixels, image.width * irow + icolumn);
}

void image_set_pixel(Image image, int irow, int icolumn, Byte pixel) {
    assert(irow < image.height);
    assert(icolumn < image.width);
    ba_set(image.pixels, image.width * irow + icolumn, pixel);
}

void image_swap_pixel(Image image,
                      int irow1, int icol1,
                      int irow2, int icol2
                     ) {

    Byte pixel1 = image_get_pixel(image, irow1, icol1);
    Byte pixel2 = image_get_pixel(image, irow2, icol2);

    image_set_pixel(image, irow1, icol1, pixel2);
    image_set_pixel(image, irow2, icol2, pixel1);
}

/*
Mirror the image horizontally, i.e.,
:-) becomes (-:
*/
Image mirror_horizontally(Image image) {
	// todo: replace by your implementation
    Array mirrored_bytes = a_copy(image.pixels);
    Image mirrored = make_image(mirrored_bytes, image.width, image.height);

    for(int row = 0; row < mirrored.height; row++) {
        for(int column = 0; column < mirrored.width/2; column++) {
            image_swap_pixel(mirrored, row, column,
                             row, mirrored.width - column - 1);
        }
    }
	return mirrored;
}

/*
Scale the image in half, i.e.,
 \|||/
( o o )                     \|/
 (   )   becomes (roughly) (oo)
  ( )                       ()
  (_)
The function removes every second row and every second column.
*/
Image scale_half(Image image) {
	// todo: replace by your implementation
    Image scaled = make_image_with_new_array(image.width/2, image.height/2);
    for(int row = 0; row < scaled.height; row++) {
        for(int column = 0; column < scaled.width; column++) {
            Byte pixel = image_get_pixel(image, row*2, column*2);
            image_set_pixel(scaled, row, column, pixel);
        }
    }
	return scaled;
}

/*
Crop image, i.e.,
 \|||/
( o o )                                         \|||/
 (   )   becomes (depending on the paremeters) ( o o )
  ( )
  (_)
The function creates a subimage of the given width cw and height ch. The left
top corner of the subimage in the original image is (cx, cy).
*/
Image crop(Image image, int cx, int cy, int cw, int ch) {

    Image cropped = make_image_with_new_array(cw, ch);
    assert(cx + cw < image.width);
    assert(cy + ch < image.height);

    for(int row = 0; row < cropped.height; row++) {
        for(int column = 0; column < cropped.width; column++) {
            Byte pixel = image_get_pixel(image, cy + row, cx + column);
            image_set_pixel(cropped, row, column, pixel);
        }
    }
	return cropped;
}

/*
Insert an image into another image. The left top corner of the insertion position is (offset_x, offset_y).
 \|/                         \|/
(o  )   insert x at (3,1)   (o x)
 --                          --
*/
void insert(Image image, Image insert, int offset_x, int offset_y) {

    /* Array result_bytes = a_copy(image.pixels); */
    /* Image result = make_image(result_bytes, image.width, image.height); */

    assert(offset_x + insert.width < image.width);
    assert(offset_y + insert.height < image.height);

    for(int row = 0; row < insert.height; row++) {
        for(int column = 0; column < insert.width; column++) {
            Byte pixel = image_get_pixel(insert, row, column);
            image_set_pixel(image, row + offset_y, column + offset_x, pixel);
        }
    }
}

int main() {
	Image in = load_image("person.jpg");

	Image mirror = mirror_horizontally(in);
	save_image("out-mirror-horizontally.png", mirror);
	a_free(mirror.pixels);

	Image half = scale_half(in);
	save_image("out-half.png", half);

	Image cropped = crop(in, 448, 65, 180, 200);
	save_image("out-cropped.png", cropped);
	a_free(cropped.pixels);

	insert(in, half, 0, 0);
	save_image("out-insert.png", in);
	a_free(half.pixels);
	a_free(in.pixels);
}
