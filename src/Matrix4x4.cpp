#include "Matrix4x4.h"
#pragma region matrix4x4_methods
Matrix4x4::Matrix4x4() : m11(1), m22(1), m33(1), m44(1),
m12(0), m13(0), m14(0), m21(0), m23(0), m24(0), m31(0), m32(0), m34(0), m41(0), m42(0), m43(0)
{
}
Matrix4x4::Matrix4x4(float(&mat)[16])
{
	memcpy(this->mat, mat, sizeof(Matrix4x4));
}
Matrix4x4::Matrix4x4(Vector3f diagonal) : m11(diagonal.x), m22(diagonal.y), m33(diagonal.z), m44(1),
m12(0), m13(0), m14(0), m21(0), m23(0), m24(0), m31(0), m32(0), m34(0), m41(0), m42(0), m43(0)
{
}
Matrix4x4::Matrix4x4(float _m11, float _m12, float  _m13, float _m14,
	float _m21, float _m22, float _m23, float _m24,
	float _m31, float _m32, float _m33, float _m34,
	float _m41, float _m42, float _m43, float _m44) :
	m11(_m11), m12(_m12), m13(_m13), m14(_m14),
	m21(_m21), m22(_m22), m23(_m23), m24(_m24),
	m31(_m31), m32(_m32), m33(_m33), m34(_m34),
	m41(_m41), m42(_m42), m43(_m43), m44(_m44)
{
}
Matrix4x4::~Matrix4x4()
{
}
Matrix4x4 Matrix4x4::Transpose(Matrix4x4& right)
{
	return Matrix4x4(right.m11, right.m21, right.m31, right.m41,
		right.m12, right.m22, right.m32, right.m42,
		right.m13, right.m23, right.m33, right.m43,
		right.m14, right.m24, right.m34, right.m44);
}
Matrix4x4 Matrix4x4::Transpose()
{
	return Matrix4x4::Transpose(*this);
}
float Matrix4x4::Determinate(Matrix4x4& right)
{
	return right.Determinate();
}
float Matrix4x4::Determinate()
{
	//sorry, this is stupidly long
	//heres some mild documentation: http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
	float det = m11*m22*m33*m44 + m11*m23*m34*m42 + m11*m24*m32*m43 +
		m12*m21*m34*m43 + m12*m23*m31*m44 + m12*m24*m33*m41 +
		m13*m21*m32*m44 + m13*m22*m34*m41 + m13*m24*m31*m42 +
		m14*m21*m33*m42 + m14*m22*m31*m43 + m14*m23*m32*m41 -
		m11*m22*m34*m43 - m11*m23*m32*m44 - m11*m24*m33*m42 -
		m12*m21*m33*m44 - m12*m23*m34*m41 - m12*m24*m31*m43 -
		m13*m21*m34*m42 - m13*m22*m31*m44 - m13*m24*m32*m41 -
		m14*m21*m32*m43 - m14*m22*m33*m41 - m14*m23*m31*m42;
	return det;
}
Matrix4x4 Matrix4x4::Inverse(Matrix4x4& right)
{
	return right.InverseTransform() * (1 / right.Determinate());
}
Matrix4x4 Matrix4x4::Inverse()
{
	return InverseTransform()*(1 / Determinate());
}
Matrix4x4 Matrix4x4::InverseTransform(Matrix4x4& right)
{
	return right.InverseTransform();
}
Matrix4x4 Matrix4x4::InverseTransform()
{
	Matrix4x4 inverse;
	inverse.m11 = m22*m33*m44 + m23*m34*m42 + m24*m32*m43 - m22*m34*m43 - m23*m32*m44 - m24*m33*m42;
	inverse.m12 = m12*m34*m43 + m13*m32*m44 + m14*m33*m42 - m12*m33*m44 - m13*m34*m42 - m14*m32*m43;
	inverse.m13 = m12*m23*m44 + m13*m24*m42 + m14*m22*m43 - m12*m24*m43 - m13*m22*m44 - m14*m23*m42;
	inverse.m14 = m12*m24*m33 + m13*m22*m34 + m14*m23*m32 - m12*m23*m34 - m13*m24*m32 - m14*m22*m33;

	inverse.m21 = m21*m34*m43 + m23*m31*m44 + m24*m33*m41 - m21*m33*m44 - m23*m34*m41 - m24*m31*m43;
	inverse.m22 = m11*m33*m44 + m13*m34*m41 + m14*m31*m43 - m11*m34*m43 - m13*m31*m44 - m14*m33*m41;
	inverse.m23 = m11*m24*m43 + m13*m21*m44 + m14*m23*m41 - m11*m23*m44 - m13*m24*m41 - m14*m21*m43;
	inverse.m24 = m11*m23*m34 + m13*m24*m31 + m14*m21*m33 - m11*m24*m33 - m13*m21*m34 - m14*m23*m31;

	inverse.m31 = m21*m32*m44 + m22*m34*m41 + m24*m31*m42 - m21*m34*m42 - m22*m31*m44 - m24*m32*m41;
	inverse.m32 = m11*m34*m42 + m12*m31*m44 + m14*m32*m41 - m11*m32*m44 - m12*m34*m41 - m14*m31*m42;
	inverse.m33 = m11*m22*m44 + m12*m24*m41 + m14*m21*m42 - m11*m24*m42 - m12*m21*m44 - m14*m22*m41;
	inverse.m34 = m11*m24*m32 + m12*m21*m34 + m14*m22*m31 - m11*m22*m34 - m12*m24*m31 - m14*m21*m32;

	inverse.m41 = m21*m33*m42 + m22*m31*m43 + m23*m32*m41 - m21*m32*m43 - m22*m33*m41 - m23*m31*m42;
	inverse.m42 = m11*m32*m43 + m12*m33*m41 + m13*m31*m42 - m11*m33*m42 - m12*m31*m43 - m13*m32*m41;
	inverse.m43 = m11*m23*m42 + m12*m21*m43 + m13*m22*m41 - m11*m22*m43 - m12*m23*m41 - m13*m21*m42;
	inverse.m44 = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31;
	return inverse;
}
Vector3f Matrix4x4::ExtractScale(Matrix4x4& right)
{
	return right.ExtractScale();
}
Vector3f Matrix4x4::ExtractScale()
{
	return Vector3f(Vector3f(m11, m21, m31).Length(), Vector3f(m12, m22, m32).Length(), Vector3f(m13, m23, m33).Length());
}
Vector3f Matrix4x4::ExtractInverseScale(Matrix4x4& right)
{
	return right.ExtractInverseScale();
}
Vector3f Matrix4x4::ExtractInverseScale()
{
	return Vector3f(1/Vector3f(m11, m21, m31).Length(), 1/Vector3f(m12, m22, m32).Length(), 1/Vector3f(m13, m23, m33).Length());
}
void Matrix4x4::TranslateBy(Vector3f translate)
{
	m14 += translate.x;
	m24 += translate.y;
	m34 += translate.z;
}
Matrix4x4 Matrix4x4::makeZero()
{
	Matrix4x4 matrix;
	matrix.m11 = matrix.m22 = matrix.m33 = matrix.m44 = 0;
	return matrix;
}
Matrix4x4 Matrix4x4::makeTranslate(Vector3f translate)
{
	Matrix4x4 matrix;
	matrix.m14 = translate.x;
	matrix.m24 = translate.y;
	matrix.m34 = translate.z;
	return matrix;
}
Matrix4x4 Matrix4x4::makeRotationX(float rotX)
{
	Matrix4x4 matrix;
	matrix.m22 = matrix.m33 = cos(rotX);
	matrix.m32 = sin(rotX);
	matrix.m23 = -matrix.m32;
	return matrix;
}
Matrix4x4 Matrix4x4::makeRotationY(float rotY)
{
	Matrix4x4 matrix;
	matrix.m11 = matrix.m33 = cos(rotY);
	matrix.m13 = sin(rotY);
	matrix.m31 = -matrix.m13;
	return matrix;
}
Matrix4x4 Matrix4x4::makeRotationZ(float rotZ)
{
	Matrix4x4 matrix;
	matrix.m11 = matrix.m22 = cos(rotZ);
	matrix.m21 = sin(rotZ);
	matrix.m12 = -matrix.m21;
	return matrix;
}
Matrix4x4 Matrix4x4::makePerspective(float fov, float aspect, float nearPlane, float farPlane)
{
	Matrix4x4 matrix;
	float f = 1.0f / tan(fov*PI / 360.0f);
	matrix.m11 = f / aspect;
	matrix.m22 = f;
	matrix.m33 = (farPlane + nearPlane) / (nearPlane - farPlane);
	matrix.m43 = -1.0f;
	matrix.m34 = (2 * farPlane*nearPlane) / (nearPlane - farPlane);
	return matrix;
}
void Matrix4x4::LookAt(Vector3f& position, Vector3f& lookAtPoint, Vector3f& up, Matrix4x4& out)
{
	Vector3f z = Vector3f::Normalize(lookAtPoint - position);
	Vector3f x = Vector3f::Normalize(Vector3f::Cross(up, z));
	Vector3f y = Vector3f::Cross(z, x);
	out.m11 = x.x;
	out.m21 = x.y;
	out.m31 = x.z;

	out.m12 = y.x;
	out.m22 = y.y;
	out.m32 = y.z;

	out.m13 = z.x;
	out.m23 = z.y;
	out.m33 = z.z;
}
Matrix4x4 Matrix4x4::M4x4_SSE(Matrix4x4& right)
{
	Matrix4x4 matrix;
	__m128 row1 = _mm_loadu_ps(&right[0]);
	__m128 row2 = _mm_loadu_ps(&right[4]);
	__m128 row3 = _mm_loadu_ps(&right[8]);
	__m128 row4 = _mm_loadu_ps(&right[12]);
	for (int i = 0; i<4; i++) {
		__m128 brod1 = _mm_set1_ps(mat[4 * i + 0]);
		__m128 brod2 = _mm_set1_ps(mat[4 * i + 1]);
		__m128 brod3 = _mm_set1_ps(mat[4 * i + 2]);
		__m128 brod4 = _mm_set1_ps(mat[4 * i + 3]);
		__m128 row = _mm_add_ps(
			_mm_add_ps(
			_mm_mul_ps(brod1, row1),
			_mm_mul_ps(brod2, row2)),
			_mm_add_ps(
			_mm_mul_ps(brod3, row3),
			_mm_mul_ps(brod4, row4)));
		_mm_storeu_ps(&matrix[4 * i], row);
	}
	return matrix;
}
Matrix4x4 Matrix4x4::M4x4_SSE(Matrix4x4& left, Matrix4x4& right)
{
	Matrix4x4 matrix;
	__m128 row1 = _mm_loadu_ps(&right[0]);
	__m128 row2 = _mm_loadu_ps(&right[4]);
	__m128 row3 = _mm_loadu_ps(&right[8]);
	__m128 row4 = _mm_loadu_ps(&right[12]);
	for (int i = 0; i<4; i++) {
		__m128 brod1 = _mm_set1_ps(left[4 * i + 0]);
		__m128 brod2 = _mm_set1_ps(left[4 * i + 1]);
		__m128 brod3 = _mm_set1_ps(left[4 * i + 2]);
		__m128 brod4 = _mm_set1_ps(left[4 * i + 3]);
		__m128 row = _mm_add_ps(
			_mm_add_ps(
			_mm_mul_ps(brod1, row1),
			_mm_mul_ps(brod2, row2)),
			_mm_add_ps(
			_mm_mul_ps(brod3, row3),
			_mm_mul_ps(brod4, row4)));
		_mm_storeu_ps(&matrix[4 * i], row);
	}
	return matrix;
}
void Matrix4x4::M4x4_SSE(Matrix4x4& left, Matrix4x4& right, Matrix4x4& out)
{
	__m128 row1 = _mm_loadu_ps(&right[0]);
	__m128 row2 = _mm_loadu_ps(&right[4]);
	__m128 row3 = _mm_loadu_ps(&right[8]);
	__m128 row4 = _mm_loadu_ps(&right[12]);
	for (int i = 0; i<4; i++) {
		__m128 brod1 = _mm_set1_ps(left[4 * i + 0]);
		__m128 brod2 = _mm_set1_ps(left[4 * i + 1]);
		__m128 brod3 = _mm_set1_ps(left[4 * i + 2]);
		__m128 brod4 = _mm_set1_ps(left[4 * i + 3]);
		__m128 row = _mm_add_ps(
			_mm_add_ps(
			_mm_mul_ps(brod1, row1),
			_mm_mul_ps(brod2, row2)),
			_mm_add_ps(
			_mm_mul_ps(brod3, row3),
			_mm_mul_ps(brod4, row4)));
		_mm_storeu_ps(&out[4 * i], row);
	}
}
void Matrix4x4::M4x4_SSE_Fast(float* right, float* out)
{
	__m128 row1 = _mm_loadu_ps(&right[0]);
	__m128 row2 = _mm_loadu_ps(&right[4]);
	__m128 row3 = _mm_loadu_ps(&right[8]);
	__m128 row4 = _mm_loadu_ps(&right[12]);
	for (int i = 0; i<4; i++) {
		__m128 brod1 = _mm_set1_ps(mat[4 * i + 0]);
		__m128 brod2 = _mm_set1_ps(mat[4 * i + 1]);
		__m128 brod3 = _mm_set1_ps(mat[4 * i + 2]);
		__m128 brod4 = _mm_set1_ps(mat[4 * i + 3]);
		__m128 row = _mm_add_ps(
			_mm_add_ps(
			_mm_mul_ps(brod1, row1),
			_mm_mul_ps(brod2, row2)),
			_mm_add_ps(
			_mm_mul_ps(brod3, row3),
			_mm_mul_ps(brod4, row4)));
		_mm_storeu_ps(&out[4 * i], row);
	}
}
void Matrix4x4::M4x4_SSE_Fast(float* left, float* right, float* out)
{
	__m128 row1 = _mm_loadu_ps(&right[0]);
	__m128 row2 = _mm_loadu_ps(&right[4]);
	__m128 row3 = _mm_loadu_ps(&right[8]);
	__m128 row4 = _mm_loadu_ps(&right[12]);
	for (int i = 0; i<4; i++) {
		__m128 brod1 = _mm_set1_ps(left[4 * i + 0]);
		__m128 brod2 = _mm_set1_ps(left[4 * i + 1]);
		__m128 brod3 = _mm_set1_ps(left[4 * i + 2]);
		__m128 brod4 = _mm_set1_ps(left[4 * i + 3]);
		__m128 row = _mm_add_ps(
			_mm_add_ps(
			_mm_mul_ps(brod1, row1),
			_mm_mul_ps(brod2, row2)),
			_mm_add_ps(
			_mm_mul_ps(brod3, row3),
			_mm_mul_ps(brod4, row4)));
		_mm_storeu_ps(&out[4 * i], row);
	}
}
void Matrix4x4::M4x4_Slow(float* left, float* right, float* result)
{
	result[0] = left[0] * right[0] + left[1] * right[4] + left[2] * right[8] + left[3] * right[12];
	result[1] = left[0] * right[1] + left[1] * right[5] + left[2] * right[9] + left[3] * right[13];
	result[2] = left[0] * right[2] + left[1] * right[6] + left[2] * right[10] + left[3] * right[14];
	result[3] = left[0] * right[3] + left[1] * right[7] + left[2] * right[11] + left[3] * right[15];

	result[4] = left[4] * right[0] + left[5] * right[4] + left[6] * right[8] + left[7] * right[12];
	result[5] = left[4] * right[1] + left[5] * right[5] + left[6] * right[9] + left[7] * right[13];
	result[6] = left[4] * right[2] + left[5] * right[6] + left[6] * right[10] + left[7] * right[14];
	result[7] = left[4] * right[3] + left[5] * right[7] + left[6] * right[11] + left[7] * right[15];

	result[8] = left[8] * right[0] + left[9] * right[4] + left[10] * right[8] + left[11] * right[12];
	result[9] = left[8] * right[1] + left[9] * right[5] + left[10] * right[9] + left[11] * right[13];
	result[10] = left[8] * right[2] + left[9] * right[6] + left[10] * right[10] + left[11] * right[14];
	result[11] = left[8] * right[3] + left[9] * right[7] + left[10] * right[11] + left[11] * right[15];

	result[12] = left[12] * right[0] + left[13] * right[4] + left[14] * right[8] + left[15] * right[12];
	result[13] = left[12] * right[1] + left[13] * right[5] + left[14] * right[9] + left[15] * right[13];
	result[14] = left[12] * right[2] + left[13] * right[6] + left[14] * right[10] + left[15] * right[14];
	result[15] = left[12] * right[3] + left[13] * right[7] + left[14] * right[11] + left[15] * right[15];
}
#pragma endregion matrix4x4_methods

///
//matrix4x4 operators
///
#pragma region matrix4x4_operators
Matrix4x4 Matrix4x4::operator*(Matrix4x4& right)
{
	return M4x4_SSE(*this, right);
}
void Matrix4x4::operator*=(Matrix4x4& right)
{
	M4x4_SSE(*this, right, *this);
}
Matrix4x4 Matrix4x4::operator*(float right)
{
	return Matrix4x4(m11*right, m12*right, m13*right, m14*right,
		m21*right, m22*right, m23*right, m24*right,
		m31*right, m32*right, m33*right, m34*right,
		m41*right, m42*right, m43*right, m44*right);
}
Vector3f Matrix4x4::operator*(Vector3f& right)
{
	return Vector3f(m11*right.x + m12*right.y + m13*right.z, m21*right.x + m22*right.y + m23*right.z, m31*right.x + m32*right.y + m33*right.z);
}


float& Matrix4x4::operator[](int index)
{
	return mat[index];
}
#pragma endregion matrix4x4_operators