#include "UI.h"
#include "Player.h"
#include "Collision.h"
#include "Global.h"

UI::UI(Player * player)
{
	mPlayer = player;
	mHeart.CreateBitmap("Assets/Heart.bmp", true, 5);
	mCoin.CreateBitmap("Assets/Coin.bmp", true, 5);
	mCoolDown.CreateBitmap("Assets/CoolDown.bmp", true, 5);
	mKey.CreateBitmap("Assets/Key.bmp", true, 5);
	std::vector<int> foo = Global::GAME.GetLevelDataPtr()->LoadPlayerData();
	mCurCoins = foo[1];
	mCurKeys = foo[2];
}

UI::~UI()
{
}

void UI::Draw(Vector2 pos)
{
	pos.x += 20;
	pos.y += 20;
	//Hearts
	for (int i = 0; i < mPlayer->GetHealth(); i++)
	{
		mHeart.DrawBitmap(Vector2((i *10) + pos.x, pos.y));
	}
	//Coins
	for (int i = 0; i < mCurCoins; i++)
	{
		mCoin.DrawBitmap(Vector2((i *6) + pos.x + 100, pos.y));
	}
	//Keys
	for (int i = 0; i < mCurKeys; i++)
	{
		mKey.DrawBitmap(Vector2((i * 20) + pos.x, 20 + pos.y));
	}
	//CoolDown
	Vector2 playerPos = mPlayer->GetPostion();
	playerPos.y += mPlayer->GetCollider()->GetCollisionDimensions()[HEIGHT];
	int coolDown = (int) mPlayer->GetAttackCoolDown() / 5;
	for (int i = 0; i < coolDown; i++)
	{
		mCoolDown.DrawBitmap(Vector2(playerPos.x + (4 * i), playerPos.y));
	}

}

void UI::AddItem(GameObjectSymbols symbol)
{
	switch (symbol)
	{
	case COIN:
		mCurCoins++;
		break;
	case KEY:
		mCurKeys++;
		break;
	default:
		break;
	}
}

int UI::GetItemAmount(GameObjectSymbols symbol)
{
	switch (symbol)
	{
	case COIN:
		return mCurCoins;
		break;
	case KEY:
		return mCurKeys;
		break;
	default:
		break;
	}
}

void UI::RemoveItem(GameObjectSymbols symbol, int amount)
{
	switch (symbol)
	{
	case COIN:
		mCurCoins -= amount;
		break;
	case KEY:
		mCurKeys -= amount;
		break;
	default:
		break;
	}
}
