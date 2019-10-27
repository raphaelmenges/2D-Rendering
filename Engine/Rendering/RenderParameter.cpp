#include "RenderParameter.h"
#include "RenderItem.h"

void RenderParameter::init(Material const * pMaterial, bool visible)
{
    mVisible = visible;

    /* Initialize parameters */
    for (const pair<string, ParameterClass>& parameter : pMaterial->getAvailableParameters())
    {
        switch (parameter.second)
        {
        case ParameterClass::MATRIX_4F:
        addMatrix4f(parameter.first);
        break;

        case ParameterClass::COLOR_RGBA:
        addColorRGBA(parameter.first);
        break;

        default:
        Logger::error(parameter.first, " parameter has unkown class");
        }
    }

    if (mpOwner != _null)
    {
        mpOwner->updateShaderInputLocationsCache(this);
    }
}

void RenderParameter::setVisibility(bool visible)
{
	/* Always tell the owner about visibility changes */
	if (mVisible != visible)
	{
		mVisible = visible;

		if (mVisible)
		{
			if (mpOwner != _null)
			{
				mpOwner->activateParameter(this);
			}
		}
		else
		{
			if (mpOwner != _null)
			{
				mpOwner->deactivateParameter(this);
			}
		}
	}
}

bool RenderParameter::isVisible() const
{
	return mVisible;
}

void RenderParameter::addMatrix4f(string name)
{
    mMatrices4f[name] = INITIAL_MATRIX_4F;
}

void RenderParameter::addColorRGBA(string name)
{
    mColorRGBAs[name]  = INITIAL_COLOR_RGBA;
}
