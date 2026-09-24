#include "Title.h"

Title::Title(ID3D11Device* device, int screenWidth, int screenHeight, const WCHAR* textureFilename, int bitmapWidth, int bitmapHeight, int positionX, int positionY) :
	BitmapClassOrtho(device, screenWidth, screenHeight, textureFilename, bitmapWidth, bitmapHeight, positionX, positionY)
{

}

Title::~Title()
{
}

bool Title::Render(ID3D11DeviceContext* deviceContext)
{
	bool result;


	// Re-build the dynamic vertex buffer for rendering to possibly a different location on the screen.
	result = UpdateBuffers(deviceContext);
	if (!result)
	{
		return false;
	}

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return true;
}