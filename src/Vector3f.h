#pragma once
#include <math.h>
#include <iostream>
#define PI 3.14159265359f
using namespace std;
class Vector3i;
class Vector3f
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float vec[3];
		};
	};
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(Vector3i& pos);
	//normal (0,1,0)
	static Vector3f Up();
	//normal (0,-1,0)
	static Vector3f Down();
	//normal (1,0,0)
	static Vector3f Right();
	//normal (-1,0,0)
	static Vector3f Left();
	//normal (0,0,1)
	static Vector3f Forward();
	//normal (0,0,-1)
	static Vector3f Back();
	//returns scaled vector
	void Scale(float scale);
	static Vector3f Scale(Vector3f& vec, float scale);

	static Vector3f vec_mod(Vector3f vec, Vector3f divisor);
	static Vector3f vec_abs(Vector3f vec);

	static Vector3f floor(Vector3f vec);
	static Vector3f ceil(Vector3f vec);
	//return's scalar of both vectors
	float Dot(Vector3f& right);
	//return's scalar of both vectors
	static float Dot(Vector3f& left, Vector3f& right);

	//piece-wise vector multiplication e.g. left.x*right.x (looking for Vector3f.Dot?)
	void PieceMult(Vector3f& right);
	//piece-wise vector multiplication e.g. left.x*right.x (looking for Vector3f.Dot?)
	static Vector3f PieceMult(Vector3f& left, Vector3f& right);

	//standard cross product, returns vector right angled to both supplied vectors.
	Vector3f Cross(Vector3f& right);
	//standard cross product, returns vector right angled to both supplied vectors.
	static Vector3f Cross(Vector3f& left, Vector3f& right);

	void Normalize();
	//returns normalized vector
	static Vector3f Normalize(Vector3f& vec);
	//good for finding out the cos of an angle (aka take the arccos to get said angle)
	float DotNormalized(Vector3f& right);
	//good for finding out the cos of an angle (aka take the arccos to get said angle)
	static float DotNormalized(Vector3f& left, Vector3f& right);

	//simple addition
	void Add(Vector3f& right);
	//simple addition
	static Vector3f Add(Vector3f& left, Vector3f& right);

	void Sub(Vector3f& right);
	//simple subtraction
	static Vector3f Sub(Vector3f& left, Vector3f& right);

	//more "specialized" shit below
	//returns the distance between two vectors
	static float Distance(Vector3f& left, Vector3f& right);

	//returns the distance squared between two vectors (faster than Distance)
	static float DistanceSquared(Vector3f& left, Vector3f& right);

	void Negate();
	//negates the vector (literally, just negative of the components)
	static Vector3f Negate(Vector3f& vec);

	//projects a vector onto another
	static Vector3f Project(Vector3f& onto, Vector3f& from);

	//reflects based off of supplied normal vector (norm) | not tested to work, but it should?
	static Vector3f Reflect(Vector3f& initial, Vector3f& normal);

	//returns a dot product relating to the angle between the plane defined by planevec1/planevec2 and vec format: leftmost = vec1, rightmost = vec2
	static float planeDotVector(Vector3f& planeVec1, Vector3f& planeVec2, Vector3f& vec);

	float Length();
	static float Length(Vector3f& vec);

	Vector3f Copy();
	//duplicates the vector
	static Vector3f Copy(Vector3f& vec);

	~Vector3f();

	Vector3f operator*(const float& right);
	void operator*=(const float& right);

	Vector3f operator/(const float& right);
	void operator/=(const float& right);

	Vector3f operator*(const Vector3f& right);
	void operator*=(const Vector3f& right);

	Vector3f operator/(const Vector3f& right);
	void operator/=(const Vector3f& right);

	Vector3f operator+(const Vector3f& right);
	void operator+=(const Vector3f& right);

	Vector3f operator+(const float& right);
	void operator+=(const float& right);

	Vector3f operator-() const;

	Vector3f operator-(const Vector3f& right);
	void operator-=(const Vector3f& right);

	Vector3f operator-(const float& right);
	void operator-=(const float& right);

	bool operator==(const Vector3f& right);
	bool operator!=(const Vector3f& left);
};

static ostream& operator<<(ostream& os, Vector3f& vec)
{
	return os << "x:" << vec.x << "\ty:" << vec.y << "\tz:" << vec.z;
}
static Vector3f operator*(float left, Vector3f& right)
{
	return right*left;
}

static Vector3f operator+(float& left, Vector3f& right)
{
	return right + left;
}
