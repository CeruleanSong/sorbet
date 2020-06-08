#include "draw.h"

#include <math.h>
#include <GL/gl.h>

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

void draw__pixel(double x, double y, double z)
{
	glBegin(GL_POINTS);

	glVertex3f(x ,y, z);

	glEnd();
} // draw_pixel()

void draw__line(double x1, double y1, double x2, double y2, double z)
{
	glBegin(GL_LINES);

	glVertex3f(x1, y1, z);
	glVertex3f(x2, y2, z);

	glEnd();
} // draw_line()

void draw__rect(double x1, double y1, double width, double height, double z)
{
	glBegin(GL_POLYGON);

	glVertex3f(x1, y1, z);
	glVertex3f(x1+width, y1, z);
	glVertex3f(x1+width, y1-height, z);
	glVertex3f(x1, y1-height, z);

	glEnd();
} // draw_rect()

void draw__circle(double x, double y, double radius, double z)
{
    float theta;

	glBegin(GL_POLYGON);
	for(int i=0; i<64; i++)
	{
        theta = i*M_PI/32;
        glVertex2f(radius*cos(theta)+x, radius*sin(theta)+y);
    }
	glEnd();

} // draw_circle()