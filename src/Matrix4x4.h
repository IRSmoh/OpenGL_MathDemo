#pragma once
#include <math.h>
#include "Vector3f.h"
#include <iostream>
#include <xmmintrin.h>
using namespace std;

class Matrix4x4
{
public:
	union
	{
		struct
		{
			float mat[16];
		};
		struct
		{
			//this is the memory layout, not the accessor layout.
			float m11, m21, m31, m41;
			float m12, m22, m32, m42;
			float m13, m23, m33, m43;
			float m14, m24, m34, m44;
			//the accessor layout is meant to be this:
			/*
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
			*/
		};
	};
	//the default constructor returns a unit matrix
	Matrix4x4();
	Matrix4x4(float (&mat)[16]);
	~Matrix4x4();
	//intializes the scale of the vector
	Matrix4x4(Vector3f diagonal);
	Matrix4x4(float m11, float m12, float  m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	void TranslateBy(Vector3f translate);
	///statics
	static Matrix4x4 Transpose(Matrix4x4& right);
	Matrix4x4 Transpose();
	static float Determinate(Matrix4x4& right);
	float Determinate();
	static Matrix4x4 Inverse(Matrix4x4& right);
	Matrix4x4 Inverse();
	static Matrix4x4 InverseTransform(Matrix4x4& transform);
	Matrix4x4 InverseTransform();
	static Vector3f ExtractScale(Matrix4x4& matrix);
	Vector3f ExtractScale();
	static Vector3f ExtractInverseScale(Matrix4x4& right);
	Vector3f ExtractInverseScale();
	static Matrix4x4 makeRotationY(float rotY);
	static Matrix4x4 makeRotationX(float rotX);
	static Matrix4x4 makeRotationZ(float rotZ);
	static Matrix4x4 makeZero();
	static Matrix4x4 makePerspective(float fov, float aspect, float nearPlane, float farPlane);
	static Matrix4x4 makeTranslate(Vector3f translate);
	//this assumes the out matrix is already a valid rotation matrix.
	static void LookAt(Vector3f& eye, Vector3f& lookAtPoint, Vector3f& up, Matrix4x4& out);
	static void M4x4_SSE(Matrix4x4& left, Matrix4x4& right, Matrix4x4& out);
	//this is 2x faster than default multiplying
	Matrix4x4 M4x4_SSE(Matrix4x4& right);
	//this is 2x faster than default multiplying
	static Matrix4x4 M4x4_SSE(Matrix4x4& left, Matrix4x4& right);
	//this is 4x faster than default multiplying
	void M4x4_SSE_Fast(float* right, float* out);
	//this is 4x faster than default multiplying
	static void M4x4_SSE_Fast(float* left, float* right, float* out);
	//legacy support (lol older than 2001 chip)
	static void M4x4_Slow(float* left, float* right, float* out);
	///operators
	Matrix4x4 operator*(Matrix4x4& right);
	//this kinda lies from the face of it, it performs right * this instead of the 'proper' this * right basically, use it how you want, and it'll prolly work
	void operator*=(Matrix4x4& right);
	Matrix4x4 operator*(float right);

	Vector3f operator*(Vector3f& right);
	float& operator[](const int index);
};

static ostream& operator<<(ostream& os, Matrix4x4& mat)
{
	os << "===================================\n";
	os << mat.m11 << "\t" << mat.m12 << "\t" << mat.m13 << "\t" << mat.m14 << "\n";
	os << mat.m21 << "\t" << mat.m22 << "\t" << mat.m23 << "\t" << mat.m24 << "\n";
	os << mat.m31 << "\t" << mat.m32 << "\t" << mat.m33 << "\t" << mat.m34 << "\n";
	os << mat.m41 << "\t" << mat.m42 << "\t" << mat.m43 << "\t" << mat.m44 << "\n";
	os << "\n===================================\n";
	return os;
}