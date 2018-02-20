#include "Door.h"
#include "Global.h"
#include "Player.h"
#include "Collision.h"
#include "UI.h"


Door::Door(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight, std::string bitmapFileName, int renderLayer) : Static(newName, symbol, position, colliderPosition, collierWidthHeight, bitmapFileName, renderLayer)
{
	mTrigger = new Collision(0, 0, 0, 0);
}


Door::~Door()
{
}

void Door::Update()
{
	Player* player = Global::GAME.GetPlayer();

	if (Global::GAME.GetUI()->GetItemAmount(KEY) > 0 && mTrigger->GetDistanceBetweenTwoPoints(GetPostion(), player->GetPostion()) < 40)
	{
		if (mTrigger->IsColliding(GetPostion(), mTrigger->GetCollisionDimensions(), player->GetPostion(), player->GetCollider()->GetCollisionDimensions()))
		{
			Global::GAME.GetUI()->RemoveItem(KEY, 1);
			SetActiveState(false);
		}
	}
}
