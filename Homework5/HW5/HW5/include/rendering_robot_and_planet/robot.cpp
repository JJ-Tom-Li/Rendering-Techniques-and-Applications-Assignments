/*********************************
4104056004 李家駿 第五次作業 5/13
This object will draw a robotic arm.
*********************************/
#include "rendering_robot_and_planet\bounding_box.cpp"
class Robot:public Moving_object{
public:
	Robot::Robot(){
		init();
	}

	Robot(float x, float y, float z){
		_x = x;
		_y = y;
		_z = z;
		init();
	}
	void init() {
		shoulder_angle = -30;
		elbow_angle = 40;
		elbow_shift = 5;
		finger_angle = 0;
		finger_shift = 3;
		thumb_angle = 0;
		thumb_shift = 3;
		finger_and_thumb_move = 0;
		bounding_box = Bounding_box(_x+arm_length, _y , _z, arm_length*2+2, arm_length, arm_width);
	}
	/*
	void other_boxes(Bounding_box *other_boxes[],int number) {
		other_boxes_number = number;
		for (int i = 0; i < number; i++) {
			_other_boxes[i] = other_boxes[i];
		}
	}*/
	float get_arm_length() { return this->arm_length; }
	void Rotate_shoulder(){
		/*Rotate shoulder*/
		shoulder_angle = (shoulder_angle + 5) % 360;
		glutPostRedisplay();
	}
	void Rotate_elbow(){
		elbow_angle = (elbow_angle + elbow_shift) % 360;
		if (elbow_angle >= 180)		//Touch the arm.Turn back.
			elbow_shift = -5;
		else if (elbow_angle <= 0)	//Totally extended.Turn back.
			elbow_shift = 5;
		glutPostRedisplay();
	}
	void Rotate_finger(){
		/*Rotate finger*/
		finger_and_thumb_move = 1;	//Rotate thumb and finger at the same time.
		finger_angle = (finger_angle - finger_shift) % 360;

		/*Avoid fingers touch each other.*/
		if (finger_angle <= -60 || (finger_angle < 0 && thumb_angle <= -6))		//Totally extended.Turn back.
			finger_shift = -3;
		else if (finger_angle >= 60)	//Touch the second setion.Turn back.
			finger_shift = 3;

		/*Redraw*/
		glutPostRedisplay();
	}
	void Rotate_thumb(){
		/*Rotate thumb*/
		finger_and_thumb_move = 0;		//Only move thumb.
		thumb_angle = (thumb_angle + thumb_shift) % 360;

		/*Avoid fingers touch each other.*/
		if (thumb_angle >= 60)		//Touch the second setion.Turn back.
			thumb_shift = -3;
		else if (thumb_angle <= -60 || (thumb_angle<0 && finger_angle <= -6))	//Totally extended.Turn back.
			thumb_shift = 3;

		/*Redraw*/
		glutPostRedisplay();
	}
	bool collision(float wall_x, float wall_y, float wall_z, float wall_width, float wall_height, float wall_length) {
		/*AABB collision*/
		float minX1 = _x + arm_length - (arm_length * 2 + 2) / 2,
			maxX1 = _x + arm_length + (arm_length * 2 + 2) / 2,
			minY1 = _y - arm_length / 2,
			maxY1 = _y + arm_length / 2,
			minZ1 = _z - arm_width / 2,
			maxZ1 = _z + arm_width / 2;

		float minX2 = wall_x - wall_width / 2,
			maxX2 = wall_x + wall_width / 2,
			minY2 = wall_y - wall_height / 2,
			maxY2 = wall_y + wall_height / 2,
			minZ2 = wall_z - wall_length / 2,
			maxZ2 = wall_z + wall_length / 2;

		if (maxX1 > minX2 && maxX2 > minX1 &&
			maxY1 > minY2 && maxY2 > minY1 &&
			maxZ1 > minZ2 && maxZ2 > minZ1) {
			return true;
		}
		else
			return false;
	}
	void Move(float x_step, float y_step, float z_step) {
		/*Collision detection*/
		bool collision = false;
		/*Move if no collision*/
		if (!collision) {
			_x += x_step;
			_y += y_step;
			_z += z_step;
			bounding_box.Move(x_step, y_step, z_step);
		}
	}
	void Draw()
	{
		/*Set bounding box*/
		bounding_box.Draw();
		/*Set color material*/
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_SPECULAR);
		GLfloat low_shininess[] = { 128.0 };
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glPushMatrix();
			/*Move to the (x,y,z)*/
			glTranslatef(this->_x, this->_y, this->_z);
			glTranslatef(arm_length / 2, 0, 0);
			this->rendering_arm_and_elbow();
			glTranslatef(-arm_length / 2, 0, 0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(this->_x, this->_y, this->_z);
			glRotatef(shoulder_angle, 0, 0, 1);					//Rotate with arm.

			glTranslatef(arm_length, 0, 0);
			glRotatef(elbow_angle, 0, 0, 1);					//Rotate with elbow
			glTranslatef(-arm_length, 0, 0);

			glTranslatef(arm_length * 2, 0, 0);					//Move to hand's position

			/*Rendering*/
			this->rendering_finger();
			this->rendering_thumb();
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
	}
	void rendering_arm_and_elbow()
	{
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		/*Arm Rotate*/
		glTranslatef(-((float)arm_length / 2), 0, 0);	//Move center to (0,0,0);
		glRotatef(shoulder_angle, 0, 0, 1);				//Rotate
		glTranslatef(((float)arm_length / 2), 0, 0);		//Move back

															/*Draw arm*/
		glPushMatrix();
		glScalef(arm_length, arm_height, arm_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();

		glTranslatef(arm_length, 0, 0);	//shift elbow position.

										/*Elbow Rotate*/
										//glTranslatef(-((float)arm_length / 2), ((float)arm_height / 2), 0);	//Move center to (0,0,0);
		glTranslatef(-((float)arm_length / 2), 0, 0);	//Move center to (0,0,0);
		glRotatef(elbow_angle, 0, 0, 1);									//Rotate
		glTranslatef(((float)arm_length / 2), 0, 0);	//Move center to (0,0,0);
														//glTranslatef(((float)arm_length / 2), -((float)arm_height / 2), 0);	//Move back

														/*Draw elbow*/
		glPushMatrix();
		glScalef(arm_length, arm_height, arm_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPopMatrix();
	}
	void rendering_finger()
	{
		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
		GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat no_shininess[] = { 0.0 };
		GLfloat low_shininess[] = { 5.0 };
		GLfloat high_shininess[] = { 100.0 };
		GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

		
		/*Draw second section finger*/
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef((finger_length)*cos(30 * 3.14159 / 180) / 2, arm_height - 0.1, 0); //Move to finger position
		glPushMatrix();
		glTranslatef(0, 0, finger_width); //Move to first finger position
		glRotatef(30, 0, 0, 1);			  //Rotate finger angle
		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(0, 0, 0); //Move to middle finger position
		glRotatef(30, 0, 0, 1);				//Rotate finger angle
		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0, 0, -finger_width); //Move to last finger position
		glRotatef(30, 0, 0, 1);				//Rotate finger angle
		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPopMatrix();

		/*Draw first section finger*/
		glPushMatrix();
		glTranslatef((finger_length)*cos(30 * 3.14159 / 180)*1.65, arm_height - 0.1, 0); //Move to finger position
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0, 0, finger_width);		//Move to first finger position
		glRotatef(-30, 0, 0, 1);				//Rotate finger angle

		glTranslatef(-finger_length / 2, -finger_height / 2, 0);
		glRotatef(finger_angle, 0, 0, 1);			//Rotate finger angle
		glTranslatef(finger_length / 2, finger_height / 2, 0);

		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(0, 0, 0);		//Move to middle finger position
		glRotatef(-30, 0, 0, 1);				//Rotate finger angle

		glTranslatef(-finger_length / 2, -finger_height / 2, 0);
		glRotatef(finger_angle, 0, 0, 1);			//Rotate finger angle
		glTranslatef(finger_length / 2, finger_height / 2, 0);

		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0, 0, -finger_width);		//Move to last finger position
		glRotatef(-30, 0, 0, 1);				//Rotate finger angle

