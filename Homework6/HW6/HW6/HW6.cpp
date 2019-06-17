// HW5.cpp : 定義主控台應用程式的進入點。
//
/*********************************
4104056004 李家駿 第6次作業 5/29
**********************************

*********************************/
#include "stdafx.h"
//#include "rendering_robot_and_planet\draw_all.h"
#include "rendering_robot_and_planet\enemy.cpp"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <iostream>
#define PI 3.1415926
#define radians(x) x*PI/180
using namespace std;
static float camera_x = 0, camera_y = 0, camera_z = 3;
static float lookat_x = 0, lookat_y = 0, lookat_z = 0;
static float camera_up_x = 0, camera_up_y = 1, camera_up_z = 0;
static double camera_pitch = 0.0, camera_yaw = 0.0;
static int mouse_preX = 0, mouse_preY = 0;
static float light_i = 0.0;
static float angle_x = 0, angle_y = 0, angle_z = 0;
static bool fullscreen = false,
			snipe_open = false,
			anti_aliasing = false,
			fog_scene = false,
			offset_polygon = false;
GLfloat lamp_light_position[] = { -10.0, 10.0, 0.0, 0.0 };
GLfloat spot_direction[] = { -1,-1,0 };
vector<Bounding_box> collision_objects;
float degInRad;
Robot r1;	//Robotic arm
Planet p1;	//Planet
Wall w0_floor, w1, w2, w3, w4, w5;	//Walls
Enemy e1, e2, e3;	//Enemys
void init(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)500 / (GLfloat)500, 1.0, 60.0);
	//glShadeModel(GL_FLAT);
	//srand(time(NULL));
	camera_x = 0;
	camera_y = 0;
	camera_z = 0;
	lookat_x = 2;
	lookat_y = camera_y;
	lookat_z = 0;
	camera_up_x = 0;
	camera_up_y = 1;
	camera_up_z = 0;
	mouse_preX = glutGet(GLUT_WINDOW_WIDTH)/2;
	mouse_preY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouse_preX, mouse_preY);
	ShowCursor(false);
	camera_pitch = 0.0;
	camera_yaw = 0.0;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	light_i = 0;
	r1 = Robot(2, 0, 0);
	//r1.load_model("include/obj/al/al.obj");
	p1 = Planet(0, 30, 0);
	w0_floor = Wall(0, -5, 0, 200, 1, 200);

	w1 = Wall(100, 5, -50, 200, 50, 1);
	w2 = Wall(100, 5, 0, 1, 50, 200);
	w3 = Wall(10, 0, -5, 10, 10, 1);
	//w3.angle_y(-30);
	w4 = Wall(10, 0, 5, 10, 10, 1);
	//w4.angle_y(30);
	w5 = Wall(5, 0, 10, 10, 10, 1);
	
	e1 = Enemy(1, 2, -20);
	e1.load_model("include/obj/al/al.obj");
	e2 = Enemy(20, 2, 0);
	e2.load_model("include/obj/al/al.obj");
	e3 = Enemy(-1, 2, 20);
	e3.load_model("include/obj/al/al.obj");

	/*Create the bounding box array*/
	collision_objects.push_back(p1.bounding_box);
	collision_objects.push_back(w0_floor.bounding_box);
	collision_objects.push_back(w1.bounding_box);
	collision_objects.push_back(w2.bounding_box);
	collision_objects.push_back(w3.bounding_box);
	collision_objects.push_back(w4.bounding_box);
	collision_objects.push_back(w5.bounding_box);
	collision_objects.push_back(e1.bounding_box);
	collision_objects.push_back(e2.bounding_box);
	collision_objects.push_back(e3.bounding_box);
	
	/*Light0(Sun)*/

	/*Light1(Lamp)*/
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100 };
	//GLfloat light_position[] = { -2.0, 2.0, 0.0, 0.0 };
	//GLfloat sun_light_position[] = { (r1.get_arm_length() * -0.5)*cos(60 * 3.14159 / 360) , 0, -(r1.get_arm_length() * 8)*sin(60 * 3.14159 / 360),0 };
	GLfloat sun_light_position[] = { 0,25,0,1.0 };

	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat red_light[] = { 1.0,0.0,0.0,1.0 };
	GLfloat orange_light[] = { 1.0,(float)215 / 255,0.0,0.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat ca[] = { 2 };

	glShadeModel(GL_SMOOTH);

	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	//glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, ca);
	//glLightfv(GL_LIGHT0, GL_EMISSION, orange_light);
	glLightfv(GL_LIGHT1, GL_POSITION, lamp_light_position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, ca);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}
