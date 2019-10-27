#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../Global.h"
#include <vector>
#include <fstream>

#include "../External/picopng.h"

enum class TextureType
{
	Gray, Color, ColorAlpha
};

enum class TextureFiltering
{
	Nearest, Linear
};

enum class TextureWrap
{
	Clamp, Mirror, Repeat
};

class Texture
{
public:

	/* Constructor */
	Texture();

	/* Destructor */
	virtual ~Texture();

	/* Initialization */
	virtual void init(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering) = 0;

	/* Binding */
	virtual void bind(_uint slot) const = 0;

protected:

	/* Load image from disk */
	void loadImage(TextureType type, string fullpath, vector<unsigned char> &image, _ulong &width, _ulong &height, bool flipVertical);

	/* Members */
	_ulong mWidth;
	_ulong mHeight;

};

#endif