		glTranslatef(-finger_length / 2, -finger_height / 2, 0);
		glRotatef(finger_angle, 0, 0, 1);			//Rotate finger angle
		glTranslatef(finger_length / 2, finger_height / 2, 0);

		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
		glPopMatrix();
	}
	void rendering_thumb()
	{
		glColor3f(1.0, 1.0, 1.0);
		/*Draw second section thumb*/
		glPushMatrix();
		glTranslatef((finger_length)*cos(30 * 3.14159 / 180) / 2, -(arm_height - 0.1), finger_width); //Move to first finger position
		glRotatef(-30, 0, 0, 1);				//Rotate finger angle
		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();

		/*Draw first section thumb*/
		glPushMatrix();
		glTranslatef((finger_length)*cos(30 * 3.14159 / 180)*1.65, -(arm_height - 0.1), finger_width); //Move to first finger position
		glRotatef(30, 0, 0, 1);				//Rotate finger angle

		if (finger_and_thumb_move)
			thumb_angle = finger_angle;
		glTranslatef(-finger_length / 2, finger_height / 2, 0);
		glRotatef(-thumb_angle, 0, 0, 1);			//Rotate finger angle
		glTranslatef(finger_length / 2, -finger_height / 2, 0);

		glScalef(finger_length, finger_height, finger_width);
		glutSolidSphere(0.7, 20, 16);
		glPopMatrix();
	}
private:
	float arm_length = 2.0;
	float arm_height = 0.3;
	float arm_width = 0.3;
	float finger_length = 0.4;
	float finger_height = 0.1;
	float finger_width = 0.1;
	int shoulder_angle = 0;
	int elbow_angle = 0;
	int elbow_shift = 5;		//The rotate angle of elbow each time. 
	int finger_angle = 0;
	int finger_shift = 3;
	int thumb_angle = 0;
	int thumb_shift = 3;
	int finger_and_thumb_move = 0;	//Move finger and thumb together.
	Bounding_box bounding_box;
	/*
	Bounding_box *_other_boxes[50];
	int other_boxes_number;*/
};