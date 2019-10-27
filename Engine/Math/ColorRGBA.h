#ifndef COLOR_RGBA_H_
#define COLOR_RGBA_H_

#include "../Global.h"
#include <string>
#include <sstream>

class ColorRGBA
{
public:

	/* Setter used by constructors */
	void setColor(_float red, _float green, _float blue, _float alpha)
	{
		mComponents[0] = red;
		mComponents[1] = green;
		mComponents[2] = blue;
		mComponents[3] = alpha;
	}

	/* Constructors */
	ColorRGBA() : ColorRGBA(1, 1, 1, 1) {}
	ColorRGBA(_float gray) : ColorRGBA(gray, 1) {}
	ColorRGBA(_float gray, _float alpha) : ColorRGBA(gray, gray, gray, alpha) {}
	ColorRGBA(const ColorRGBA& other) : ColorRGBA(other.red(), other.green(), other.blue(), other.alpha()) {}
	ColorRGBA(_float red, _float green, _float blue, _float alpha)
	{
		setColor(red, green, blue, alpha);
	}

	/* Destructor */
	virtual ~ColorRGBA() {}

	/* Getter */
	_float red() const { return mComponents[0]; }
	_float green() const { return mComponents[1]; }
	_float blue() const { return mComponents[2]; }
	_float alpha() const { return mComponents[3]; }

	_float const * getArrayPointer() const { return &(mComponents[0]); }

	/* Setter */
	void setRed(_float red) { mComponents[0] = red; }
	void setGreen(_float green) { mComponents[1] = green; }
	void setBlue(_float blue) { mComponents[2] = blue; }
	void setAlpha(_float alpha) { mComponents[3] = alpha; }
	void set(ColorRGBA other)
	{
		mComponents[0] = other.red();
		mComponents[1] = other.green();
		mComponents[2] = other.blue();
		mComponents[3] = other.alpha();
	}

	/* Casts */
	operator std::string() const
	{
		stringstream ss;
		ss << "(" << to_string(mComponents[0]) << ", " << to_string(mComponents[1]) << ", " << to_string(mComponents[2]) << ", " << to_string(mComponents[3]) << ")";
		return ss.str();
	}

	// TODO operatoren

private:

	/* Members */
	_float mComponents[4];
};

#endif
