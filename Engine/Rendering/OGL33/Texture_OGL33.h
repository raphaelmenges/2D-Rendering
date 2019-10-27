#ifndef TEXTURE_OGL33_H_
#define TEXTURE_OGL33_H_

#include "../Texture.h"

#include "../../External/gl_core_3_3.h"
#include <GLFW/glfw3.h>

class Texture_OGL33 : public Texture
{
public:

	/* Constructor */
	Texture_OGL33();

	/* Destructor */
	virtual ~Texture_OGL33();

	/* Initialization */
	virtual void init(string path, TextureType type, TextureWrap wrap, TextureFiltering filtering);

	/* Binding */
	virtual void bind(_uint slot) const;

protected:

	/* Members */
	_uint mTexture;
};

#endif
