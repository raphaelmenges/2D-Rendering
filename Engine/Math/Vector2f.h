#ifndef VECTOR_2F_H_
#define VECTOR_2F_H_

#include "../Types.h"
#include <string>
#include <sstream>
#include <cmath>

class Vector2f
{
public:

	/* Constructors */
	Vector2f() : Vector2f(0, 0) {}
	Vector2f(_float value) : Vector2f(value, value) {}
	Vector2f(const Vector2f& other) : Vector2f(other.x(), other.y()) {}
	Vector2f(_float x, _float y) { mX = x; mY = y; }

	/* Destructor */
	virtual ~Vector2f() {}

	/* Getter */
	_float x() const { return mX; }
	_float y() const { return mY; }

	/* Setter */
	void setX(_float x) { this->mX = x; }
	void setY(_float y) { this->mY = y; }
	void setXY(_float x, _float y) { setX(x); setY(y); }

	/* Casts */
	operator std::string() const
	{
		std::stringstream ss;
		ss << "(" << std::to_string(mX) << ", " << std::to_string(mY) << ")";
		return ss.str();
	}

	/* Methods */
	_float length() const
	{
		return std::sqrt(mX * mX + mY * mY);
	}

	_float max() const
	{
		return mX > mY ? mX : mY;
	}

	/* Operators */
	Vector2f operator + (const Vector2f& right) const
	{
		return Vector2f(mX + right.x(), mY + right.y());
	}

	Vector2f operator - (const Vector2f& right) const
	{
		return Vector2f(mX - right.x(), mY - right.y());
	}

	Vector2f& operator += (const Vector2f& right)
	{
		mX += right.x();
		mY += right.y();
		return *this;
	}

	Vector2f& operator -= (const Vector2f& right)
	{
		mX -= right.x();
		mY -= right.y();
		return *this;
	}

	/* Operations with scalar types */
	Vector2f operator / (const _float& right) const
	{
		return Vector2f(mX / right, mY / right);
	}

	Vector2f& operator /= (const _float right)
	{
		mX /= right;
		mY /= right;
		return *this;
	}

	bool operator == (const Vector2f& right) const
	{
		return (mX == right.x() && mY == right.y());
	}

	/* Static methods */
	static _float dot(const Vector2f& left, const Vector2f& right)
	{
		_float sum = 0;
		sum += left.x() * right.x();
		sum += left.y() * right.y();
		return sum;
	}

	// static Vector2f cross()

private:

	/* Members */
	_float mX;
	_float mY;
};

#endif
