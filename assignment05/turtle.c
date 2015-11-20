/*
Compile: make turtle_solution
Run: ./turtle_solution

*** Turtle Command Reference ***
FORWARD <VALUE>                // turtle walks <value> pixel forward
RIGHT <DEGREE>                 // turtle turns right by <degree> degrees
BACKWARD <VALUE>
LEFT <DEGREE>
CLEARSCREEN                    // erase everything and go back to start
PENUP                          // turtle stops drawing when it moves
PENDOWN                        // turtle starts drawing when it moves
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#undef assert

#include "base.h"
#include "string.h"

#define WIDTH  200
#define HEIGHT  200
#define M_PI 3.14159265358979323846
unsigned char image[WIDTH * HEIGHT];

enum PenState { UP, DOWN };
typedef enum PenState PenState;

int turtle_x = 0;
int turtle_y = 0;
int turtle_dir = 0;
int pen_state = DOWN;

void set_pixel(int x, int y, int color) {
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		image[y * WIDTH + x] = color;
	}
}

// adapted from http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C
void draw_line(int x0, int y0, int x1, int y1) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	while (true) {
		set_pixel(x0, y0, 0);
		if(x0 == x1 && y0 == y1) break;
		e2 = err;
		if(e2 > -dx){
			err -= dy;
			x0 += sx;
		}
		if(e2 < dy){
			err += dx;
			y0 += sy;
		}
	}
}

void clear(void) {
	memset(image, 255, WIDTH * HEIGHT);
	turtle_x = 0;
	turtle_y = 0;
	turtle_dir = 0;
	pen_state = DOWN;
}

void move_turtle(int movement) {
	int dx = (int)(movement * cos(turtle_dir * M_PI / 180.0));
	int dy = (int)(movement * sin(turtle_dir * M_PI / 180.0));

	if (pen_state == DOWN) {
		draw_line(turtle_x, turtle_y, turtle_x + dx, turtle_y + dy);
	}

	turtle_x += dx;
	turtle_y += dy;
}

void parse_command(String command) {
	if (s_equals(command, "CLEARSCREEN")) {
		clear();
	} else if(s_equals(command, "PENUP")) {
		pen_state = UP;
	} else if(s_equals(command, "PENDOWN")) {
		pen_state = DOWN;
	} else if(s_equals(command, "FORWARD")) {
		int movement = i_input();
		move_turtle(movement);
	} else if(s_equals(command, "BACKWARD")) {
		int movement = -i_input();
		move_turtle(movement);
	} else if(s_equals(command, "LEFT")) {
		int angle = i_input();
		if(turtle_dir < 0) {
            turtle_dir += 360 - angle;
        } else {
            turtle_dir -= angle;
        }
	} else if(s_equals(command, "RIGHT")) {
		int angle = i_input();
        if(turtle_dir > 0) {
            turtle_dir -= 360 - angle;
        } else {
            turtle_dir += angle;
        }
	} else {
		printf("Unknown command: %s\n", command);
	}
}

int main(void) {
	clear();

	String command = s_input(100);
	while (!s_equals(command, "")) {
		parse_command(command);
		command = s_input(100);
	}

	stbi_write_png("result.png", WIDTH, HEIGHT, 1, image, WIDTH);
}
