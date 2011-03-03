#include <cmath>

#include "Vector3d.h"

/** Default constructor */
Vector3d::Vector3d() {
}

/**
 * Public constructor
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 */
Vector3d::Vector3d(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
	length = sqrt(x * x + y * y + z * z);
}

/**
 * Compute the normalized vector
 * @return Normalized vector
 */
Vector3d Vector3d::getNormalizedVector() {
	return (*this) / length;
}

/**
 * Override the operator +. Add two vectors
 * @param v Second vector for the addition
 * @return Result of the addition
 */
Vector3d Vector3d::operator +(Vector3d v) {
	return Vector3d(x + v.x, y + v.y, z + v.z);
}

/**
 * Override the operator -. Substract two vectors
 * @param v Second vector for the substraction
 * @return Result of the substraction
 */
Vector3d Vector3d::operator -(Vector3d v) {
	return Vector3d(x - v.x, y - v.y, z - v.z);
}

/**
 * Override the operator *. Multiply each coordinate of the vector by a number
 * @param num Factor for the multiplication
 * @return Result of the multiplication
 */
Vector3d Vector3d::operator *(GLfloat num) {
	return Vector3d(x * num, y * num, z * num);
}

/**
 * Override the operator /. Divide each coordinate of the vector by a number
 * @param num Factor for the division
 * @return Result of the division
 */
Vector3d Vector3d::operator /(GLfloat num) {
	return Vector3d(x / num, y / num, z / num);
}

/**
 * Override the operator %. Compute a cross product between two vectors
 * @param v Second vector for the cross product
 * @return Result of the cross product
 */
Vector3d Vector3d::operator %(Vector3d v) {
	return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}