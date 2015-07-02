#pragma once
#include <iostream>
#include <string>
using namespace std;
class Vector3f;
class Vector3i
{
public:
	int x;
	int y;
	int z;
	Vector3i();
	Vector3i(int x, int y, int z);
	Vector3i(Vector3f& pos);
	~Vector3i();
	//gives a string in the format "X:x Y:y Z:z"
	string to_string();
	//(1,0,0)
	static Vector3i Right();
	//(0,0,1)
	static Vector3i Forward();
	//(0,1,0)
	static Vector3i Up();
	//(-1,0,0)
	static Vector3i Left();
	//(0,0,-1)
	static Vector3i Back();
	//(0,-1,0)
	static Vector3i Down();
	//(1,1,1)
	static Vector3i One();
	static Vector3i abs(Vector3i& right);
	static int sumParts(Vector3i& right);
	//rounds down if x/y/z >0 rounds up if x/y/z <0 (e.g. 0.1->0 & -0.1->-1 & -1 ->-1)
	Vector3i preserveDiv(int divisor);
	//similar to % except if the number goes negative, it adds it in
	Vector3i preserveOffset(int divisor);

	bool operator==(Vector3i& right);
	bool operator!=(Vector3i& right);
	Vector3i operator-() const;
	Vector3i operator+(Vector3i& right);
	void operator+=(Vector3i& right);
	Vector3i operator-(Vector3i& right);
	void operator-=(Vector3i& right);
	Vector3i operator*(Vector3i& right);
	void operator*=(Vector3i& right);
	Vector3i operator*(int& right);
	void operator*=(int& right);
	Vector3i operator*(const int& right);
	void operator*=(const int& right);
	Vector3i operator+(int& right);
	void operator+=(int& right);
	Vector3i operator-(int& right);
	void operator-=(int& right);
	Vector3i operator/(Vector3i& right);
	void operator/=(Vector3i& right);
	Vector3i operator/(int& right);
	void operator/=(int& right);
	Vector3i operator/(unsigned short& right);
	void operator/=(unsigned short& right);
	Vector3i operator/(const unsigned short& right);
	void operator/=(const unsigned short& right);
	Vector3i operator%(int& right);
	void operator%=(int& right);
	Vector3i operator%(unsigned short& right);
	void operator%=(unsigned short& right);
	Vector3i operator%(const unsigned short& right);
	void operator%=(const unsigned short& right);
	Vector3i operator%(Vector3i& right);
	void operator%=(Vector3i& right);

	//bit twiddling operators
	Vector3i operator>>(int amount);
	void operator>>=(int amount);
	Vector3i operator>>(Vector3i& amount);
	void operator>>=(Vector3i& amount);
	Vector3i operator<<(int amount);
	void operator<<=(int amount);
	Vector3i operator<<(Vector3i& amount);
	void operator<<=(Vector3i& amount);
	Vector3i operator&(int mask);
	void operator&=(int mask);
	Vector3i operator&(Vector3i& mask);
	void operator&=(Vector3i& mask);
	Vector3i operator|(int mask);
	void operator|=(int mask);
	Vector3i operator|(Vector3i& mask);
	void operator|=(Vector3i& mask);
	Vector3i operator^(int mask);
	void operator^=(int mask);
	Vector3i operator^(Vector3i& mask);
	void operator^=(Vector3i& mask);
	Vector3i operator~() const;
};

static ostream& operator<<(ostream& os, Vector3i& right)
{
	return os << "x:" << right.x << "\ty:" << right.y << "\tz:" << right.z;
}
static Vector3i operator*(int& left, Vector3i& right)
{
	return right*left;
}
static Vector3i operator+(int& left, Vector3i& right)
{
	return right + left;
}
