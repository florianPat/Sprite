#pragma once

#include <cmath>

template <typename T>
class Vec2_
{
public:
	Vec2_(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{
	}

	Vec2_<T> operator+(const Vec2_<T>& rhs) const
	{
		return Vec2_<T>(x + rhs.x, y + rhs.y);
	}

	Vec2_<T>& operator+=(const Vec2_<T>& rhs)
	{
		return *this = *this + rhs;
	}

	Vec2_<T> operator*(T rhs) const
	{
		return Vec2_<T>(x * rhs, y * rhs);
	}

	Vec2_<T>& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}

	Vec2_<T> operator-(const Vec2_<T>& rhs) const
	{
		return Vec2_<T>(x - rhs.x, y - rhs.y);
	}

	Vec2_<T>& operator-=(const Vec2_<T>& rhs)
	{
		return *this = *this - rhs;
	}

	T GetLength() const
	{
		return std::sqrt(GetLengthSq());
	}

	T GetLengthSq() const
	{
		return x * x + y * y;
	}

	Vec2_<T>& Normalize()
	{
		return *this = GetNormalized();
	}

	Vec2_<T> GetNormalized() const
	{
		const T len = GetLength();
		if (len != 0.0f)
		{
			return *this * (1.0f / len);
		}
		return *this;
	}

	operator Vec2_<T>() const
	{
		return{ int(x),int(y) };
	}

public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;
