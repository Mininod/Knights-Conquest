#include "Enemy.h"
#include "Global.h"
#include "Player.h"
#include "Collision.h"

Enemy::Enemy(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight) : Charater(newName, symbol, position, colliderPosition, collierWidthHeight)
{
	Start();
}


Enemy::~Enemy()
{
}

void Enemy::Start()
{
	switch (GetLevelSymbol())
	{
	case BAT:
		GetBitmap()->CreateBitmap("Assets/Bat.bmp", true, 3);
		SetMoveSpeed(1);
		SetMaxCoolDown(50);
		break;
	case SLUG:
		GetBitmap()->CreateBitmap("Assets/Slime.bmp", true, 3);
		SetMoveSpeed(0.5f);
		SetMaxCoolDown(50);
		break;
	default:
		break;
	}

	SetIsColliderTrigger(false);
}

void Enemy::Update()
{
	Move();
	Attack();
}

void Enemy::Move()
{
	if (GetLevelSymbol() == BAT)
	{
		Vector2 pos = GetPostion();
		float speed = GetMoveSpeed();
		Vector2 playerPos = Global::GAME.GetPlayer()->GetPostion();
		std::vector<float> colliderDimentions = GetCollider()->GetCollisionDimensions();
		//Up
		if (playerPos.y  < pos.y && !GetCollider()->IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X], colliderDimentions[Y] - speed, colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
		{
			pos.y -= speed;
		}
		//Left
		if (playerPos.x < pos.x && !GetCollider()->IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X] - speed, colliderDimentions[Y], colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
		{
			pos.x -= speed;
		}
		//Down
		if (playerPos.y  > pos.y && !GetCollider()->IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X], colliderDimentions[Y] + speed, colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
		{
			pos.y += speed;
		}
		//Right
		if (playerPos.x > pos.x && !GetCollider()->IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X] + speed, colliderDimentions[Y], colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
		{
			pos.x += speed;
		}
		SetPostion(pos);
	}
	else if(GetLevelSymbol() == SLUG)
	{
		Vector2 pos = GetPostion();
		float speed = GetMoveSpeed();
		Vector2 playerPos = Global::GAME.GetPlayer()->GetPostion();
		//Up
		if (playerPos.y  < pos.y && IsSafeSpace(Direction_UP))
		{
			pos.y -= speed;
		}
		//Left
		if (playerPos.x < pos.x && IsSafeSpace(Direction_LEFT))
		{
			pos.x -= speed;
		}
		//Down
		if (playerPos.y  > pos.y && IsSafeSpace(Direction_DOWN))
		{
			pos.y += speed;
		}
		//Right
		if (playerPos.x > pos.x && IsSafeSpace(Direction_RIGHT))
		{
			pos.x += speed;
		}
		SetPostion(pos);
	}
}

void Enemy::Attack()
{
	if (GetAttackCoolDown() <= 0)
	{
		SetAttackCoolDown(GetMaxCoolDown());
		Vector2 pos = GetPostion();
		pos.x -= 5;
		pos.y -= 5;
		std::vector<float> colDim = GetCollider()->GetCollisionDimensions();
		colDim[WIDTH] += 10;
		colDim[HEIGHT] += 10;
		std::vector<GameObject*> colGameObjects = GetCollider()->FindGameObjectsColliding(pos, colDim);
		for (size_t i = 0; i < colGameObjects.size(); i++)
		{
			if (colGameObjects[i]->GetLevelSymbol() == PLAYER)
			{
				float hp = Global::GAME.GetPlayer()->GetHealth();
				hp--;
				Global::GAME.GetPlayer()->SetHealth(hp);
				std::cout << "Hit" << std::endl;
			}
		}
	}
	else
	{
		SetAttackCoolDown(GetAttackCoolDown() - 1);
	}
}
