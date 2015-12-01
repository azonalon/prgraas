/*
Compile: make quicksort_visualization
Run: ./quicksort_visualization
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#undef assert

#include "base.h"

typedef struct {
	int red;	// 0..255
	int green;	// 0..255
	int blue;	// 0..255
} Color;

Color make_color(int r, int g, int b) {
	Color c = { r, g, b };
	return c;
}

typedef struct {
	int width; // in pixels
	int height; // in pixels
	Byte *data; // 3 bytes per pixel: r, g, b
} Image;

void clear_image(Image *image) {
	memset(image->data, 255, 3 * image->width * image->height); // white
}

Image make_image(int width, int height) {
	Byte *data = xmalloc(3 * width * height);
	Image i = { width, height, data };
	clear_image(&i);
	return i;
}

/**
Writes the image into file result-<index>.png in the current directory.
*/
void write_image(Image *image, int index) {
	char filename[64];
	sprintf(filename, "result-%02d.png", index);
	stbi_write_png(filename, image->width, image->height, 3, image->data, 3 * image->width);
}

void set_pixel(Image *image, int x, int y, Color color) {
    assert(x < image->width);
    assert(y < image->height);

    int h = image->height - y;
    Byte* first = image->data + 3 * image->width * h + 3 * x;
    *(first) = color.red;
    *(first + 1) = color.green;
    *(first + 2) = color.blue;

}

void swap(int v[], int i, int j) {
	int a = v[i];
	v[i] = v[j];
	v[j] = a;
}
Image quicksort_im;
int quicksort_image_index = 1;
const Color GREEN = {0, 255, 0};
const Color RED = {255, 0, 0};
const Color BLACK = {0, 0, 0};
const Color WHITE = {255, 255, 255};

void plot_array_64_black(Image* im, const int* data)
{
    clear_image(im);
    for(int i = 0; i < 64; i++) {
        set_pixel(im, i, data[i], BLACK);
    }
}


void quicksort(int v[], int left, int right) {

    plot_array_64_black(&quicksort_im, v);
	if (left >= right) return; // 0 or 1 elements, recursion end
	swap(v, left, (left + right) / 2); // move pivot element to left
	int j = left;
	for (int i = left + 1; i <= right; i++) {
        if (v[i] < v[left]) {
			swap(v, ++j, i);
            set_pixel(&quicksort_im, i, v[i], RED);
            set_pixel(&quicksort_im, j, v[j], RED);
		}
		// assert: v[i] < v[left] for i = left+1..j
	}
	swap(v, left, j); // move back pivot element
    // mark the pivot
    set_pixel(&quicksort_im, j, v[j], GREEN);

	// todo: implement a visualization of the current state (c)
    write_image(&quicksort_im, quicksort_image_index++);

	quicksort(v, left, j-1); // assert: v[i] < v[j] for i = left..j-1
	quicksort(v, j+1, right); // assert: v[i] >= v[j] for i = j+1..right
}


void quicksort_test(void) {
    /* Image im = make_image(64, 64); */
	int test_array[64];
    for(int i = 0; i < 64; i++) {
        test_array[i] = i_rnd(64);
    }
    plot_array_64_black(&quicksort_im, test_array);
    write_image(&quicksort_im, 0);

    quicksort(test_array, 0, 64);
}

int main(void) {
    quicksort_im = make_image(64, 64);
    quicksort_image_index = 1;
	quicksort_test();
}
