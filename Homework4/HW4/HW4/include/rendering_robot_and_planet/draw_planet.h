/*********************************
4104056004 李家駿 第四次作業 5/1
Drawing the earth arounding the sun.
*********************************/
#include "rendering_robot_and_planet/draw_includes.h"
void rendering_sun()
{
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(1.0, 20, 16);   /* draw sun */	

}
void rendering_earth()
{
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
		glRotatef((GLfloat)earth_year, 0.0, 1.0, 0.0);		
		glTranslatef(2.0, 0.0, 0.0);
		glRotatef((GLfloat)earth_day, 0.0, 1.0, 0.0);		
		glutSolidSphere(0.2, 10, 8);    /* draw smaller planet */
	glPopMatrix();
}
void rendering_orbit()
{
	const float DEG2RAD = 3.14159 / 180;
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glRotatef(90,1,0,0);

		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 360; i++)
		{
			float degInRad = i*DEG2RAD;
			glVertex2f(cos(degInRad)*2.0, sin(degInRad)*2.0);
		}

		glEnd();
	glPopMatrix();
}
