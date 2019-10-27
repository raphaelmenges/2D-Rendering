#include "Material.h"
#include "../AssetManager.h"

void Material::init(AssetManager* pAssetManager, MaterialType materialType, ShaderType shaderType)
{
	mpAssetManager = pAssetManager;
	mType = materialType;
	mpShader = pAssetManager->loadShader(shaderType);
}

void Material::bind() const
{
	mpShader->bind();
}
