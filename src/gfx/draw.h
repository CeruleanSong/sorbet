#ifndef GFX_DRAW_H
#define GFX_DRAW_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../types.h"

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

/**
 * draw a pixle.
 * @param x x coordinate of pixel.
 * @param y y coordinate of pixel.
 **/
void draw__pixel(double x, double y, double z);

/**
 * draw a line.
 * @param x1 start x of line.
 * @param y1 start y of line.
 * @param x2 end x of line.
 * @param y2 end y of line.
 **/
void draw__line(double x1, double y1, double x2, double y2, double z);

/**
 * draw a rectangle.
 * @param x1 x coordinate of rectangle.
 * @param y1 y coordinate of rectangle.
 * @param width width of rectangle.
 * @param height height of rectangle.
 **/
void draw__rect(double x1, double y1, double width, double height, double z);

/**
 * draw a circle.
 * @param x x coordinate of circle.
 * @param y y coordinate of circle.
 * @param radius radius of circle.
 **/
void draw__circle(double x, double y, double radius, double z);

#endif