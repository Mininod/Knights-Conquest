#pragma once
#include "Charater.h"

class Enemy : public Charater
{
public:
	Enemy(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight);
	~Enemy();
private:
	void Start() override;
	void Update() override;
	void Move() override;
	void Attack() override;
};

