#include "StandardMaterial.h"
#include "../AssetManager.h"

void StandardMaterial::init(AssetManager* pAssetManager)
{
	init(pAssetManager, StandardMaterialType::Solid);
}

void StandardMaterial::init(AssetManager* pAssetManager, StandardMaterialType type)
{
	/* Determine correct shader */
	ShaderType shaderType;
	switch (type)
	{
	case StandardMaterialType::Solid:
		shaderType = ShaderType::Standard;
		break;
	case StandardMaterialType::Masked:
		shaderType = ShaderType::Standard_Masked;
		break;
	case StandardMaterialType::Transparent:
		shaderType = ShaderType::Standard;

		/* Add to right bucket */
		// TODO

		break;
	}

	/* Super call */
	Material::init(
		pAssetManager,
		MaterialType::Standard,
		shaderType);
}

void StandardMaterial::setDiffuse(string imagePath, bool linearFiltering, bool hasAlpha)
{
	/* Textures */
	mpDiffuse = mpAssetManager->loadTexture(
		imagePath,
		hasAlpha ? TextureType::ColorAlpha : TextureType::Color,
		TextureWrap::Repeat,
		linearFiltering ? TextureFiltering::Linear : TextureFiltering::Nearest);
}

void StandardMaterial::bind() const
{
	/* Super call */
	Material::bind();

	/* Textures */
	mpDiffuse->bind(0);
}
