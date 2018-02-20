#include "Static.h"
#include "Bitmap.h"


Static::Static(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight, std::string bitmapFileName, int renderLayer) : GameObject(newName, symbol, position, colliderPosition, collierWidthHeight)
{
	GetBitmap()->CreateBitmap(bitmapFileName, true, renderLayer);
}


Static::~Static()
{
}

void Static::Start()
{
}

void Static::Update()
{
}
