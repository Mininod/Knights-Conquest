#include "Item.h"
#include "Global.h"
#include "Player.h"
#include "UI.h"
#include "Collision.h"

Item::Item(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight) : GameObject(newName,  symbol, position,  colliderPosition, collierWidthHeight)
{
	Start();
}

Item::~Item()
{
}

void Item::Start()
{
	switch (GetLevelSymbol())
	{
	case HEALTH_POT:
		GetBitmap()->CreateBitmap("Assets/Heart.bmp", true, 2);
		break;
	case COIN:
		GetBitmap()->CreateBitmap("Assets/Coin.bmp", true, 2);
		break;
	case KEY:
		GetBitmap()->CreateBitmap("Assets/Key.bmp", true, 2);
		break;
	default:
		std::cout << GetName() <<"Item created with a invalid level symbol" << std::endl;
		break;
	}
	SetIsColliderTrigger(true);
}

void Item::Update()
{
	Player* player = Global::GAME.GetPlayer();
	if (GetCollider()->GetDistanceBetweenTwoPoints(GetPostion(),player->GetPostion()) < 7)
	{
		if (GetCollider()->IsColliding(GetPostion(), GetCollider()->GetCollisionDimensions(), player->GetPostion(), player->GetCollider()->GetCollisionDimensions()))
		{
			switch (GetLevelSymbol())
			{
			case HEALTH_POT:
				if (player->GetHealth() < player->GetMaxHealth())
				{
					player->SetHealth(player->GetHealth() + 1);
					std::cout << "Health Gained" << std::endl;
					SetActiveState(false);
				}
				else
				{
					Vector2 pos = GetPostion();
					float speed = 1;
					Vector2 playerPos = Global::GAME.GetPlayer()->GetPostion();
					//Up
					if (playerPos.y  > pos.y && GetCollider()->IsSpaceFree(GetPostion(), GetCollider()->GetCollisionDimensions(), speed, Direction_UP))
					{
						pos.y -= speed;
					}
					//Left
					if (playerPos.x > pos.x && GetCollider()->IsSpaceFree(GetPostion(), GetCollider()->GetCollisionDimensions(), speed, Direction_LEFT))
					{
						pos.x -= speed;
					}
					//Down
					if (playerPos.y  < pos.y && GetCollider()->IsSpaceFree(GetPostion(), GetCollider()->GetCollisionDimensions(), speed, Direction_DOWN))
					{
						pos.y += speed;
					}
					//Right
					if (playerPos.x < pos.x && GetCollider()->IsSpaceFree(GetPostion(), GetCollider()->GetCollisionDimensions(), speed, Direction_RIGHT))
					{
						pos.x += speed;
					}
					SetPostion(pos);
				}
				break;
			case COIN:
				Global::GAME.GetUI()->AddItem(COIN);
				SetActiveState(false);
				break;
			case KEY:
				Global::GAME.GetUI()->AddItem(KEY);
				SetActiveState(false);
			default:
				break;
			}
		}
	}
}
