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
	// todo: implement (a)
}

void swap(int v[], int i, int j) {
	int a = v[i];
	v[i] = v[j];
	v[j] = a;
}

void quicksort(int v[], int left, int right) {
	if (left >= right) return; // 0 or 1 elements, recursion end
	swap(v, left, (left + right) / 2); // move pivot element to left
	int j = left;
	for (int i = left + 1; i <= right; i++) {
		if (v[i] < v[left]) {
			swap(v, ++j, i);
		}
		// assert: v[i] < v[left] for i = left+1..j
	}
	swap(v, left, j); // move back pivot element

	// todo: implement a visualization of the current state (c)

	quicksort(v, left, j-1); // assert: v[i] < v[j] for i = left..j-1
	quicksort(v, j+1, right); // assert: v[i] >= v[j] for i = j+1..right
}

void quicksort_test(void) {

	// todo: create random array and create image that shows the initial state (b)

	// todo: call quicksort(...);
	
}

int main(void) {
	quicksort_test();
}
