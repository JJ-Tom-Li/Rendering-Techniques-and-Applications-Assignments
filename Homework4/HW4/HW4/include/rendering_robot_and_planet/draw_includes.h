/*********************************
4104056004 李家駿 第四次作業 5/1
Includes needed headers and declares some constants.
*********************************/
#include "GL\glew.h"
#include "GL\glut.h"
#include "math.h"
#define INITIAL_WIDTH 500
#define INITIAL_HEIGHT 500
float arm_length = 2.0;
float arm_height = 0.3;
float arm_width = 0.3;
float finger_length = 0.4;
float finger_height = 0.1;
float finger_width = 0.1;
float sun_radius = 1.0;
float earth_radius = 0.2;
static int shoulder_angle = 0;
static int elbow_angle = 0;
static int elbow_shift = 5;		//The rotate angle of elbow each time. 
static int finger_angle = 0;
static int finger_shift = 3;
static int thumb_angle = 0;
static int thumb_shift = 3;
static int earth_day = 0;
static int earth_year = 0;
static int finger_and_thumb_move = 0;	//Move finger and thumb together.
void init_robot_and_planet()
{
	shoulder_angle = 0;
	elbow_angle = 0;
	elbow_shift = 5;
	finger_angle = 0;
	finger_shift = 3;
	thumb_angle = 0;
	thumb_shift = 3;
	earth_day = 0;
	earth_year = 0;
	finger_and_thumb_move = 0;
}
