#include "Shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{

}

string Shader::readShaderFile(string fullpath, vector<string> defines) const
{
	/* Read shader */
	string text = readFile(fullpath);

	/* Find DEFINES_PHRASE */
	stringstream ss(text);
	string line;
	string textWithDefines;

	while (getline(ss, line, '\n'))
	{
		if (line.compare(DEFINES_PHRASE) == 0)
		{
			/* Add defines instead of DEFINES_PHRASE */
			for (string define : defines)
			{
				textWithDefines += define + "\n";
			}
		}
		else
		{
			/* Copy code */
			textWithDefines += line + "\n";
		}
	}

	/* Return complete text*/
	return textWithDefines;
}
