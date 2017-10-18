#pragma once

#include "Vec2.h"

template <typename T>
class Rect_
{
public:
	Rect_() = default;

	Rect_::Rect_(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{
	}

	Rect_::Rect_(const Vec2<T>& topLeft, const Vec2<T> & bottomRight)
		:
		Rect_(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}

	Rect_::Rect_(const Vec2<T>& topLeft, T width, T height)
		:
		Rect_(topLeft, topLeft + Vec2<T>(width, height))
	{
	}

	bool Rect_::IsOverlappingWith(const Rect_& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}

	bool Rect_::IsContainedBy(const Rect_ & other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}

	bool Rect_::Contains(const Vec2<T>& poT) const
	{
		return poT.x >= left && poT.x < right && poT.y >= top && poT.y < bottom;
	}

	Rect_ Rect_::FromCenter(const Vec2<T> & center, T halfWidth, T halfHeight)
	{
		const Vec2<T> half(halfWidth, halfHeight);
		return Rect_(center - half, center + half);
	}

	Rect_ Rect_::GetExpanded(T offset) const
	{
		return Rect_(left - offset, right + offset, top - offset, bottom + offset);
	}

	Vec2<T> Rect_::GetCenter() const
	{
		return Vec2<T>((left + right) / 2, (top + bottom) / 2);
	}

	T Rect_::GetWidth() const
	{
		return right - left;
	}

	T Rect_::GetHeight() const
	{
		return bottom - top;
	}

public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect_<float> RectF;
typedef Rect_<int> RectI; #pragma once
