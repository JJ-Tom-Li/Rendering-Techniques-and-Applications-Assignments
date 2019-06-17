#include "rendering_robot_and_planet\draw_includes.h"
class Moving_object {
public:
	//Coordinate of object
	float _x;
	float _y;
	float _z;
	GLMmodel * model;
	//char _model_name[80];
	char _name[20];

	Moving_object() {
		
	}
	/*Moving_object(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}*/
	//Moving_obejct(char *name);

	float x() {
		return _x;
	}
	float y(){
		return _y;
	}
	float z(){
		return _z;
	}
	void x(float x){
		_x = x;
	}
	void y(float y){
		_y = y;
	}
	void z(float z){
		_z = z;
	}
	char* name() {
		return _name;
	}

	void Move(float x_step, float y_step, float z_step);
	void Draw();
private:
	
};