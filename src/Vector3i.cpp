#include "Vector3i.h"
#include "Vector3f.h"

Vector3i::Vector3i()
{
	x = y = z = 0;
}
Vector3i::Vector3i(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3i::Vector3i(Vector3f& pos)
{
	x = (int)pos.x;
	y = (int)pos.y;
	z = (int)pos.z;
}
Vector3i::~Vector3i()
{
}
string Vector3i::to_string()
{
	return string(std::to_string(x) + "." + std::to_string(y) + "." + std::to_string(z));
}
Vector3i Vector3i::Right()
{
	return Vector3i(1, 0, 0);
}
Vector3i Vector3i::Forward()
{
	return Vector3i(0, 0, 1);
}
Vector3i Vector3i::Up()
{
	return Vector3i(0, 1, 0);
}
Vector3i Vector3i::Left()
{
	return Vector3i(-1, 0, 0);
}
Vector3i Vector3i::Back()
{
	return Vector3i(0, 0, -1);
}
Vector3i Vector3i::Down()
{
	return Vector3i(0, -1, 0);
}
Vector3i Vector3i::One()
{
	return Vector3i(1, 1, 1);
}
Vector3i Vector3i::abs(Vector3i& right)
{
	return Vector3i(std::abs(right.x), std::abs(right.y), std::abs(right.z));
}
int Vector3i::sumParts(Vector3i& right)
{
	return right.x + right.y + right.z;
}
Vector3i Vector3i::preserveDiv(int divisor)
{
	//the point of this is to preserve sectors
	//if the number is negative, it needs to preserve it's negative offset, e.g. -2/10 = -1 since we were below zero.
	// -11/10 = -2 since we are 1 + 10 units from 0.
	//and if x == -divisor, then we want it to be 0, not -1.
	//since -32/32 is still be part of a chunk, and not the neighboring chunk. e.g. this is to recenter our access points into chunk co-ords and preserve offsets.
	int dx, dy, dz;
	if (x < 0)
		dx = (x+1) / divisor -1;
	else
		dx = x / divisor;
	if (y < 0)
		dy = (y+1) / divisor -1;
	else
		dy = y / divisor;
	if (z < 0)
		dz = (z+1) / divisor-1;
	else
		dz = z / divisor;
	return Vector3i(dx,dy,dz);
}
Vector3i Vector3i::preserveOffset(int divisor)
{
	//this is similar to the above block of code, in that fucking accessing negative indexes of a chunk is questionable at best.
	//if we are accessing world co-ords x:0 , y: -1, z :0
	//we want to get the block co-ords of x:0, y: -1 +32, x:0
	//e.g. x:-32 becomes x:0 so we can access the first slot of the array.
	int dx, dy, dz;
	if (x < 0)
	{
		dx = x % divisor;
		dx += dx != 0 ? divisor : 0;
	}
	else
	{
		dx = x %divisor;
	}
	if (y < 0)
	{
		dy = y % divisor;
		dy += dy != 0 ? divisor : 0;
	}
	else
	{
		dy = y %divisor;
	}
	if (z < 0)
	{
		dz = z %divisor;
		dz += dz != 0 ? divisor : 0;
	}
	else
	{
		dz = z %divisor;
	}
	return Vector3i(dx,dy,dz);
}
bool Vector3i::operator==(Vector3i& right)
{
	if (x == right.x && y == right.y && z == right.z)
	{
		return true;
	}
	return false;
}
bool Vector3i::operator!=(Vector3i& right)
{
	return !(*this == right);
}
Vector3i Vector3i::operator-() const
{
	return Vector3i(-x, -y, -z);
}
Vector3i Vector3i::operator+(Vector3i& right)
{
	return Vector3i(x + right.x, y + right.y, z + right.z);
}
void Vector3i::operator+=(Vector3i& right)
{
	*this = *this + right;
}
Vector3i Vector3i::operator-(Vector3i& right)
{
	return *this + (-right);
}
void Vector3i::operator-=(Vector3i& right)
{
	*this = *this - right;
}
Vector3i Vector3i::operator*(Vector3i& right)
{
	return Vector3i(x*right.x, y*right.y, z*right.z);
}
void Vector3i::operator*=(Vector3i& right)
{
	*this = *this * right;
}
Vector3i Vector3i::operator*(int& right)
{
	return Vector3i(x*right, y*right, z*right);
}
void Vector3i::operator*=(int& right)
{
	*this = *this*right;
}
Vector3i Vector3i::operator*(const int& right)
{
	return Vector3i(x*right, y*right, z*right);
}
void Vector3i::operator*=(const int& right)
{
	*this = *this*right;
}
Vector3i Vector3i::operator/(Vector3i& right)
{
	return Vector3i(x / right.x, y / right.y, z / right.z);
}
void Vector3i::operator/=(Vector3i& right)
{
	*this = *this / right;
}
Vector3i Vector3i::operator/(int& right)
{
	return Vector3i(x / right, y / right, z / right);
}
void Vector3i::operator/=(int& right)
{
	*this = *this / right;
}
Vector3i Vector3i::operator/(unsigned short& right)
{
	return Vector3i(x / right, y / right, z / right);
}
void Vector3i::operator/=(unsigned short& right)
{
	*this = *this / right;
}
Vector3i Vector3i::operator/(const unsigned short& right)
{
	return Vector3i(x / right, y / right, z / right);
}
void Vector3i::operator/=(const unsigned short& right)
{
	*this = *this / right;
}
Vector3i Vector3i::operator+(int& right)
{
	return Vector3i(x + right, y + right, z + right);
}
void Vector3i::operator+=(int& right)
{
	*this = *this + right;
}
Vector3i Vector3i::operator-(int& right)
{
	return Vector3i(x - right, y - right, z - right);
}
void Vector3i::operator-=(int& right)
{
	*this = *this - right;
}
Vector3i Vector3i::operator%(int& right)
{
	return Vector3i(x%right, y%right, z%right);
}
void Vector3i::operator%=(int& right)
{
	x %= right;
	y %= right;
	z %= right;
}
Vector3i Vector3i::operator%(unsigned short& right)
{
	return Vector3i(x%right, y%right, z%right);
}
void Vector3i::operator%=(unsigned short& right)
{
	x %= right;
	y %= right;
	z %= right;
}
Vector3i Vector3i::operator%(const unsigned short& right)
{
	return Vector3i(x%right, y%right, z%right);
}
void Vector3i::operator%=(const unsigned short& right)
{
	x %= right;
	y %= right;
	z %= right;
}
Vector3i Vector3i::operator%(Vector3i& right)
{
	return Vector3i(x%right.x, y%right.y, z%right.z);
}
void Vector3i::operator%=(Vector3i& right)
{
	x %= right.x;
	y %= right.y;
	z %= right.z;
}
Vector3i Vector3i::operator>>(int amount)
{
	return Vector3i(x >> amount, y >> amount, z >> amount);
}
void Vector3i::operator>>=(int amount)
{
	x >>= amount;
	y >>= amount;
	z >>= amount;
}
Vector3i Vector3i::operator>>(Vector3i& amount)
{
	return Vector3i(x >> amount.x, y >> amount.y, z >> amount.z);
}
void Vector3i::operator>>=(Vector3i& amount)
{
	x >>= amount.x;
	y >>= amount.y;
	z >>= amount.z;
}
Vector3i Vector3i::operator<<(int amount)
{
	return Vector3i(x << amount, y << amount, z << amount);
}
void Vector3i::operator<<=(int amount)
{
	x <<= amount;
	y <<= amount;
	z <<= amount;
}
Vector3i Vector3i::operator<<(Vector3i& amount)
{
	return Vector3i(x << amount.x, y << amount.y, z << amount.z);
}
void Vector3i::operator<<=(Vector3i& amount)
{
	x <<= amount.x;
	y <<= amount.y;
	z <<= amount.z;
}
Vector3i Vector3i::operator&(int mask)
{
	return Vector3i(x&mask, y&mask, z&mask);
}
void Vector3i::operator&=(int mask)
{
	x &= mask;
	y &= mask;
	z &= mask;
}
Vector3i Vector3i::operator&(Vector3i& mask)
{
	return Vector3i(x&mask.x, y&mask.y, z&mask.z);
}
void Vector3i::operator&=(Vector3i& mask)
{
	x &= mask.x;
	y &= mask.y;
	z &= mask.z;
}
Vector3i Vector3i::operator|(int mask)
{
	return Vector3i(x | mask, y | mask, z | mask);
}
void Vector3i::operator|=(int mask)
{
	x |= mask;
	y |= mask;
	z |= mask;
}
Vector3i Vector3i::operator|(Vector3i& mask)
{
	return Vector3i(x | mask.x, y | mask.y, z | mask.z);
}
void Vector3i::operator|=(Vector3i& mask)
{
	x |= mask.x;
	y |= mask.y;
	z |= mask.z;
}
Vector3i Vector3i::operator^(int mask)
{
	return Vector3i(x^mask, y^mask, z^mask);
}
void Vector3i::operator^=(int mask)
{
	x ^= mask;
	y ^= mask;
	z ^= mask;
}
Vector3i Vector3i::operator^(Vector3i& mask)
{
	return Vector3i(x^mask.x, y^mask.y, z^mask.z);
}
void Vector3i::operator^=(Vector3i& mask)
{
	x ^= mask.x;
	y ^= mask.y;
	z ^= mask.z;
}
Vector3i Vector3i::operator~() const
{
	return Vector3i(~x, ~y, ~z);
}