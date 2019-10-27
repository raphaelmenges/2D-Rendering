#include "Texture_OGL33.h"

Texture_OGL33::Texture_OGL33()
{
}

Texture_OGL33::~Texture_OGL33()
{
	glDeleteTextures(1, &mTexture);
}

void Texture_OGL33::init(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering)
{
	/* Read image from disk */
	vector<unsigned char> image;
	loadImage(type, ASSETS_PATH + path, image, mWidth, mHeight, true);

	/* Create OpenGL texture */
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	/* Wrapping */
	switch (wrap)
	{
	case TextureWrap::Clamp:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case TextureWrap::Mirror:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	case TextureWrap::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	}

	/* Loading */
	switch (type)
	{
	case TextureType::Gray:
		Logger::error("TextureType::Gray: Not yet implemented");
		break;
	case TextureType::Color:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &image[0]);
		break;
	case TextureType::ColorAlpha:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
		break;
	}

	/* Filtering */
	switch (filtering)
	{
	case TextureFiltering::Linear:
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case TextureFiltering::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	}

	/* Unbind texture */
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture_OGL33::bind(_uint slot) const
{
	/* Choose slot */
	switch (slot)
	{
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE1);
		break;
	case 2:
		glActiveTexture(GL_TEXTURE2);
		break;
	case 3:
		glActiveTexture(GL_TEXTURE3);
		break;
	case 4:
		glActiveTexture(GL_TEXTURE4);
		break;
	case 5:
		glActiveTexture(GL_TEXTURE5);
		break;
	case 6:
		glActiveTexture(GL_TEXTURE6);
		break;
	case 7:
		glActiveTexture(GL_TEXTURE7);
		break;
	case 8:
		glActiveTexture(GL_TEXTURE8);
		break;
	case 9:
		glActiveTexture(GL_TEXTURE9);
		break;
	default:
		glActiveTexture(GL_TEXTURE0);
	}

	/* Bind texture */
	glBindTexture(GL_TEXTURE_2D, mTexture);
}
