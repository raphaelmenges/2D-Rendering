#ifndef MATRIX_4F_H_
#define MATRIX_4F_H_

#include "../Types.h"
#include <string>
#include <sstream>
#include <cmath>
#include "Constants.h"

class Matrix4f
{
public:

	/* Setter used by constructors */
	void setFields(_float aa, _float ab, _float ac, _float ad,
		_float ba, _float bb, _float bc, _float bd,
		_float ca, _float cb, _float cc, _float cd,
		_float da, _float db, _float dc, _float dd)
	{
		this->mFields[0][0] = aa;
		this->mFields[0][1] = ab;
		this->mFields[0][2] = ac;
		this->mFields[0][3] = ad;

		this->mFields[1][0] = ba;
		this->mFields[1][1] = bb;
		this->mFields[1][2] = bc;
		this->mFields[1][3] = bd;

		this->mFields[2][0] = ca;
		this->mFields[2][1] = cb;
		this->mFields[2][2] = cc;
		this->mFields[2][3] = cd;

		this->mFields[3][0] = da;
		this->mFields[3][1] = db;
		this->mFields[3][2] = dc;
		this->mFields[3][3] = dd;
	}

	/* Constructors */
	Matrix4f() : Matrix4f(0) {}

	Matrix4f(_float value)
	{
		this->setFields(value, value, value, value,
			value, value, value, value,
			value, value, value, value,
			value, value, value, value);
	}

	Matrix4f(_float aa, _float ab, _float ac, _float ad,
		_float ba, _float bb, _float bc, _float bd,
		_float ca, _float cb, _float cc, _float cd,
		_float da, _float db, _float dc, _float dd)
	{
		this->setFields(aa, ab, ac, ad, ba, bb, bc, bd, ca, cb, cc, cd, da, db, dc, dd);
	}

	/* Destructor */
	virtual ~Matrix4f() {}

	/* Getter */
	_float getField(_int row, _int column) const { return mFields[row][column]; }
	_float const * getArrayPointer() const { return &(mFields[0][0]); }

	/* Setter */
	void setField(_int row, _int column, _float value) { mFields[row][column] = value; }

	/* Casts */
	operator std::string() const
	{
		std::stringstream ss;
		for (int r = 0; r < 4; r++)
		{
			ss << "(";
			for (int c = 0; c < 4; c++)
			{
				ss << std::to_string(mFields[r][c]);
				if (c < 3)
				{
					ss << ", ";
				}
			}
			ss << ")";
			if (r < 3)
			{
				ss << "\n";
			}
		}
		return ss.str();
	}

	/* Operators */
	Matrix4f operator * (const Matrix4f& right) const
	{
		Matrix4f result;
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				/* For each value, 4 multiplications are necessary */
				for (int i = 0; i < 4; i++)
				{
					result.addToField(r, c, mFields[r][i] * right.getField(i, c));
				}
			}
		}
		return result;
	}

	/* Operators */
	Matrix4f& operator *= (const Matrix4f& right)
	{
		Matrix4f left = *this;
		*this = Matrix4f::zeros();
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				/* For each value, 4 multiplications are necessary */
				for (int i = 0; i < 4; i++)
				{
					this->addToField(r, c, left.getField(r, i) * right.getField(i, c));
				}
			}
		}
		return *this;
	}


	// Skalare sachen

	// Gleichheit

	/* Matrix values */

	// Determinante

	// Eigenwert? :D

	/* Other */
	void addToField(_int row, _int column, _float value) { mFields[row][column] += value; }

	/* Useful matrices */
	static Matrix4f eye()
	{
		return Matrix4f(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	static Matrix4f zeros()
	{
		return Matrix4f(0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
	}

	static Matrix4f orthographic(_float left, _float right, _float bottom, _float top, _float near, _float far)
	{
		const _float two = 2;
		return Matrix4f(two / (right - left), 0, 0, -(right + left) / (right - left),
			0, two / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, -two / (far - near), -(far + near) / (far - near),
			0, 0, 0, 1);
	}

	static Matrix4f rotationZAxis(_float degree)
	{
		_float rad = degree / static_cast<_float>(180.0) * _PI;
		return Matrix4f(std::cos(rad), -std::sin(rad), 0, 0,
			std::sin(rad), std::cos(rad), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

private:

	/* Members */
	_float mFields[4][4];
};

#endif
