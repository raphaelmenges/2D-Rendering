#ifndef SHADER_OGL33_H_
#define SHADER_OGL33_H_

#include "../Shader.h"

#include "../../External/gl_core_3_3.h"
#include <GLFW/glfw3.h>

const string OGL33_SHADERS_PATH = SHADERS_PATH + "GLSL33/";
const string OGL33_DEFINE_PREFIX = "#define ";

class Shader_OGL33 : public Shader
{
public:

	/* Constructor */
	Shader_OGL33();

	/* Destructor */
	virtual ~Shader_OGL33();

	/* Initialization */
	virtual void init(ShaderType shaderType);

	/* Binding */
	virtual void bind() const;

	/* Getter */
	_uint getProgramHandle() const { return mProgram; }

protected:

	/* Log about shader compilation if there is an error */
	void logShaderInfo(_uint shaderHandle);

	/* Members */
	_uint mProgram;
};

#endif
