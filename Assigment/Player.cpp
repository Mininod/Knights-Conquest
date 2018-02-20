#include "Player.h"
#include "Global.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Collision.h"
#include "UI.h"

Player::Player(std::string name, GameObjectSymbols Symbol, Vector2 position) : Charater(name, Symbol, position)
{
	Start();
}

Player::Player(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight) : Charater(newName, symbol, position, colliderPosition, collierWidthHeight)
{
	Start();
}

void Player::Start()
{
	GetBitmap()->CreateBitmap("Assets/Player.bmp", true, 3);
	SetMoveSpeed(1);
	SetHealth(Global::GAME.GetLevelDataPtr()->LoadPlayerData()[0]);
	SetMaxHealth(5);
	SetMaxCoolDown(50);
	SetIsColliderTrigger(false);
}

void Player::HealthCheck()
{
	if (GetHealth() <= -1)
	{
		SetHealth(GetMaxHealth());
		UI* foo = Global::GAME.GetUI();
		foo->RemoveItem(KEY, Global::GAME.GetUI()->GetItemAmount(KEY));
		foo->RemoveItem(COIN, Global::GAME.GetUI()->GetItemAmount(COIN));
		foo = nullptr;
	}
}

Player::~Player()
{
}

void Player::Move()
{
	Vector2 newPos = GetPostion();
	float speed = GetMoveSpeed();
	
	//Up
	if (Global::GAME.IsKeyPressed(KEY_W) && IsSafeSpace(Direction_UP))
	{
		newPos.y -= speed;
	}
	//Left
	if (Global::GAME.IsKeyPressed(KEY_A) && IsSafeSpace(Direction_LEFT))
	{
		newPos.x -= speed;
	}
	//Down
	if (Global::GAME.IsKeyPressed(KEY_S) && IsSafeSpace(Direction_DOWN))
	{
		newPos.y += speed;
	}
	//Right
	if (Global::GAME.IsKeyPressed(KEY_D) && IsSafeSpace(Direction_RIGHT))
	{
		newPos.x += speed;
	}
	SetPostion(newPos);
}

void Player::Attack()
{
	if (GetAttackCoolDown() <= 0)
	{
		std::vector<GameObject*> foo;
		if (Global::GAME.IsKeyPressed(KEY_UP))
		{
			SetAttackCoolDown(GetMaxCoolDown());
			Collision swordCol(0, -10, 30, 10);
			Vector2 swordPos(GetPostion().x, GetPostion().y);

			foo = swordCol.FindGameObjectsColliding(swordPos, swordCol.GetCollisionDimensions());
		}
		else if (Global::GAME.IsKeyPressed(KEY_DOWN))
		{
			SetAttackCoolDown(GetMaxCoolDown());
			Collision swordCol(0, 0, 30, 10);
			Vector2 swordPos(GetPostion().x, GetPostion().y + GetCollider()->GetCollisionDimensions()[HEIGHT]);

			foo = swordCol.FindGameObjectsColliding(swordPos, swordCol.GetCollisionDimensions());
		}
		else if (Global::GAME.IsKeyPressed(KEY_LEFT))
		{
			SetAttackCoolDown(GetMaxCoolDown());
			Collision swordCol(-10, 0, 10, 30);
			Vector2 swordPos(GetPostion().x, GetPostion().y);

			foo = swordCol.FindGameObjectsColliding(swordPos, swordCol.GetCollisionDimensions());
		}
		else if (Global::GAME.IsKeyPressed(KEY_RIGHT))
		{
			SetAttackCoolDown(GetMaxCoolDown());
			Collision swordCol(0, 0, 10, 30);
			Vector2 swordPos(GetPostion().x + GetCollider()->GetCollisionDimensions()[WIDTH], GetPostion().y);

			foo = swordCol.FindGameObjectsColliding(swordPos, swordCol.GetCollisionDimensions());
		}

		for (size_t i = 0; i < foo.size(); i++)
		{
			if (!foo[i]->IsColliderTrigger() && foo[i]->GetLevelSymbol() != DOOR && foo[i]->GetLevelSymbol() != EXIT)
			{
				foo[i]->SetActiveState(false);
			}
		}
	}
	else
	{
		SetAttackCoolDown(GetAttackCoolDown() - 1);
	}
}

void Player::Update()
{
	Global::GAME.GetRendererPtr()->CameraFollow(GetPostion());
	Move();
	Attack();
	HealthCheck();
}


