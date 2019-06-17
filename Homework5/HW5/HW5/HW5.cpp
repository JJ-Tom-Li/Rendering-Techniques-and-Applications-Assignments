// HW5.cpp : 定義主控台應用程式的進入點。
//
/*********************************
4104056004 李家駿 第五次作業 5/13
**********************************
Usage--
	Move camera:
		W:Move Camera forward.
		S:Move Camera backward.
		A:Move Camera left.
		D:Move Camera right.
	Move robotic arm:
		Up:Move arm forward.
		Down:Move arm backward.
		Left:Move arm left.
		Right:Move arm right.
		Space:Move arm up.
		X:Move arm down.
		3:Move fingers.
		4:Move thumb.

*********************************/
#include "stdafx.h"
//#include "rendering_robot_and_planet\draw_all.h"
//#include "rendering_robot_and_planet\robot.cpp"
#include "rendering_robot_and_planet\wall.cpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
static float camera_x = 0, camera_y = 0, camera_z = 3;
static float light_i = 0.0;
static float angle_x = 0, angle_y = 0, angle_z = 0;
static bool fullscreen = false;
GLfloat lamp_light_position[] = { -2.0, 2.0, 0.0, 0.0 };
GLfloat spot_direction[] = { -1,-1,0 };
float degInRad;
Robot r1;
Planet p1;
Wall w0_floor,w1,w2,w3,w4,w5;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)500 / (GLfloat)500, 1.0, 60.0);
	glShadeModel(GL_FLAT);
	srand(time(NULL));
	camera_x = 2;
	camera_y = 0;
	camera_z = 20;
	angle_x = 0;
	angle_y = 60;
	angle_z = 0;
	light_i = 0;
	r1 = Robot(2, 0, 0);
	p1 = Planet(r1.get_arm_length() * 8, 0, 0);
	w0_floor = Wall(0, -5, 0, 100, 1, 100);
	w1 = Wall(10, 5, -10, 50, 50, 1);
	w2 = Wall(20, 5, 0, 1, 50, 50);
	w3 = Wall(10, 0,-5 , 10, 10, 1);
	//w3.angle_y(-30);
	w4 = Wall(10, 0, 5, 10, 10, 1);
	//w4.angle_y(30);
	w5 = Wall(5, 0, 10, 10, 10, 1);
	/*Bounding_box *other_boxes[] = { p1.bounding_box,w1.bounding_box,w2.bounding_box ,w3.bounding_box ,w4.bounding_box ,w5.bounding_box };
	r1.other_boxes(other_boxes, 6);
	for (int i = 0; i < 6; i++) {
		cout << r1.other_boxes[i].x() << "," << r1.other_boxes[i].y() << "," << r1.other_boxes[i].z() << endl;
	}*/
	/*Light0(Sun)*/

	/*Light1(Lamp)*/
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100 };
	//GLfloat light_position[] = { -2.0, 2.0, 0.0, 0.0 };
	GLfloat sun_light_position[] = { (r1.get_arm_length() * -0.5)*cos(60*3.14159/360) , 0, -(r1.get_arm_length() * 8)*sin(60 * 3.14159 / 360),0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat red_light[] = { 1.0,0.0,0.0,1.0 };
	GLfloat orange_light[] = { 1.0,(float)215/255,0.0,0.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat ca[] = { 2};
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, ca);
	//glLightfv(GL_LIGHT0, GL_EMISSION, orange_light);
	glLightfv(GL_LIGHT1, GL_POSITION, lamp_light_position);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, orange_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, orange_light);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, ca);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}
