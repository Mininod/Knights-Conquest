#pragma once
#include "Static.h"

class Collision;

class Door : public Static
{
public:
	Door(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight, std::string bitmapFileName, int renderLayer);
	~Door();
private:
	void Update() override;
	Collision* mTrigger;
};

