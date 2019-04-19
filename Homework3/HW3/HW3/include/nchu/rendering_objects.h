/*********************************
4104056004 李家駿 第三次作業 4/17
This file stores the rendering polygon objects.
*********************************/
#include "coordinates.h"
typedef struct _rendering_object {  //the polygon object struct
	
	float color[3];		//color
	GLfloat *vertices;	//vertices array
	int vnumber;		//number of vertices
}Rendering_object;

/*中文字********************************/
Rendering_object ch1 = {
	{ 1.0,1.0,1.0 },	//color
	vertices_ch1,		//vertices_array
	sizeof(vertices_ch1) / sizeof(GLfloat)	//number of vertices
};
Rendering_object ch2 = {
	{ 1.0,1.0,1.0 },	//color
	vertices_ch2,		//vertices_array
	sizeof(vertices_ch2) / sizeof(GLfloat)	//number of vertices
};
Rendering_object ch3 = {
	{ 1.0,1.0,1.0 },	//color
	vertices_ch3,		//vertices_array
	sizeof(vertices_ch3) / sizeof(GLfloat)	//number of vertices
};
Rendering_object ch4 = {
	{ 1.0,1.0,1.0 },	//color
	vertices_ch4,		//vertices_array
	sizeof(vertices_ch4) / sizeof(GLfloat)	//number of vertices
};
Rendering_object ch5 = {
	{ 1.0,1.0,1.0 },	//color
	vertices_ch5,		//vertices_array
	sizeof(vertices_ch5) / sizeof(GLfloat)	//number of vertices
};
Rendering_object ch6 = {
	{ 1.0,1.0,1.0 },	//color
	vertices_ch6,		//vertices_array
	sizeof(vertices_ch6) / sizeof(GLfloat)	//number of vertices
};

/*英文字********************************/
Rendering_object letter_N = {
	{ 1.0,1.0,1.0 },	//color
	vertices_N,		//vertices_array
	sizeof(vertices_N) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_C = {
	{ 1.0,.5,1.0 },	//color
	vertices_C,		//vertices_array
	sizeof(vertices_C) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_H = {
	{ 1.0,.6,1.0 },	//color
	vertices_H,		//vertices_array
	sizeof(vertices_H) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_U = {
	{ 1.0,.7,1.0 },	//color
	vertices_U,		//vertices_array
	sizeof(vertices_U) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_a = {
	{ 1.0,.8,1.0 },	//color
	vertices_a,		//vertices_array
	sizeof(vertices_a) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_e = {
	{ 1.0,.9,1.0 },	//color
	vertices_e,		//vertices_array
	sizeof(vertices_e) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_g = {
	{ 1.0,1.0,.4 },	//color
	vertices_g,		//vertices_array
	sizeof(vertices_g) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_h = {
	{ 1.0,1.0,.5 },	//color
	vertices_h,		//vertices_array
	sizeof(vertices_h) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_i = {
	{ 1.0,1.0,.6 },	//color
	vertices_i,		//vertices_array
	sizeof(vertices_i) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_l = {
	{ 1.0,1.0,.7 },	//color
	vertices_l,		//vertices_array
	sizeof(vertices_l) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_n = {
	{ 1.0,1.0,.8 },	//color
	vertices_n,		//vertices_array
	sizeof(vertices_n) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_o = {
	{ 1.0,1.0,.9 },	//color
	vertices_o,		//vertices_array
	sizeof(vertices_o) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_r = {
	{ 1.0,1.0,.87 },	//color
	vertices_r,		//vertices_array
	sizeof(vertices_r) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_s = {
	{ 1.0,1.0,1.0 },	//color
	vertices_s,		//vertices_array
	sizeof(vertices_s) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_t = {
	{ 1.0,1.0,1.0 },	//color
	vertices_t,		//vertices_array
	sizeof(vertices_t) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_u = {
	{ 1.0,1.0,1.0 },	//color
	vertices_u,		//vertices_array
	sizeof(vertices_u) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_v = {
	{ 1.0,1.0,1.0 },	//color
	vertices_v,		//vertices_array
	sizeof(vertices_v) / sizeof(GLfloat)	//number of vertices
};
Rendering_object letter_y = {
	{ 1.0,1.0,1.0 },	//color
	vertices_y,		//vertices_array
	sizeof(vertices_y) / sizeof(GLfloat)	//number of vertices
};

/*校徽********************************/
Rendering_object logo_square = {
	{ .0f,0.3f,1.0f },	//color
	vertices_logo_square,		//vertices_array
	sizeof(vertices_logo_square) / sizeof(GLfloat)	//number of vertices
};
Rendering_object logo_circle = {
	{ 1.0f,.0f,.0f },	//color
	vertices_logo_circle,		//vertices_array
	sizeof(vertices_logo_circle) / sizeof(GLfloat)	//number of vertices
};