bool collision()
{
	for (int i = 0; i < collision_objects.size(); i++)
		if (r1.bounding_box.collision(collision_objects[i]))
			return true;
	return false;
}
void planet_idle_display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	/*Set the lamp*/
	degInRad = (light_i)*PI / 180;
	light_i += 0.5;
	if (light_i >= 360) light_i = 0;
	/*Rotate the lamp*/
	lamp_light_position[0] = cos(degInRad)*10.0;
	lamp_light_position[1] = 20;
	lamp_light_position[2] = sin(degInRad)*10.0;
	lamp_light_position[3] = 0.0;
	spot_direction[0] = 0;
	spot_direction[1] = -1;
	spot_direction[2] = 0;

	glutPostRedisplay();
}
void display()
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int width = glutGet(GLUT_WINDOW_WIDTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x, camera_y, camera_z, lookat_x+camera_x, lookat_y+camera_y, lookat_z+camera_z, camera_up_x,camera_up_y,camera_up_z);
	glPushMatrix();
	/*get angle of robot arm*/
	r1.angle_x(acos((lookat_x/(sqrt(lookat_x*lookat_x+ 0+ lookat_z*lookat_z))))*180/PI);//angle=arccos((A dot B)/(|A||B|))
	if (lookat_z > 0) r1.angle_x(-r1.angle_x());
	r1.angle_z(acos((lookat_y / (sqrt(lookat_x*lookat_x + lookat_y*lookat_y +0)))) * 180 / PI+90);//angle=arccos((A dot B)/(|A||B|))
	if (lookat_x > 0) r1.angle_z(-r1.angle_z());
	//cout << "robot angle=" << r1.angle_z() << endl;
																									  /*Rotate camera*/
	//glRotatef(angle_x, 1, 0, 0);	//Rotate scene by x-axis.
	//glRotatef(angle_y, 0, 1, 0);	//Rotate scene by y-axis.
	//glRotatef(angle_z, 0, 0, 1);	//Rotate scene by z-axis.

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//r1.load_draw();

	/*Draw sun*/
	p1.Draw_sun();

	/*Draw floor and walls*/
	w0_floor.Draw();
	w1.Draw();
	w2.Draw();
	w3.Draw();
	w4.Draw();
	w5.Draw();

	/*Draw enemys*/
	e1.Draw();
	e2.Draw();
	e3.Draw();

	///*Draw light and earth*/
	p1.Draw_earth();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(cos(degInRad)*2.0, 5, sin(degInRad)*2.0);
	glutSolidCube(0.5);
	glPopMatrix();
	glDisable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, lamp_light_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glEnable(GL_LIGHT1);
	glPopMatrix();

	/*Draw robotic arm*/
	if (snipe_open)//Draw scope if press b,no to show the arm.
		r1.rendering_scope(lookat_x,lookat_y,lookat_z);
	else
		r1.Draw();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(camera_x, camera_y, camera_z, lookat_x + camera_x, lookat_y + camera_y, lookat_z + camera_z, camera_up_x, camera_up_y, camera_up_z);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w>h)
		gluPerspective(65.0, 1 * (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	else
		gluPerspective(65.0*(GLfloat)h / (GLfloat)w, 1, 1.0, 100.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		/*Robot move*/
	case '1':
		/*Rotate shoulder*/
		r1.Rotate_shoulder();
		break;
	case '2':
		/*Rotate elbow*/
		r1.Rotate_elbow();
		break;
	case '3':
		/*Rotate finger*/
		r1.Rotate_finger();
		break;
	case '4':
		r1.Rotate_thumb();
		break;
		/*Move camera*/
	case 'W':
	case 'w':
		r1.Move(0.2 * lookat_x, 0, 0.2 * lookat_z);
		if (collision())
			r1.Move(-0.2 * lookat_x, 0, -0.2 * lookat_z);
			//r1.Move(-0.2, 0.0, 0.0);
		else {
			camera_x += 0.2 * lookat_x;
			camera_z += 0.2 * lookat_z;
			glutPostRedisplay();
		}
		break;
	case 'S':
	case 's':
		//r1.Move(-0.2, 0, 0);
		r1.Move(-0.2 * lookat_x, 0, -0.2 * lookat_z);
		if (collision())
			r1.Move(0.2 * lookat_x, 0, 0.2 * lookat_z);
			//r1.Move(0.2, 0.0, 0.0);
		else {
			camera_x -= 0.2 * lookat_x;
			camera_z -= 0.2 * lookat_z;
			glutPostRedisplay();
		}
		break;
	case 'A':
	case 'a':
		//r1.Move(0, 0, -0.2);
		r1.Move (-0.2*(-lookat_z), 0, -0.2*lookat_x);
		if (collision())
			//r1.Move(0.0, 0.0, 0.2);
			r1.Move(0.2*(-lookat_z), 0, 0.2*lookat_x);
		else {
			camera_x -= 0.2*(-lookat_z);
			camera_z -= 0.2*lookat_x;
			glutPostRedisplay();
		}
		break;
	case 'D':
	case 'd':
		//r1.Move(0, 0, 0.2);
		r1.Move(0.2*(-lookat_z), 0, 0.2*lookat_x);
		if (collision())
			r1.Move(-0.2*(-lookat_z), 0, -0.2*lookat_x);
			//r1.Move(0.0, 0.0, -0.2);
		else {
			camera_x += 0.2*(-lookat_z);
			camera_z += 0.2*lookat_x;
			glutPostRedisplay();
		}
		break;

	/*arm move*/
	case 32://space:up
		r1.Move(0.0, 0.1, 0.0);
		if (collision())
			r1.Move(0.0, -0.1, 0.0);
		else
			glutPostRedisplay();
		break;
	case 'X':
	case 'x':
		r1.Move(0.0, -0.1, 0.0);
		if(collision())
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

		mouse_preX = glutGet(GLUT_WINDOW_WIDTH) / 2;
		mouse_preY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
		glutWarpPointer(mouse_preX, mouse_preY);
		break;
	case 'B':
	case 'b':
		/*Snipe your target with blending.*/
		if (snipe_open)
		{
			cout << "Disable snipe scope.\n";
			glutPostRedisplay();
			snipe_open = false;
		}
		else
		{
			cout << "Enable snipe scope.\n";
			//r1.rendering_scope();
			glutPostRedisplay();
			snipe_open = true;
		}
		break;
	case 'C':
	case 'c':
		/*Anti aliasing*/
		if (anti_aliasing)
		{
			cout << "Disable anti aliasing.\n";
			//glDisable(GL_LINE_SMOOTH);
			//glDisable(GL_POLYGON_SMOOTH);
			glDisable(GL_MULTISAMPLE_ARB);
			glutPostRedisplay();
			anti_aliasing = false;
		}
		else
		{
			cout << "Enable anti aliasing.\n";
			//glEnable(GL_LINE_SMOOTH);
			//glEnable(GL_POLYGON_SMOOTH);
			glEnable(GL_MULTISAMPLE_ARB);
			glutPostRedisplay();
			anti_aliasing = true;
		}
		break;
	case 'F':
	case 'f':
		/*Open the fog*/
		if (fog_scene)
		{
			cout << "Disable fog.\n";
			glDisable(GL_FOG);
			glutPostRedisplay();
			fog_scene = false;
		}
		else
		{
			cout << "Enable fog.\n";
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glEnable(GL_FOG);
			{
				GLfloat fogColor[4] = { 0.1, 0.5, 0.5, 1.0 };

				glFogi(GL_FOG_MODE, GL_EXP2);
				glFogfv(GL_FOG_COLOR, fogColor);
				glFogf(GL_FOG_DENSITY, 0.05);
				glHint(GL_FOG_HINT, GL_DONT_CARE);
				glFogf(GL_FOG_START, 60.0);
				glFogf(GL_FOG_END, 200.0);
			}
			glClearColor(0.1, 0.5, 0.5, 1.0);  /* fog color */
			glutPostRedisplay();
			fog_scene = true;
		}
		break;
	case 'P':
	case 'p':
		/*Offset the polygons.*/
		if (offset_polygon)
		{
			cout << "Disable polygon offset.\n";
			glDisable(GL_POLYGON_OFFSET_FILL);
			glutPostRedisplay();
			offset_polygon = false;
		}
		else
		{
			cout << "Enable polygon offset.\n";
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0,1.0);
			glutPostRedisplay();
			offset_polygon = true;
		}
		break;
	case 'V':
	case 'v':
		if (draw_box)
		{
			cout << "Hide the bounding box\n";
			draw_box = false;
			glutPostRedisplay();
		}
		else
		{
			cout << "Show the bounding box\n";
			draw_box = true;
			glutPostRedisplay();
		}
		break;
	case '0':
		init();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
void special_keyboard(int key, int x, int y)
{
	/*switch (key) {
	case GLUT_KEY_UP:
		r1.Move(0.1, 0, 0);
		if (collision())
			r1.Move(-0.1, 0.0, 0.0);
		else
			glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		r1.Move(-0.1, 0, 0);
		if (collision())
			r1.Move(0.1, 0.0, 0.0);
		else
			glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		r1.Move(0, 0, -0.1);
		if (collision())
			r1.Move(0.0, 0.0, 0.1);
		else
			glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		r1.Move(0, 0, 0.1);
		if (collision())
			r1.Move(0.0, 0.0, -0.1);
		else
			glutPostRedisplay();
		break;
	default:
		break;
	}*/
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
void move_mouse(int x, int y) {
	int width = glutGet(GLUT_WINDOW_WIDTH), height = glutGet(GLUT_WINDOW_HEIGHT);
	if (x < 0 || x > width || y < 0 || y > height) {
		//Avoid cursor out of window.
		if (x <= 0) x = mouse_preX = width - 1;
		if (x >= width) x = mouse_preX = 1;
		if (y <= 0) y = mouse_preY = height - 1;
		if (y >= height) y = mouse_preY = 1;
		//Set cursor position
		glutWarpPointer(x, y);
		//glfwSetCursorPos(window, curPosX, curPosY);
	}
	if (x != mouse_preX || y != mouse_preY) {
		camera_pitch += (mouse_preY - y) * 0.5; 
		//限制pitch範圍(-60~89)
		camera_pitch = camera_pitch > 90 ? 90 : camera_pitch;
		camera_pitch = camera_pitch < -60 ? -60 : camera_pitch;
		camera_yaw += (x - mouse_preX) * 0.5;
		//限制yaw範圍(
		//camera_yaw = camera_yaw > 60 ? 60 : camera_yaw;
		//camera_yaw = camera_yaw < -60 ? -60 : camera_yaw;

		lookat_x = cos(radians(camera_pitch))*cos(radians(camera_yaw));
		lookat_y = sin(radians(camera_pitch));
		lookat_z = cos(radians(camera_pitch))*sin(radians(camera_yaw));
		glutPostRedisplay();
		//cout << "pre:" << mouse_preX << "," << mouse_preY << endl;
		//cout << "now:" << x << "," << y << endl;
		mouse_preX = x;
		mouse_preY = y;
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
	glutCreateWindow("Homework6");
	init();
	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);		//Keep the shape of objects.
	glutKeyboardFunc(keyboard);		//Get the keyboard input.
	glutSpecialFunc(special_keyboard); //Get special keyboard input.
	glutMouseFunc(mouse);			//Get the mouse input.
	glutPassiveMotionFunc(move_mouse);
	glutIdleFunc(planet_idle_display);//Planet rotating function.
	glutMainLoop();

	return 0;   /* ANSI C requires main to return int. */
}
