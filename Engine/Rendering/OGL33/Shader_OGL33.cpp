#include "Shader_OGL33.h"

Shader_OGL33::Shader_OGL33()
{

}

Shader_OGL33::~Shader_OGL33()
{
	glDeleteProgram(mProgram);
}

void Shader_OGL33::init(ShaderType shaderType)
{
	/* Create defines */
	vector<string> vertexDefines;
	vector<string> fragmentDefines;

	switch (shaderType)
	{
	case ShaderType::Standard:
		// Nothing to do here
		break;
	case ShaderType::Standard_Masked:
		/* Set right define */
		fragmentDefines.push_back(OGL33_DEFINE_PREFIX + "USE_DISCARD");
		break;
	}

	/* Vertex shader */
	string vertexData = readShaderFile(OGL33_SHADERS_PATH + "Standard.vert", vertexDefines);
	vector<char> vertexBuffer(vertexData.size() + 1);
	copy(vertexData.begin(), vertexData.end(), vertexBuffer.begin());
	const char* vertexShaderSource = &vertexBuffer[0];

	_uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	logShaderInfo(vertexShader);

	/* Fragment shader */
	string fragmentData = readShaderFile(OGL33_SHADERS_PATH + "Standard.frag", fragmentDefines);
	vector<char> fragmentBuffer(fragmentData.size() + 1);
	copy(fragmentData.begin(), fragmentData.end(), fragmentBuffer.begin());
	const char* fragmentShaderSource = &fragmentBuffer[0];

	_uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	logShaderInfo(fragmentShader);

	/* Create program */
	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);
	glLinkProgram(mProgram);

	/* Delete shaders */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader_OGL33::bind() const
{
	glUseProgram(mProgram);
}

void Shader_OGL33::logShaderInfo(_uint shaderHandle)
{
	/* Get length of log */
	_int logLength = 0;
	if (glIsShader(shaderHandle))
	{
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
	}

	/* If there is log, write it to debug logging output */
    if (logLength > 1)
	{
		/* Copy log to chars */
		char* log = new char[logLength];
        glGetShaderInfoLog(shaderHandle, logLength, NULL, log);

		/* Print to logger */
		Logger::warning(log);

		/* Delete chars */
		delete[] log;
	}
}
