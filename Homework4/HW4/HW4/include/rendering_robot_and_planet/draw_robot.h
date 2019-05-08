/*********************************
4104056004 李家駿 第四次作業 5/1
Drawing a robot hands.
*********************************/
#include "rendering_robot_and_planet/draw_planet.h"
void rendering_arm_and_elbow()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		/*Arm Rotate*/
		glTranslatef(-((float)arm_length / 2), 0, 0);	//Move center to (0,0,0);
		glRotatef(shoulder_angle, 0, 0, 1);				//Rotate
		glTranslatef(((float)arm_length / 2),0, 0);		//Move back
		
		/*Draw arm*/
		glPushMatrix();
			glScalef(arm_length, arm_height,arm_width);
			glutWireCube(1.0);
		glPopMatrix();

		glTranslatef(arm_length, 0, 0);	//shift elbow position.

		/*Arm Rotate*/
		glTranslatef(-((float)arm_length / 2), ((float)arm_height / 2), 0);	//Move center to (0,0,0);
		glRotatef(elbow_angle, 0, 0, 1);									//Rotate
		glTranslatef(((float)arm_length / 2), -((float)arm_height / 2), 0);	//Move back

		/*Draw elbow*/
		glPushMatrix();
			glScalef(arm_length, arm_height, arm_width);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();
}
void rendering_finger()
{
	glColor3f(1.0, 1.0, 1.0);
	/*Draw second section finger*/
	glPushMatrix();
		glTranslatef((finger_length )*cos(30 * 3.14159 / 180) / 2, arm_height - 0.1, 0); //Move to finger position
		glPushMatrix();
			glTranslatef(0, 0, finger_width); //Move to first finger position
			glRotatef(30, 0, 0, 1);			  //Rotate finger angle
			glScalef(finger_length, finger_height, finger_width);
			glutWireCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 0); //Move to middle finger position
			glRotatef(30, 0, 0, 1);				//Rotate finger angle
			glScalef(finger_length, finger_height, finger_width);
			glutWireCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, -finger_width); //Move to last finger position
			glRotatef(30, 0, 0, 1);				//Rotate finger angle
			glScalef(finger_length, finger_height, finger_width);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();

	/*Draw first section finger*/
	glPushMatrix();
		glTranslatef((finger_length)*cos(30 * 3.14159 / 180)*1.65, arm_height - 0.1, 0); //Move to finger position
		glPushMatrix();
			glTranslatef(0, 0, finger_width);		//Move to first finger position
			glRotatef(-30, 0, 0, 1);				//Rotate finger angle

			glTranslatef(-finger_length / 2, -finger_height / 2, 0);
			glRotatef(finger_angle,0,0,1);			//Rotate finger angle
			glTranslatef(finger_length/2,finger_height/2,0);

			glScalef(finger_length, finger_height, finger_width);
			glutWireCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 0);		//Move to middle finger position
			glRotatef(-30, 0, 0, 1);				//Rotate finger angle

			glTranslatef(-finger_length / 2, -finger_height / 2, 0);
			glRotatef(finger_angle, 0, 0, 1);			//Rotate finger angle
			glTranslatef(finger_length / 2, finger_height / 2, 0);

			glScalef(finger_length, finger_height, finger_width);
			glutWireCube(1.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, -finger_width);		//Move to last finger position
			glRotatef(-30, 0, 0, 1);				//Rotate finger angle

			glTranslatef(-finger_length / 2, -finger_height / 2, 0);
			glRotatef(finger_angle, 0, 0, 1);			//Rotate finger angle
			glTranslatef(finger_length / 2, finger_height / 2, 0);

			glScalef(finger_length, finger_height, finger_width);
			glutWireCube(1.0);
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
		glutWireCube(1.0);
	glPopMatrix();

	/*Draw first section thumb*/
	glPushMatrix();
		glTranslatef((finger_length)*cos(30 * 3.14159 / 180)*1.65, -(arm_height - 0.1), finger_width); //Move to first finger position
		glRotatef(30, 0, 0, 1);				//Rotate finger angle
		
		if(finger_and_thumb_move)
			thumb_angle = finger_angle;
		glTranslatef(-finger_length / 2, finger_height / 2, 0);
		glRotatef(-thumb_angle, 0, 0, 1);			//Rotate finger angle
		glTranslatef(finger_length / 2, -finger_height / 2, 0);

		glScalef(finger_length, finger_height, finger_width);
		glutWireCube(1.0);
	glPopMatrix();
}