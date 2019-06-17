/*********************************
4104056004 李家駿 第五次作業 5/13
This object will creating a bounding box around the object.
*********************************/
#include "rendering_robot_and_planet\moving_object.h"
#include "rendering_robot_and_planet\draw_includes.h"
class Bounding_box :public Moving_object {
public:
	Bounding_box() {
		_x = 0.0;
		_y = 0.0;
		_z = 0.0;
		_width=1.0;
		_height= 1.0;
		_length= 1.0;
		_angle_x=0;
		_angle_y=0;
		_angle_z=0;
	}
	Bounding_box(float x, float y, float z, float width, float height, float length) {
		_x = x;
		_y = y;
		_z = z;
		_width = width;
		_height = height;
		_length = length;
		_angle_x = 0;
		_angle_y = 0;
		_angle_z = 0;
	}
	float width() { return _width; }
	float height() { return _height; }
	float length() { return _length; }
	void Move(float x_step,float y_step,float z_step) {
		/*Bounding box will move with the object.*/
		_x += x_step;
		_y += y_step;
		_z += z_step;
	}
	void Rotate(float angle_x,float angle_y,float angle_z) {
		/*Bounding box will rotate with the object.*/
		_angle_x = angle_x;
		_angle_y = angle_y;
		_angle_z = angle_z;
	}
	void Draw() {
		/*Recreating the bounding box.*/
		/*Draw a virtual bounding box*/
		/*glPushMatrix();
			glTranslatef(_x, _y, _z);
			glRotatef(_angle_x, 1, 0, 0);
			glRotatef(_angle_y, 0, 1, 0);
			glRotatef(_angle_z, 0, 0, 1);
			glScalef(_width,_height,_length);
			glutWireCube(1.0);
		glPopMatrix();*/
	}
private:
	float _width;
	float _height;
	float _length;
	float _angle_x;
	float _angle_y;
	float _angle_z;
};