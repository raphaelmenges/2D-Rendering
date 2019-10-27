#ifndef SHADER_H_
#define SHADER_H_

#include "../Global.h"
#include "../Utilities/FileReader.h"

#include <string>
#include <vector>
#include <sstream>

const string DEFINES_PHRASE = "#custom_defines";

/* Standard can be also transparent! */
enum class ShaderType
{
	Standard, Standard_Masked
};

class Shader
{
public:

	/* Constructor */
	Shader();

	/* Destructor */
	virtual ~Shader();

	/* Initialization TODO defines as variadic strings */
	virtual void init(ShaderType shaderType) = 0;

	/* Binding */
	virtual void bind() const = 0;

protected:

	/* Read shader file */
	string readShaderFile(string fullpath, vector<string> defines) const;
};

#endif
