#include "RenderItem_OGL33.h"

RenderItem_OGL33::RenderItem_OGL33()
{
}

RenderItem_OGL33::~RenderItem_OGL33()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
}

void RenderItem_OGL33::init(Mesh const * pMesh, Material const * pMaterial, _float const * pLocalMedianZ)
{
	RenderItem::init(pMesh, pMaterial, pLocalMedianZ);

	mpMesh_OGL33 = dynamic_cast<Mesh_OGL33 const *>(mpMesh);
	mpShader_OGL33 = dynamic_cast<Shader_OGL33 const *>(mpMaterial->getShader());

	/* Vertex Array Object */
	mVertexArrayObject = 0;
	glGenVertexArrays(1, &mVertexArrayObject);
	glBindVertexArray(mVertexArrayObject);

	/* Vertices */
	_int vertexAttrib = glGetAttribLocation(mpShader_OGL33->getProgramHandle(), "vertex");
	glEnableVertexAttribArray(vertexAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, mpMesh_OGL33->getVerticesBufferHandle());
	glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	/* Texture coordinates */
	_int uvAttrib = glGetAttribLocation(mpShader_OGL33->getProgramHandle(), "textureCoordinate");
	glEnableVertexAttribArray(uvAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, mpMesh_OGL33->getTextureCoordinateBufferHandle());
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	/* Unbind as current VAO */
	glBindVertexArray(0);
}

void RenderItem_OGL33::bind() const
{
	glBindVertexArray(mVertexArrayObject);
}

void RenderItem_OGL33::drawOneInstance(RenderParameter const * pRenderParameter) const
{
    /* Fill uniforms (cheaper to have loop per class) */
    for (const pair<string, Matrix4f>& parameter : pRenderParameter->getMatrices4f())
	{
        glUniformMatrix4fv(mUniformLocationsCache.at(parameter.first), 1, GL_TRUE, parameter.second.getArrayPointer());
	}
    for (const pair<string, ColorRGBA>& parameter : pRenderParameter->getColorsRGBAs())
	{
        glUniform4fv(mUniformLocationsCache.at(parameter.first), 1, parameter.second.getArrayPointer());
	}

	/* Camera */
	glUniformMatrix4fv(mCameraUniformLocation, 1, GL_TRUE, pRenderParameter->getCamera()->getProjectionViewMatrix()->getArrayPointer());

	/* World position */
	glUniformMatrix4fv(mWorldPositionUniformLocation, 1, GL_TRUE, pRenderParameter->getModelMatrix()->getArrayPointer());

	/* Drawing */
    glDrawArrays(GL_TRIANGLES, 0, mpMesh_OGL33->getVertexCount());
}

void RenderItem_OGL33::updateShaderInputLocationsCache(RenderParameter const * pRenderParameter)
{
	/* Matrices */
    for (const pair<string, Matrix4f>& parameter : pRenderParameter->getMatrices4f())
	{
        mUniformLocationsCache[parameter.first] = glGetUniformLocation(mpShader_OGL33->getProgramHandle(), parameter.first.c_str());
	}

	/* Colors */
    for (const pair<string, ColorRGBA>& parameter : pRenderParameter->getColorsRGBAs())
	{
        mUniformLocationsCache[parameter.first] = glGetUniformLocation(mpShader_OGL33->getProgramHandle(), parameter.first.c_str());
	}

	/* Camera */
	mCameraUniformLocation = glGetUniformLocation(mpShader_OGL33->getProgramHandle(), RENDER_PARAMETER_PROJECTION_VIEW_MATRIX.c_str());

	/* World position */
	mWorldPositionUniformLocation = glGetUniformLocation(mpShader_OGL33->getProgramHandle(), RENDER_PARAMETER_MODEL_MATRIX.c_str());
	
}
