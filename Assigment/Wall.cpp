#include "Wall.h"



Wall::Wall(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight, std::string bitmapFileName, int renderLayer) : Static(newName, symbol, position, colliderPosition, collierWidthHeight, bitmapFileName, renderLayer)
{
	Start();
}


Wall::~Wall()
{
}

void Wall::Start()
{
}

void Wall::Update()
{
}
