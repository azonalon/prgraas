/*
Compile: make rectangles
Run: ./rectangles
*/

#include "base.h"

struct Rectangle {
	double width;
	double height;
};
typedef struct Rectangle Rectangle;

/**
A rectangle on the stack of the given width and height.
*/
Rectangle make_rectangle(double width, double height) {
	Rectangle r = { width, height };
	return r;
}

/**
A dynamically allocated rectangle of the given width and height.
*/
Rectangle *make_rectangle_dynamic(double width, double height) {
	Rectangle *r = xmalloc(sizeof(Rectangle));
	r->width = width;
	r->height = height;
	return r;
}

double total_area(/*in*/ Rectangle *rs, int n);
double total_area_pointers(/*in*/ Rectangle **rs, int n);

void total_area_test(void) {
	Rectangle rs1[] = { 
		make_rectangle(10, 5), 
		make_rectangle(5, 5), 
		make_rectangle(0.5, 200) 
	};
	check_within_d(total_area(rs1, 3), 175.0, EPSILON);

	Rectangle *rs2[] = { 
		make_rectangle_dynamic(10, 5), 
		make_rectangle_dynamic(5, 5), 
		make_rectangle_dynamic(0.5, 200) 
	};
	check_within_d(total_area_pointers(rs2, 3), 175.0, EPSILON);
	for (int i = 0; i < 3; i++) {
		free(rs2[i]);
	}
}

/**
Computes the area of an array of n rectangles (array of structs).
@param[in] rs pointer to an array of n rectangles.
@param[in] n the length of the array
@return the sum of the areas of the rectangles
*/
double total_area(/*in*/ Rectangle *rs, int n) {
	return 0.0; // @todo: implement
}

/**
Computes the area of an array of n pointers to rectangles (array of pointers to structs).
@param[in] rs pointer to an array of n pointers to rectangles.
@param[in] n the length of the array
@return the sum of the areas of the rectangles
*/
double total_area_pointers(/*in*/ Rectangle **rs, int n) {
	return 0.0; // @todo: implement
}

void scale_rectangles(/*inout*/ Rectangle *rs, int n, double factor);
void scale_rectangles_pointers(/*inout*/ Rectangle **rs, int n, double factor);

void scale_rectangles_test(void) {
	Rectangle rs1[] = { 
		make_rectangle(10, 5), 
		make_rectangle(5, 5), 
		make_rectangle(0.5, 200) 
	};
	scale_rectangles(rs1, 3, 2.0);
	check_within_d(total_area(rs1, 3), 4.0 * 175.0, EPSILON);

	Rectangle *rs2[] = { 
		make_rectangle_dynamic(10, 5), 
		make_rectangle_dynamic(5, 5), 
		make_rectangle_dynamic(0.5, 200) 
	};
	scale_rectangles_pointers(rs2, 3, 2.0);
	check_within_d(total_area_pointers(rs2, 3), 4.0 * 175.0, EPSILON);
	for (int i = 0; i < 3; i++) {
		free(rs2[i]);
	}
}
/**
Multiply the width and height of each rectangle by factor.
@param[inout] rs pointer to an array of n rectangles.
@param[in] n the length of the array
@param[in] factor scale factor
*/
void scale_rectangles(/*inout*/ Rectangle *rs, int n, double factor) {
	// @todo: implement
}

/**
Multiply the width and height of each rectangle by factor.
@param[inout] rs pointer to an array of n pointers to rectangles.
@param[in] n the length of the array
@param[in] factor scale factor
*/
void scale_rectangles_pointers(/*inout*/ Rectangle **rs, int n, double factor) {
	// @todo: implement
}

int main(void) {
	total_area_test();
	scale_rectangles_test();
	return 0;
}
