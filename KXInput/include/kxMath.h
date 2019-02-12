#ifndef __KXMATH_H__
#define __KXMATH_H__

struct Vector2
{
	Vector2()
	{
		x = 0.f;
		y = 0.f;
	}

	Vector2(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	Vector2& operator+=(const Vector2& a_rhs)
	{
		x += a_rhs.x;
		y += a_rhs.y;
		return *this;
	}

	friend Vector2 operator+(Vector2 a_lhs, const Vector2& a_rhs)
	{
		a_lhs += a_rhs;
		return a_lhs;
	}

	Vector2& operator-=(const Vector2& a_rhs)
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		return *this;
	}

	friend Vector2 operator-(Vector2 a_lhs, const Vector2& a_rhs)
	{
		a_lhs -= a_rhs;
		return a_lhs;
	}

	Vector2& operator*=(const Vector2& a_rhs)
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		return *this;
	}

	friend Vector2 operator*(Vector2 a_lhs, const Vector2& a_rhs)
	{
		a_lhs *= a_rhs;
		return a_lhs;
	}

	Vector2& operator/=(const Vector2& a_rhs)
	{
		x /= a_rhs.x;
		y /= a_rhs.y;
		return *this;
	}

	friend Vector2 operator/(Vector2 a_lhs, const Vector2& a_rhs)
	{
		a_lhs /= a_rhs;
		return a_lhs;
	}

	float x, y;
};


#endif