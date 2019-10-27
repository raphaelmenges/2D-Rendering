#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "../Global.h"
#include "Shader.h"
#include <memory>
#include "Texture.h"
#include "../Math/Math.h"
#include <map>

class AssetManager;

enum class MaterialType
{
	Standard
};

enum class ParameterClass // TODO maybe move to Math?
{
    COLOR_RGBA, MATRIX_4F
};

class Material
{
public:

	/* Constructor */
	Material() {}

	/* Destructor */
     virtual ~Material() {}

	/* Initialization */
	virtual void init(AssetManager* pAssetManager) = 0;

	/* Bind material for drawing */
	virtual void bind() const;

	/* Get pointer to shader */
	Shader const * getShader() const { return mpShader; }

	/* Get type */
	MaterialType getType() const { return mType; }

    /* Get available parameters */
    const map<string, ParameterClass>& getAvailableParameters() const { return mAvailableParameters; }

protected:

	/* Internal initialization */
	void init(AssetManager* pAssetManager, MaterialType materialType, ShaderType shaderType);

	/* Members */
	AssetManager* mpAssetManager;
	Shader const * mpShader;
	MaterialType mType;
    map<string, ParameterClass> mAvailableParameters;
};

#endif
