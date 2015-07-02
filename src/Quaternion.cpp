#include "Quaternion.h"
#pragma region quaternion_methods

Quaternion::Quaternion()
{
	x = y = z = 0;
	w = 1;
}
Quaternion::Quaternion(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}
Quaternion::Quaternion(Vector3f rotations)
{
	this->x = rotations.x;
	this->y = rotations.y;
	this->z = rotations.z;
	this->w = 1;
}
Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Quaternion::~Quaternion()
{

}
void Quaternion::Conjugate()
{
	x = -x;
	y = -y;
	z = -z;
}
Quaternion Quaternion::Conjugate(Quaternion& quat)
{
	return Quaternion(-quat.x, -quat.y, -quat.z, quat.w);
}
float Quaternion::Magnitude()
{
	float l = w*w + z*z + y*y + x*x;
	//if its close enough to one, it may as well be.
	if (l < 1.0000001f)
	{
		return 1;
	}
	return sqrt(w*w + z*z + y*y + x*x);
}
float Quaternion::Magnitude(Quaternion& quat)
{
	return quat.Magnitude();
}
Quaternion Quaternion::fromAxis(Vector3f axis, float angle)
{
	//tested many times, it works. don't fuck with it.
	float sinAngle = sin(angle / 2);
	Vector3f normalized = Vector3f::Normalize(axis);
	Quaternion quaternion(normalized.x*sinAngle, normalized.y*sinAngle, normalized.z*sinAngle, cos(angle / 2));
	return Normalize(quaternion);
}
Matrix4x4 Quaternion::ToMatrix()
{
	//tested many times, it works. don't fuck with it.
	Matrix4x4 matrix;

	matrix.m11 = 1 - 2 * y*y - 2 * z*z;
	matrix.m12 = 2 * x*y - 2 * z*w;
	matrix.m13 = 2 * x*z + 2 * y*w;

	matrix.m21 = 2 * x*y + 2 * z*w;
	matrix.m22 = 1 - 2 * x*x - 2 * z*z;
	matrix.m23 = 2 * y*z - 2 * x*w;

	matrix.m31 = 2 * x*z - 2 * y*w;
	matrix.m32 = 2 * y*z + 2 * x*w;
	matrix.m33 = 1 - 2 * x*x - 2 * y*y;

	matrix.m44 = 1.0f;
	return matrix;
}
Matrix4x4 Quaternion::ToMatrix(Quaternion rotation)
{
	return rotation.ToMatrix();
}
void Quaternion::Normalize()
{
	float magnitude = Magnitude();
	//if its 1, its normalized.
	if (magnitude == 1)
	{
		return;
	}
	//if its not go ahead and do math
	x /= magnitude;
	y /= magnitude; 
	z /= magnitude;
	w /= magnitude;
}
Quaternion Quaternion::Normalize(Quaternion quaternion)
{
	float magnitude = Magnitude(quaternion);
	//if its 1, its normalized.
	if (magnitude == 1)
	{
		return quaternion;
	}
	//if its not go ahead and do math
	Quaternion result(quaternion.x / magnitude, quaternion.y / magnitude, quaternion.z / magnitude, quaternion.w / magnitude);
	return result;
}
Quaternion Quaternion::Mult(Quaternion left, Quaternion right)
{
	float x = left.x*right.w + left.y*right.z - left.z*right.y + left.w*right.x;
	float y = -left.x*right.z + left.y*right.w + left.z*right.x + left.w*right.y;
	float z = left.x*right.y - left.y*right.x + left.z*right.w + left.w*right.z;
	float w = -left.x*right.x - left.y*right.y - left.z*right.z + left.w*right.w;
	return Normalize(Quaternion(x,y,z,w));
}
Vector3f Quaternion::Mult(Quaternion left, Vector3f right)
{
	Quaternion quatVec(right.x, right.y, right.z, 0);
	Quaternion resultQuat = MultNoNormal(left, MultNoNormal(quatVec, -left));
	return Vector3f(resultQuat.x, resultQuat.y, resultQuat.z);
}
Quaternion Quaternion::MultNoNormal(Quaternion& left, Quaternion& right)
{
	float x = left.x*right.w + left.y*right.z - left.z*right.y + left.w*right.x;
	float y = -left.x*right.z + left.y*right.w + left.z*right.x + left.w*right.y;
	float z = left.x*right.y - left.y*right.x + left.z*right.w + left.w*right.z;
	float w = -left.x*right.x - left.y*right.y - left.z*right.z + left.w*right.w;
	return Quaternion(x, y, z, w);
}
void Quaternion::Inverse()
{
	Conjugate();
}
Quaternion Quaternion::Inverse(Quaternion quaternion)
{
	return Conjugate(quaternion);
}
Quaternion Quaternion::Slerp(Quaternion start, Quaternion end, float alpha)
{
	//I suspect this is broken, most else with quaternions was.....
	float startWeight, endWeight, difference;
	difference = start.x*end.x + start.y*end.y + start.z*end.z + start.w*end.w;
	if ((1.0f - fabs(difference) > SLERP_SWITCH_THRESHOLD))
	{
		float theta, oneOverSinTheta;
		theta = acos(fabs(difference));
		oneOverSinTheta = 1.0f / sin(theta);
		startWeight = sin(theta*(1.0f - alpha))*oneOverSinTheta;
		endWeight = sin(theta*alpha)*oneOverSinTheta;
		if (difference < 0.0f)
		{
			startWeight = -startWeight;
		}
	}
	else
	{
		startWeight = 1.0f - alpha;
		endWeight = alpha;
	}
	Quaternion result = Quaternion(start.x*startWeight + end.x*endWeight, start.y*startWeight + end.y*endWeight, start.z*startWeight + end.z*endWeight, start.w*startWeight + end.w*endWeight);
	return Normalize(result);
}
float Quaternion::Dot(Quaternion right)
{
	return x*right.x + y*right.y + z*right.z + w*right.w;
}
float Quaternion::Dot(Quaternion left, Quaternion right)
{
	return left.Dot(right);
}
#pragma endregion quaternion_methods

//quaternion operators
#pragma region quaternion_operators
Quaternion Quaternion::operator*(Quaternion& right)
{
	return Mult(*this, right);
}
void Quaternion::operator*=(Quaternion& right)
{
	*this = right*(*this);
}
Quaternion Quaternion::operator*(float right)
{
	return Quaternion(x*right, y*right, z*right, w*right);
}
Vector3f Quaternion::operator*(Vector3f& right)
{
	return Mult(*this, right);
}
Quaternion Quaternion::operator-() const
{
	return Inverse(*this);
}
#pragma endregion quaternion_operators