#ifndef STANDARD_MATERIAL_H_
#define STANDARD_MATERIAL_H_

#include "Material.h"

enum class StandardMaterialType
{
	Solid, Masked, Transparent
};

class StandardMaterial : public Material
{
public:

	/* Constructor */
    StandardMaterial()
    {
        mAvailableParameters["diffuseMultiplier"] = ParameterClass::COLOR_RGBA;
    }

	/* Destructor */
	virtual ~StandardMaterial() {}

	/* Initialization */
	virtual void init(AssetManager* pAssetManager);
	virtual void init(AssetManager* pAssetManager, StandardMaterialType type);

	/* Diffuse texture */
	void setDiffuse(string imagePath, bool linearFiltering = true, bool hasAlpha = false);

	/* Bind material for drawing */
	virtual void bind() const;

private:

	/* Members */
	Texture const * mpDiffuse;

};

#endif
