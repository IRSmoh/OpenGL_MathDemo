#include "Vector3f.h"
#include "Vector3i.h"
#pragma region vector3f_methods
Vector3f::Vector3f()
{
	x = y = z = 0;
}
Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3f::Vector3f(Vector3i& pos)
{
	x = (float)pos.x;
	y = (float)pos.y;
	z = (float)pos.z;
}
Vector3f Vector3f::Up()
{
	return Vector3f(0, 1, 0);
}
Vector3f Vector3f::Down()
{
	return Vector3f(0, -1, 0);
}
Vector3f Vector3f::Right()
{
	return Vector3f(1, 0, 0);
}
Vector3f Vector3f::Left()
{
	return Vector3f(-1, 0, 0);
}
Vector3f Vector3f::Forward()
{
	return Vector3f(0, 0, 1);
}
Vector3f Vector3f::Back()
{
	return Vector3f(0, 0, -1);
}
Vector3f Vector3f::vec_mod(Vector3f vec, Vector3f divisor)
{
	return Vector3f(fmod(vec.x, divisor.x), fmod(vec.y, divisor.y), fmod(vec.z, divisor.z));
}
Vector3f Vector3f::vec_abs(Vector3f vec)
{
	return Vector3f(abs(vec.x), abs(vec.y), abs(vec.z));
}
Vector3f Vector3f::floor(Vector3f vec)
{
	return Vector3f(floorf(vec.x), floorf(vec.y), floorf(vec.z));
}
Vector3f Vector3f::ceil(Vector3f vec)
{
	return Vector3f(ceilf(vec.x), ceilf(vec.y), ceilf(vec.z));
}
void Vector3f::Scale(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}
Vector3f Vector3f::Scale(Vector3f& vec, float scale)
{
	return Vector3f(vec.x*scale, vec.y*scale, vec.z*scale);
}
float Vector3f::Dot(Vector3f& right)
{
	return x*right.x + y*right.y + z*right.z;
}
float Vector3f::Dot(Vector3f& left, Vector3f& right)
{
	return left.x*right.x + left.y*right.y + left.z*right.z;
}
void Vector3f::PieceMult(Vector3f& right)
{
	x *= right.x;
	y *= right.y;
	z *= right.z;
}
Vector3f Vector3f::PieceMult(Vector3f& left, Vector3f& right)
{
	return Vector3f(left.x*right.x, left.y*right.y, left.z*right.z);
}
Vector3f Vector3f::Cross(Vector3f& right)
{
	return Vector3f(y*right.z - z*right.y, z*right.x - x*right.z, x*right.y - y*right.x);
}
Vector3f Vector3f::Cross(Vector3f& left, Vector3f& right)
{
	//(l.y*r.z - l.z*r.y)i + (l.z*r.x - l.x*r.z)j + (l.x*r.y - l.y*r.x)k
	return Vector3f(left.y*right.z - left.z*right.y, left.z*right.x - left.x*right.z, left.x*right.y - left.y*right.x);
}
void Vector3f::Normalize()
{
	float denom = sqrtf(x*x + y*y + z*z);
	if (denom > 0.000001f)
	{
		x /= denom;
		y /= denom;
		z /= denom;
	}
}
Vector3f Vector3f::Normalize(Vector3f& vec)
{
	float denom = sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	if (denom > 0.000001f)
	{
		return Vector3f(vec.x / denom, vec.y / denom, vec.z / denom);
	}
	return vec;
}
float Vector3f::DotNormalized(Vector3f& right)
{
	return Dot(Normalize(*this), Normalize(right));
}
float Vector3f::DotNormalized(Vector3f& left, Vector3f& right)
{
	return Dot(Normalize(left), Normalize(right));
}
void Vector3f::Add(Vector3f& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
}
Vector3f Vector3f::Add(Vector3f& left, Vector3f& right)
{
	return Vector3f(left.x + right.x, left.y + right.y, left.z + right.z);
}
void Vector3f::Sub(Vector3f& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
}
Vector3f Vector3f::Sub(Vector3f& left, Vector3f& right)
{
	return Vector3f(left.x - right.x, left.y - right.y, left.z - right.z);
}
float Vector3f::Distance(Vector3f& left, Vector3f& right)
{
	return sqrt(left.x*right.x+ left.y*right.y + left.z*right.z);
}
float Vector3f::DistanceSquared(Vector3f& left, Vector3f& right)
{
	return left.x*right.x + left.y*right.y + left.z*right.z;
}
void Vector3f::Negate()
{
	x = -x;
	y = -y;
	z = -z;
}
Vector3f Vector3f::Negate(Vector3f& vec)
{
	return Vector3f(-vec.x, -vec.y, -vec.z);
}
Vector3f Vector3f::Copy()
{
	return Vector3f(x, y, z);
}
Vector3f Vector3f::Copy(Vector3f& vec)
{
	return Vector3f(vec.x, vec.y, vec.z);
}
Vector3f Vector3f::Project(Vector3f& onto, Vector3f& from)
{
	Vector3f fromNorm = Normalize(from);
	return fromNorm*Dot(onto, fromNorm);
}
Vector3f Vector3f::Reflect(Vector3f& initial, Vector3f& normal)
{
	return (normal*Dot(initial, normal))*-2 + initial;
}
float Vector3f::planeDotVector(Vector3f& planeVec1, Vector3f& planeVec2, Vector3f& vec)
{
	Vector3f planeNormal = Cross(planeVec1, planeVec2);
	float normalAngle = Dot(planeNormal, vec);
	if (normalAngle > 0)
	{
		//positive angle
		return cos(PI / 2 - acos(normalAngle));
	}
	else
	{
		//negative angle
		return cos(PI / 2 + acos(normalAngle));
	}
	//angle is PI/2 thus the dot = 1
	return 1;
}
float Vector3f::Length()
{
	return sqrt(x*x + y*y + z*z);
}
float Vector3f::Length(Vector3f& vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}
Vector3f::~Vector3f()
{

}
#pragma endregion vector3f_methods