void planet_idle_display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);

	glClear(GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		/*Rotate camera*/
		glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
		glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
		glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

		/*Draw earth*/
		//p1.Draw_earth();

		/*Set the lamp*/
		degInRad = (light_i)*3.14159 / 180;
		light_i += 0.5;
		if (light_i >= 360) light_i = 0;
		//if (ceil(light_i) == light_i) {
		/*Rotate the lamp*/
		lamp_light_position[0] = cos(degInRad)*2.0;
		lamp_light_position[1] = 5;
		lamp_light_position[2] = sin(degInRad)*2.0;
		lamp_light_position[3] = 0.0;
		spot_direction[0] = 0 ;
		spot_direction[1] = -1;
		spot_direction[2] = 0 ;
		/*glPushMatrix();
		glTranslatef(cos(degInRad)*2.0, 5, sin(degInRad)*2.0);
		glutSolidCube(0.5);
		glPopMatrix();
		glLightfv(GL_LIGHT1, GL_POSITION, lamp_light_position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glEnable(GL_LIGHT1);*/
		//}
	glPopMatrix();

	//glFlush();
	//glutSwapBuffers();
	glutPostRedisplay();
}
void display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glPushMatrix();
		/*Rotate camera*/
		glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
		glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
		glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*Draw robotic arm*/
		r1.Draw();

		/*Draw sun*/
		p1.Draw_sun();

		/*Draw floor and walls*/
		w0_floor.Draw();
		w1.Draw();
		w2.Draw();
		w3.Draw();
		w4.Draw();
		w5.Draw();

		/*Draw light and earth*/
		p1.Draw_earth();
		glPushMatrix();
		glTranslatef(cos(degInRad)*2.0, 5, sin(degInRad)*2.0);
		glutSolidCube(0.5);
		glPopMatrix();
		glDisable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, lamp_light_position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
		glEnable(GL_LIGHT1);
	glPopMatrix();
	//glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, camera_x, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w>h)
		gluPerspective(65.0, 1 * (GLfloat)w / (GLfloat)h, 1.0, 60.0);
	else
		gluPerspective(65.0*(GLfloat)h / (GLfloat)w, 1, 1.0, 60.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		/*Robot move*/
	case '1':
		/*Rotate shoulder*/
		//r1.Rotate_shoulder();
		break;
	case '2':
		/*Rotate elbow*/
		//r1.Rotate_elbow();
		break;
	case '3':
		/*Rotate finger*/
		r1.Rotate_finger();
		break;
	case '4':
		r1.Rotate_thumb();
		break;
	//case '5':
		/*degInRad = (light_i)*3.14159 / 180;
		if (light_i >= 360) light_i = 0;
		light_position[0] = cos(degInRad)*2.0;
		light_position[1]= 0;
		light_position[2] = sin(degInRad)*2.0;
		light_position[3] = 0.0;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);*/
	//	glutPostRedisplay();
	//	break;
		/*Move camera*/
	case 'W':
	case 'w':
		camera_z -= 0.1;
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		camera_z += 0.1;
		glutPostRedisplay();
		break;
	case 'A':
	case 'a':
		camera_x -= 0.2;
		glutPostRedisplay();
		break;
	case 'D':
	case 'd':
		camera_x += 0.2;
		glutPostRedisplay();
		break;
	
	/*arm move*/
	case 32://space:up
		r1.Move(0.0, 0.1, 0.0); 
		if (r1.collision(w0_floor.x(), w0_floor.y(), w0_floor.z(), w0_floor.width(), w0_floor.height(), w0_floor.length())
			|| r1.collision(w1.bounding_box.x(), w1.bounding_box.y(), w1.bounding_box.z(), w1.bounding_box.width(), w1.bounding_box.height(), w1.bounding_box.length())
			|| r1.collision(w2.bounding_box.x(), w2.bounding_box.y(), w2.bounding_box.z(), w2.bounding_box.width(), w2.bounding_box.height(), w2.bounding_box.length())
			|| r1.collision(w3.bounding_box.x(), w3.bounding_box.y(), w3.bounding_box.z(), w3.bounding_box.width(), w3.bounding_box.height(), w3.bounding_box.length())
			|| r1.collision(w4.bounding_box.x(), w4.bounding_box.y(), w4.bounding_box.z(), w4.bounding_box.width(), w4.bounding_box.height(), w4.bounding_box.length())
			|| r1.collision(w5.bounding_box.x(), w5.bounding_box.y(), w5.bounding_box.z(), w5.bounding_box.width(), w5.bounding_box.height(), w5.bounding_box.length())
			|| r1.collision(p1.bounding_box.x(), p1.bounding_box.y(), p1.bounding_box.z(), p1.bounding_box.width(), p1.bounding_box.height(), p1.bounding_box.length())
			)
			r1.Move(0.0, -0.1, 0.0);
		else
			glutPostRedisplay();
		break;
	case 'X':
	case 'x':
		r1.Move(0.0, -0.1, 0.0);
		if (r1.collision(w0_floor.x(), w0_floor.y(), w0_floor.z(), w0_floor.width(), w0_floor.height(), w0_floor.length())
			|| r1.collision(w1.bounding_box.x(), w1.bounding_box.y(), w1.bounding_box.z(), w1.bounding_box.width(), w1.bounding_box.height(), w1.bounding_box.length())
			|| r1.collision(w2.bounding_box.x(), w2.bounding_box.y(), w2.bounding_box.z(), w2.bounding_box.width(), w2.bounding_box.height(), w2.bounding_box.length())
			|| r1.collision(w3.bounding_box.x(), w3.bounding_box.y(), w3.bounding_box.z(), w3.bounding_box.width(), w3.bounding_box.height(), w3.bounding_box.length())
			|| r1.collision(w4.bounding_box.x(), w4.bounding_box.y(), w4.bounding_box.z(), w4.bounding_box.width(), w4.bounding_box.height(), w4.bounding_box.length())
			|| r1.collision(w5.bounding_box.x(), w5.bounding_box.y(), w5.bounding_box.z(), w5.bounding_box.width(), w5.bounding_box.height(), w5.bounding_box.length())
			|| r1.collision(p1.bounding_box.x(), p1.bounding_box.y(), p1.bounding_box.z(), p1.bounding_box.width(), p1.bounding_box.height(), p1.bounding_box.length())
			)
			r1.Move(0.0, 0.1, 0.0);
		else
			glutPostRedisplay();
		break;
	/*Other*/
	case 'Z':
	case 'z':
		if (fullscreen)
		{
			glutReshapeWindow(INITIAL_WIDTH, INITIAL_HEIGHT);
			glutPositionWindow(100, 100);
			fullscreen = false;
		}
		else
		{
			glutFullScreen();
			fullscreen = true;
		}
		break;
	case '0':
		init();
		//init_robot_and_planet();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
void special_keyboard(int key,int x,int y)
{
	switch (key) {
		case GLUT_KEY_UP:
			r1.Move(0.1, 0, 0);
			if (r1.collision(w0_floor.x(), w0_floor.y(), w0_floor.z(), w0_floor.width(), w0_floor.height(), w0_floor.length())
				|| r1.collision(w1.bounding_box.x(), w1.bounding_box.y(), w1.bounding_box.z(), w1.bounding_box.width(), w1.bounding_box.height(), w1.bounding_box.length())
				|| r1.collision(w2.bounding_box.x(), w2.bounding_box.y(), w2.bounding_box.z(), w2.bounding_box.width(), w2.bounding_box.height(), w2.bounding_box.length())
				|| r1.collision(w3.bounding_box.x(), w3.bounding_box.y(), w3.bounding_box.z(), w3.bounding_box.width(), w3.bounding_box.height(), w3.bounding_box.length())
				|| r1.collision(w4.bounding_box.x(), w4.bounding_box.y(), w4.bounding_box.z(), w4.bounding_box.width(), w4.bounding_box.height(), w4.bounding_box.length())
				|| r1.collision(w5.bounding_box.x(), w5.bounding_box.y(), w5.bounding_box.z(), w5.bounding_box.width(), w5.bounding_box.height(), w5.bounding_box.length())
				|| r1.collision(p1.bounding_box.x(), p1.bounding_box.y(), p1.bounding_box.z(), p1.bounding_box.width(), p1.bounding_box.height(), p1.bounding_box.length())
				)
				r1.Move(-0.1, 0.0, 0.0);
			else
				glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			r1.Move(-0.1, 0, 0);
			if (r1.collision(w0_floor.x(), w0_floor.y(), w0_floor.z(), w0_floor.width(), w0_floor.height(), w0_floor.length())
				|| r1.collision(w1.bounding_box.x(), w1.bounding_box.y(), w1.bounding_box.z(), w1.bounding_box.width(), w1.bounding_box.height(), w1.bounding_box.length())
				|| r1.collision(w2.bounding_box.x(), w2.bounding_box.y(), w2.bounding_box.z(), w2.bounding_box.width(), w2.bounding_box.height(), w2.bounding_box.length())
				|| r1.collision(w3.bounding_box.x(), w3.bounding_box.y(), w3.bounding_box.z(), w3.bounding_box.width(), w3.bounding_box.height(), w3.bounding_box.length())
				|| r1.collision(w4.bounding_box.x(), w4.bounding_box.y(), w4.bounding_box.z(), w4.bounding_box.width(), w4.bounding_box.height(), w4.bounding_box.length())
				|| r1.collision(w5.bounding_box.x(), w5.bounding_box.y(), w5.bounding_box.z(), w5.bounding_box.width(), w5.bounding_box.height(), w5.bounding_box.length())
				|| r1.collision(p1.bounding_box.x(), p1.bounding_box.y(), p1.bounding_box.z(), p1.bounding_box.width(), p1.bounding_box.height(), p1.bounding_box.length())
				)
				r1.Move(0.1, 0.0, 0.0);
			else
				glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			r1.Move(0, 0, -0.1);
			if (r1.collision(w0_floor.x(), w0_floor.y(), w0_floor.z(), w0_floor.width(), w0_floor.height(), w0_floor.length())
				|| r1.collision(w1.bounding_box.x(), w1.bounding_box.y(), w1.bounding_box.z(), w1.bounding_box.width(), w1.bounding_box.height(), w1.bounding_box.length())
				|| r1.collision(w2.bounding_box.x(), w2.bounding_box.y(), w2.bounding_box.z(), w2.bounding_box.width(), w2.bounding_box.height(), w2.bounding_box.length())
				|| r1.collision(w3.bounding_box.x(), w3.bounding_box.y(), w3.bounding_box.z(), w3.bounding_box.width(), w3.bounding_box.height(), w3.bounding_box.length())
				|| r1.collision(w4.bounding_box.x(), w4.bounding_box.y(), w4.bounding_box.z(), w4.bounding_box.width(), w4.bounding_box.height(), w4.bounding_box.length())
				|| r1.collision(w5.bounding_box.x(), w5.bounding_box.y(), w5.bounding_box.z(), w5.bounding_box.width(), w5.bounding_box.height(), w5.bounding_box.length())
				|| r1.collision(p1.bounding_box.x(), p1.bounding_box.y(), p1.bounding_box.z(), p1.bounding_box.width(), p1.bounding_box.height(), p1.bounding_box.length())
				)
				r1.Move(0.0, 0.0, 0.1);
			else
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			r1.Move(0, 0, 0.1);
			if (r1.collision(w0_floor.x(), w0_floor.y(), w0_floor.z(), w0_floor.width(), w0_floor.height(), w0_floor.length())
				|| r1.collision(w1.bounding_box.x(), w1.bounding_box.y(), w1.bounding_box.z(), w1.bounding_box.width(), w1.bounding_box.height(), w1.bounding_box.length())
				|| r1.collision(w2.bounding_box.x(), w2.bounding_box.y(), w2.bounding_box.z(), w2.bounding_box.width(), w2.bounding_box.height(), w2.bounding_box.length())
				|| r1.collision(w3.bounding_box.x(), w3.bounding_box.y(), w3.bounding_box.z(), w3.bounding_box.width(), w3.bounding_box.height(), w3.bounding_box.length())
				|| r1.collision(w4.bounding_box.x(), w4.bounding_box.y(), w4.bounding_box.z(), w4.bounding_box.width(), w4.bounding_box.height(), w4.bounding_box.length())
				|| r1.collision(w5.bounding_box.x(), w5.bounding_box.y(), w5.bounding_box.z(), w5.bounding_box.width(), w5.bounding_box.height(), w5.bounding_box.length())
				|| r1.collision(p1.bounding_box.x(), p1.bounding_box.y(), p1.bounding_box.z(), p1.bounding_box.width(), p1.bounding_box.height(), p1.bounding_box.length())
				)
				r1.Move(0.0, 0.0, -0.1);
			else
				glutPostRedisplay();
			break;
		default:
			break;
	}
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)	//Rotate by z-axis while press left button of mouse.
		{
			angle_z = ((int)angle_z + 30) % 360;
			glutPostRedisplay();
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)	//Rotate by y-axis while press left button of mouse.
		{
			angle_y = ((int)angle_y + 10) % 360;
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)	//Rotate by x-axis while press left button of mouse.
		{
			angle_x = ((int)angle_x + 30) % 360;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}
/*
* Declare initial window size, position, and display mode
* (single buffer and RGBA).  Open window with "hello"
* in its title bar.  Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Homework4");
	init();
	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);		//Keep the shape of objects.
	glutKeyboardFunc(keyboard);		//Get the keyboard input.
	glutSpecialFunc(special_keyboard); //Get special keyboard input.
	glutMouseFunc(mouse);			//Get the mouse input.
	glutIdleFunc(planet_idle_display);//Planet rotating function.
	glutMainLoop();

	return 0;   /* ANSI C requires main to return int. */
}
