#pragma once
#include <math.h>
#include "Vector3f.h"
#include "Matrix4x4.h"
#include <iostream>
#define SLERP_SWITCH_THRESHOLD 0.01f
using namespace std;
class Quaternion
{
public:
	union{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			float vec[4];
		};
	};
	//the identity quaternion
	Quaternion();
	//w is default 1
	Quaternion(float x, float y, float z);
	Quaternion(Vector3f rotations);
	Quaternion(float x, float y, float z, float w);
	~Quaternion();
	void Conjugate();
	static Quaternion Conjugate(Quaternion& quat);
	float Magnitude();
	static float Magnitude(Quaternion& quat);
	//note: this is in rads
	static Quaternion fromAxis(Vector3f axis, float angle);
	//transform into matrix4x4 for gpu use.
	Matrix4x4 ToMatrix();
	//transform into matrix4x4 for gpu use.
	static Matrix4x4 ToMatrix(Quaternion rotation);
	//normalize the quaternion
	void Normalize();
	//normalize the quaternion
	static Quaternion Normalize(Quaternion quaternion);
	//combine the rotations
	static Quaternion Mult(Quaternion left, Quaternion right);
	static Quaternion MultNoNormal(Quaternion& left, Quaternion& right);
	//rotate the vector
	static Vector3f Mult(Quaternion rotation, Vector3f vec);
	//invert the quaternion
	void Inverse();
	//return inverse rotation quaternion
	static Quaternion Inverse(Quaternion quaternion);
	//spherical linear interpolation
	static Quaternion Slerp(Quaternion start, Quaternion end, float alpha);
	//returns the angle between 2 quaternions. assumes they are normalized.
	float Dot(Quaternion right);
	static float Dot(Quaternion left, Quaternion right);
	//combine quaternions
	Quaternion operator*(Quaternion& right);
	void operator*=(Quaternion& right);
	Quaternion operator*(float right);
	//rotate a vector by a quaternion (vector is not normalized)
	Vector3f operator*(Vector3f& right);

	Quaternion operator-() const;
};

static Vector3f operator*(Vector3f& left, Quaternion& right)
{
	return right*left;
}

static ostream& operator<<(ostream& os, Quaternion& right)
{
	os << "x: " << right.x << "\ty: " << right.y << "\tz: " << right.z << "\tw: " << right.w;
	return os;
}