///
//vector operators
///
#pragma region vector3f_operators
Vector3f Vector3f::operator*(const Vector3f& right)
{
	return Vector3f(this->x*right.x, this->y*right.y, this->z*right.z);
}
void Vector3f::operator*=(const Vector3f& right)
{
	x *= right.x;
	y *= right.y;
	z *= right.z;
}
Vector3f Vector3f::operator/(const Vector3f& right)
{
	return Vector3f(this->x / right.x, this->y / right.y, this->z / right.z);
}
void Vector3f::operator/=(const Vector3f& right)
{
	x /= right.x;
	y /= right.y;
	z /= right.z;
}
Vector3f Vector3f::operator*(const float& right)
{
	return Vector3f(this->x*right, this->y*right, this->z*right);
}
void Vector3f::operator*= (const float& right)
{
	x *= right;
	y *= right;
	z *= right;
}
Vector3f Vector3f::operator/(const float& right)
{
	return Vector3f(this->x / right, this->y / right, this->z / right);
}
void Vector3f::operator/=(const float& right)
{
	x /= right;
	y /= right;
	z /= right;
}
Vector3f Vector3f::operator+(const Vector3f& right)
{
	return Vector3f(this->x + right.x, this->y + right.y, this->z + right.z);
}
void Vector3f::operator+=(const Vector3f& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
}
Vector3f Vector3f::operator-() const
{
	return Vector3f(-this->x, -this->y, -this->z);
}
Vector3f Vector3f::operator-(const Vector3f& right)
{
	return *this + (-right);
}
void Vector3f::operator-=(const Vector3f& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
}
bool Vector3f::operator==(const Vector3f& right)
{
	if (this->x == right.x && this->y == right.y && this->z == right.z)
	{
		return true;
	}
	return false;
}
bool Vector3f::operator!=(const Vector3f& right)
{
	//is it a lot faster? probably not in the slightest, but I felt like it.
	if (x != right.x || y != right.y || z != right.z)
	{
		return true;
	}
	return false;
}
#pragma endregion vector3f_operators
