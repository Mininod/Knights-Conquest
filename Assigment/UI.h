#pragma once
#include <string>
#include "Vector2.h"
#include "Player.h"
#include "Bitmap.h"

class UI
{
public:
	UI(Player* player);
	~UI();
	void Draw(Vector2 pos);
	void AddItem(GameObjectSymbols symbol);
	int GetItemAmount(GameObjectSymbols symbol);
	void RemoveItem(GameObjectSymbols symbol, int amount);
private:
	Player* mPlayer;
	Bitmap mHeart;
	Bitmap mCoin;
	Bitmap mCoolDown;
	Bitmap mKey;
	int mTime; 
	int mCurCoins;
	int mCurKeys;
};

