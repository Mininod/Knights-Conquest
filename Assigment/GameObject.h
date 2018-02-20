#pragma once
#include <math.h>
#include <iostream>
#include "Vector2.h"

class Collision;
class Bitmap;

enum GameObjectSymbols
{
	PLAYER = 'P', BAT = 'B', SLUG = 'S', WALL = 'W',FAKE_WALL = 'F', DOOR = 'D', FLOOR = '.', HEALTH_POT = 'H', COIN = 'C', KEY = 'K', CRATE = 's', EXIT = '#', SIZE_OF_GAME_OBJECT_SYMBOLS_PRESSED_LIST_ENUM = '@'
};

class GameObject
{
public:
	GameObject(std::string newName, GameObjectSymbols symbol, Vector2 position);
	GameObject(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight);
	~GameObject();
	std::string GetName();
	bool isActive();
	void SetActiveState(bool isActive);
	virtual void Update();
	void Draw();
	Vector2 GetPostion();
	Collision* GetCollider();
	char GetLevelSymbol();
	void Debug();
	bool IsColliderTrigger();
	Bitmap* GetBitmap();
	void SetPostion(Vector2 pos);
protected:
	virtual void Start();
	void SetIsColliderTrigger(bool foo);
private:
	Collision* mpBoxCollider;
	std::string mName;
	bool mIsActive;
	Vector2 mPosition;
	Bitmap* mpBitmap;
	char mLevelSymbol;
	bool mIsColliderTrigger;
};

