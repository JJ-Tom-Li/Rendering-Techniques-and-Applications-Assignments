/*********************************
4104056004 李家駿 第五次作業 5/13
This object will draw floor and walls.
*********************************/
#include "rendering_robot_and_planet\planet.cpp"
class Wall :public Moving_object {
	public:
		Bounding_box bounding_box;
		Wall() {
			_x = 0.0;
			_y = 0.0;
			_z = 0.0;
			_width = 1.0;
			_height = 1.0;
			_length = 1.0;
			_angle_x = 0;
			_angle_y = 0;
			_angle_z = 0;
		}
		Wall(float x, float y, float z) {
			_x = x;
			_y = y;
			_z = z;
		}
		Wall(float x,float y,float z,float width, float height, float length) {
			_x = x;
			_y = y;
			_z = z;
			_width = width;
			_height = height;
			_length = length;
			_angle_x = 0;
			_angle_y = 0;
			_angle_z = 0;
			bounding_box = Bounding_box(_x, _y, _z, width+0.1, _height+0.1, _length+0.1);
		}
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
		void Draw() {
			/*Set bounding box*/
			bounding_box.Draw();
			/*Set color material*/
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_SPECULAR);
			GLfloat low_shininess[] = { 5.0 };
			glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
			glColor3f(0.0,139.0/255,69.0/255);
			glPushMatrix();
				
				/*Move to the position*/
				glTranslatef(_x,_y,_z);

				glRotatef(_angle_x, 1, 0, 0);
				glRotatef(_angle_y, 0, 1, 0);
				glRotatef(_angle_z, 0, 0, 1);

				/*Draw the wall*/
				glScalef(_width, _height, _length);
				glutSolidCube(1.0);
			glPopMatrix();
			glDisable(GL_COLOR_MATERIAL);
		}
	private:
		float _width;
		float _height;
		float _length;
		float _angle_x;
		float _angle_y;
		float _angle_z;
};