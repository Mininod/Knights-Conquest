#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight);
	~Item();
private:
	void Start() override;
	void Update() override;
};

