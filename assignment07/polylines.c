/*
Compile: make polylines_solution
Run: ./polylines_solution
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#undef assert

#undef M_PI
#define M_PI 3.141592654
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

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Color color;
	int points_count;
	Point *points;
} Polyline;

typedef struct {
	double step;
	double radius;
	double theta;
} CircleState;

CircleState make_circle_state(double step, double radius) {
	CircleState s = { step, radius, 0.0 };
	return s;
}

Point circle_next(/*inout*/ CircleState* s) {
	s->theta += s->step;
	Point p = { s->radius * cos(s->theta), s->radius * sin(s->theta) };
	return p;
}

Polyline *create_circle(double step1, double radius1, double step2, double radius2, Color color) {
	int n = 512;
	Point *points = xmalloc(n * sizeof(Point));
	CircleState state1 = make_circle_state(step1, radius1);
	CircleState state2 = make_circle_state(step2, radius2);
	int i = 0;
	for (; i < n && state1.theta < 2 * M_PI; i++) {
		Point p1 = circle_next(&state1);
		Point p2 = circle_next(&state2);
		Point p = { 400 + p1.x + p2.x, 400 - p1.y - p2.y };
		points[i] = p;
	}
	Polyline *p = xmalloc(sizeof(Polyline));
	p->color = color;
	p->points_count = i;
	p->points = points;
	return p;
}

void set_pixel(Image *image, int x, int y, Color color) {
	// todo: implement (a)
	// check for invalid coordinates
}

// adapted from http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C
void draw_line(Image *image, int x0, int y0, int x1, int y1, Color color) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = (dx > dy ? dx : -dy) / 2, e2;
	
	while (true) {
		set_pixel(image, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 > -dx){
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy){
			err += dx; 
			y0 += sy;
		}
	}
}

void draw_polylines(/*in*/ Polyline** polylines, int polylineCount, /*inout*/ Image *image);
void scale_polylines(/*inout*/ Polyline** polylines, int polylineCount, double sx, double sy);

void draw_polylines_test(void) {
	Polyline *pl1 = create_circle(M_PI / 180, 200, 10 * M_PI / 180,  60, make_color(0, 0, 255));
	Polyline *pl2 = create_circle(M_PI / 180, 100, 10 * M_PI / 180,  30, make_color(0, 255, 0));
	Polyline *pl3 = create_circle(M_PI / 180,  50, 10 * M_PI / 180,  15, make_color(255, 0, 0));
	Polyline *pl4 = create_circle(M_PI / 180, 400, 10 * M_PI / 180, 120, make_color(0, 255, 255));
	Polyline *polylines[] = { pl1, pl2, pl3, pl4 };
	
	Image image = make_image(800, 800);
	draw_polylines(polylines, 4, &image);
	stbi_write_png("polylines.png", image.width, image.height, 3, image.data, 3 * image.width);

	clear_image(&image);
	scale_polylines(polylines, 4, 0.8, 0.4);
	draw_polylines(polylines, 4, &image);
	stbi_write_png("polylines_scaled.png", image.width, image.height, 3, image.data, 3 * image.width);
}

/**
Draws the polylines in the given image.
@param[in] polylines pointer to an array of pointers to Polyline structs
@param[in] polylineCount number of pointers
@param[inout] image image to add polylines to
*/
void draw_polylines(/*in*/ Polyline** polylines, int polylineCount, /*inout*/ Image *image) 
{
	// @todo: implement
}

/**
Multiplies each polyline point with (sx, sy).
@param[inout] polylines pointer to an array of pointers to Polyline structs
@param[in] polylineCount number of pointers
@param[in] sx scale factor in x-direction
@param[in] sy scale factor in y-direction
*/
void scale_polylines(/*inout*/ Polyline** polylines, int polylineCount, double sx, double sy) 
{
	// @todo: implement
}

int main(void) {
	draw_polylines_test();
}
