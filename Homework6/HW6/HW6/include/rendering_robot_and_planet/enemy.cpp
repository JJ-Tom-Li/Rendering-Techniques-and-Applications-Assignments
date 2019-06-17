#include "rendering_robot_and_planet\wall.cpp"
class Enemy :public Moving_object {
public:
	Bounding_box bounding_box;
	Enemy() {
		_x = 0.0;
		_y = 0.0;
		_z = 0.0;
		_width = 2.0;
		_height = 2.0;
		_length = 2.0;
		_angle_x = 0;
		_angle_y = 0;
		_angle_z = 0;
	}
	Enemy(float x, float y, float z) {
		_x = x;
		_y = y;
		_z = z;
		_angle_x = 0;
		_angle_y = -90;
		_angle_z = 0;
		_width = 6.0;
		_height = 12.0;
		_length = 12.0;
		bounding_box = Bounding_box(_x, _y, _z, _width, _height , _length);
	}
	/*Enemy(float x, float y, float z, float width, float height, float length) {
		_x = x;
		_y = y;
		_z = z;
		_width = width;
		_height = height;
		_length = length;
		_angle_x = 0;
		_angle_y = 0;
		_angle_z = 0;
		bounding_box = Bounding_box(_x, _y, _z, width + 0.1, _height + 0.1, _length + 0.1);
	}*/
	float width() {
		return _width;
	}
	float height() {
		return _height;
	}
	float length() {
		return _length;
	}
	void angle_x(float angle_x) {
		_angle_x = angle_x;
		bounding_box.Rotate(_angle_x, _angle_y, _angle_z);
	}
	void angle_y(float angle_y) {
		_angle_y = angle_y;
		bounding_box.Rotate(_angle_x, _angle_y, _angle_z);
	}
	void angle_z(float angle_z) {
		_angle_z = angle_z;
		bounding_box.Rotate(_angle_x, _angle_y, _angle_z);
	}
	void load_model(char *model_name) {
		model = glmReadOBJ(model_name);
		glmUnitize(model);
		glmFacetNormals(model);
		glmVertexNormals(model, 90);
	}
	void Draw() {
		/*Set bounding box*/
		bounding_box.Draw();
		glPushMatrix();
			/*Move to the (x,y,z)*/
			glTranslatef(this->_x, this->_y, this->_z);
			glRotatef(_angle_y, 0, 1, 0);	//Rotate 90 degrees with y-axis.
			glScalef(7,7,7);
			glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
		glPopMatrix();
	}
private:
	float _width;
	float _height;
	float _length;
	float _angle_x;
	float _angle_y;
	float _angle_z;
};