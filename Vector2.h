#pragma once

#include <cmath>

// 2éüå≥ÉxÉNÉgÉã
class Vec2
{
public:
	int x;
	int y;

public:
	Vec2()
	{
		x = 0;
		y = 0;
	}
	Vec2(int posX, int posY)
	{
		x = posX;
		y = posY;
	}
	// Vec2 = (Vec2 += Vec2)
	Vec2 operator+=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	// Vec2 = Vec2 + Vec2
	Vec2 operator+(const Vec2& vec) const
	{
		Vec2 temp{ x + vec.x , y + vec.y };
		return temp;
	}

	// Vec2 = (Vec2 -= Vec2)
	Vec2 operator-=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	// Vec2 = Vec2 - Vec2
	Vec2 operator-(const Vec2& vec) const
	{
		Vec2 temp{ x - vec.x , y - vec.y };
		return temp;
	}

	// Vec2 = (Vec2 *= float)
	Vec2 operator*=(int scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	// Vec2 = Vec2 * float
	Vec2 operator*(int scale) const
	{
		Vec2 temp{ x * scale , y * scale };
		return temp;
	}

	// Vec2 = (Vec2 /= float)
	Vec2 operator/=(int scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
	// Vec2 = Vec2 / float
	Vec2 operator/(int scale) const
	{
		Vec2 temp{ x / scale , y / scale };
		return temp;
	}

	// í∑Ç≥ÇÃéÊìæ
	int length()
	{
		return sqrtf((x * x) + (y * y));
	}

	// ê≥ãKâª Vec2 = Vec2.normalize()
	Vec2 normalize()
	{
		int len = length();
		if (len == 0)
		{
			return *this;
		}
		return (*this) / len;
	}
};