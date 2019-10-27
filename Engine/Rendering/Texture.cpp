#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::loadImage(TextureType type, string fullpath, vector<unsigned char> &image, _ulong &width, _ulong &height, bool flipVertical)
{
	/* Read file */
	ifstream in(fullpath.c_str(), ios::in | ios::binary);

	/* Get size */
	in.seekg(0, ios::end);
	streamsize size = in.tellg();

	/* Read it */
	in.seekg(0, ios::beg);
	vector<char> buffer(static_cast<_uint>(size));
	in.read(&(buffer[0]), static_cast<_uint>(size));

	/* Close file */
	in.close();

	/* Decode image */
	decodePNG(image, width, height, reinterpret_cast<unsigned char*>(&(buffer[0])), static_cast<_uint>(size), false);

	/* Calculate number of channels */
	_uint channelCount = static_cast<_uint>(image.size() / (width * height * sizeof(unsigned char)));

	/* TODO: Compare Type with channel count and do something */

	/* Flip vertical if necessary */
	if (flipVertical)
	{
		vector<unsigned char> copyImage(image);

		/* Go over lines */
		for (_uint i = 0; i < height; i++)
		{
			/* Go over columns */
			for (_uint j = 0; j < width; j++)
			{
				/* Go over channels */
				for (_uint k = 0; k < channelCount; k++)
				{
					image[i * width * channelCount + j * channelCount + k] = copyImage[(height - 1 - i) * width * channelCount + j * channelCount + k];
				}
			}
		}
	}
}
