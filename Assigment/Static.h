#pragma once
#include "GameObject.h"

class Static : public GameObject
{
public:
	Static(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight, std::string bitmapFileName, int renderLayer);
	~Static();
private:
	void Start() override;
	void Update() override;
};

