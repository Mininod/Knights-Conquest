#pragma once
#include "Static.h"

class Wall : public Static
{
public:
	Wall(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight, std::string bitmapFileName, int renderLayer);
	~Wall();
	void Update() override;
	void Start() override;
};

