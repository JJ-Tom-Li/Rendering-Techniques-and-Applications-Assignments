/*********************************
4104056004 李家駿 第五次作業 5/13
This object will draw sun and earth.
*********************************/
//#include "rendering_robot_and_planet\Moving_object.h"
//#include "rendering_robot_and_planet\draw_includes.h"
#include "rendering_robot_and_planet\robot.cpp"
class Planet :public Moving_object {
public:
	Bounding_box bounding_box;
	Planet()
	{
		init();
	}
	Planet(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
		init();
	}
	void init()
	{
		earth_day = 0;
		earth_year = 0;
		sun_radius = 1.0;
		earth_radius = 0.2;
		bounding_box = Bounding_box(_x, _y, _z, 4, 2, 4);
	}
	void Move(float x, float y, float z)
	{

	}
	void Draw_sun()
	{
		/*Set bounding box*/
		bounding_box.Draw();
		/*Set color Material*/
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		GLfloat low_shininess[] = { 5.0 };
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glPushMatrix();
			//glRotatef(shoulder_angle, 0, 0, 1);				//Rotate with arm
			glTranslatef(this->_x, this->_y, this->_z);
			//glTranslatef((arm_length * 2 + 2), 0, 0);
			rendering_orbit();
			glColor3f(1.0, (float)97 / 255, 0.0);
			rendering_sun();
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
	}
	void Draw_earth()
	{
		/*Set the speed of evolution and rotation*/
		earth_day = (earth_day + 50) % 360;
		earth_year = (earth_year + 1) % 360;

		/*Draw earth*/
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		GLfloat low_shininess[] = { 5.0 };
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glPushMatrix();
		glTranslatef(this->_x, this->_y, this->_z);
		rendering_earth();
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
	}
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
		glRotatef(90, 1, 0, 0);

		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 360; i++)
		{
			float degInRad = i*DEG2RAD;
			glVertex2f(cos(degInRad)*2.0, sin(degInRad)*2.0);
		}

		glEnd();
		glPopMatrix();
	}
private:
	float sun_radius = 1.0;
	float earth_radius = 0.2;
	int earth_day = 0;
	int earth_year = 0;
};