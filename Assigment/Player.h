#pragma once
#include <iostream>
#include "Charater.h"
#include "Game.h"
#include"Bitmap.h"

class Player : public Charater
{
public:
	Player(std::string name, GameObjectSymbols Symbol, Vector2 position);
	Player(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight);
	~Player();
	virtual void Move() override;
	virtual void Attack() override;
private:
	void Update() override;
	void Start() override;
	void HealthCheck();
};

