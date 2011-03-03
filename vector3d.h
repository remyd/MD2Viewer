#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Vector3d {
public:
	Vector3d();
	Vector3d(GLfloat x, GLfloat y, GLfloat z);
	GLfloat getLength();
	Vector3d getNormalizedVector();
	Vector3d operator +(Vector3d v);
	Vector3d operator -(Vector3d v);
	Vector3d operator *(GLfloat num);
	Vector3d operator /(GLfloat num);
	Vector3d operator %(Vector3d v);
	GLfloat x, y, z, length;
};

#endif