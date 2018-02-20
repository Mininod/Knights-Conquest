#include "Collision.h"
#include "Global.h"
#include "GameObject.h"

Collision::Collision(float x, float y, float width, float height)
{
	SetCollisionDimensions(x, y, width, height);
}

Collision::~Collision()
{
}

bool Collision::IsColliding(Vector2 objectAPos, std::vector<float> objectAColDim, Vector2 objectBPos, std::vector<float> objectBColDim)
{
	std::vector<float> objectA = objectAColDim;
	objectA[X] += objectAPos.x;
	objectA[Y] += objectAPos.y;
	std::vector<float> objectB = objectBColDim;
	objectB[X] += objectBPos.x;
	objectB[Y] += objectBPos.y;

	if (objectA[X] < objectB[X] + objectB[WIDTH] && objectA[X] + objectA[WIDTH] > objectB[X])
	{
		if (objectA[Y] < objectB[Y] + objectB[HEIGHT] && objectA[Y] + objectA[HEIGHT] > objectB[Y])
		{
			return true;
		}
	}

	return false;
}

std::vector<float> Collision::GetCollisionDimensions()
{
	return mDimensions;
}

void Collision::SetCollisionDimensions(float x, float y, float width, float height)
{
	mDimensions.push_back(x);
	mDimensions.push_back(y);
	mDimensions.push_back(width);
	mDimensions.push_back(height);
}

bool Collision::IsWall(Vector2 pos)
{
	int blocksize = Global::GAME.GetBlockSize();
	std::vector<std::string> levelInfo = Global::GAME.GetLevelInfo();
	int x = (int) floor(pos.x / blocksize);
	int y = (int) floor(pos.y / blocksize);

	if (levelInfo[y + 1][x] == 'W')
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<GameObject*> Collision::FindGameObjectsColliding(Vector2 position, std::vector<float> colDim)
{
	std::vector<GameObject*> allGameObjects = Global::GAME.GetAllGameObjects();
	std::vector<GameObject*> collidingObjects;
	for (size_t i = 0; i < allGameObjects.size(); i++)
	{
		if (GetDistanceBetweenTwoPoints(position, allGameObjects[i]->GetPostion()) < 50)
		{
			if (allGameObjects[i]->GetLevelSymbol() != WALL && allGameObjects[i]->GetLevelSymbol() != FLOOR)
			{
				if (IsColliding(position, colDim, allGameObjects[i]->GetPostion(), allGameObjects[i]->GetCollider()->GetCollisionDimensions()))
				{
					collidingObjects.push_back(allGameObjects[i]);
				}
			}
		}
	}
	return collidingObjects;
}

float Collision::GetDistanceBetweenTwoPoints(Vector2 posA, Vector2 posB)
{
	Vector2 finalPos;
	finalPos.x = abs(posA.x - posB.x);
	finalPos.y = abs(posA.y - posB.y);

	float result = sqrt((finalPos.x * 2) + (finalPos.y * 2));

	return result;
}

bool Collision::IsSpaceFree(Vector2 pos, std::vector<float> colliderDimentions, float moveAmount, Direction direction)
{
	Vector2 newPos = pos;
	float speed = moveAmount;
	std::vector<float> colDim = colliderDimentions;
	colDim[0] += newPos.x;
	colDim[1] += newPos.y;
	colDim[2]--;
	colDim[3]--;

	if (direction == Direction_UP && !IsWall(Vector2(colDim[0], colDim[1] - speed)) && !IsWall(Vector2(colDim[0] + colDim[2], colDim[1] - speed)) && !IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X], colliderDimentions[Y] - speed, colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
	{
		return true;
	}
	else if (direction == Direction_LEFT && !IsWall(Vector2(colDim[0] - speed, colDim[1])) && !IsWall(Vector2(colDim[0] - speed, colDim[1] + colDim[3])) && !IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X] - speed, colliderDimentions[Y], colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
	{
		return true;
	}
	else if (direction == Direction_DOWN && !IsWall(Vector2(colDim[0], colDim[1] + colDim[3] + speed)) && !IsWall(Vector2(colDim[0] + colDim[2], colDim[1] + colDim[3] + speed)) && !IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X], colliderDimentions[Y] + speed, colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
	{
		return true;
	}
	else if (direction == Direction_RIGHT && !IsWall(Vector2(colDim[0] + colDim[2] + speed, colDim[1] + colDim[3])) && !IsWall(Vector2(colDim[0] + colDim[2] + speed, colDim[1])) && !IsCollidingWithAnyGameObjects(pos, std::vector<float>{colliderDimentions[X] + speed, colliderDimentions[Y], colliderDimentions[WIDTH], colliderDimentions[HEIGHT]}))
	{
		return true;
	}
	return false;
}

bool Collision::IsCollidingWithAnyGameObjects(Vector2 pos, std::vector<float> colliderDimentions)
{
	std::vector<GameObject*> allGameObjects = Global::GAME.GetAllGameObjects();
	bool CollidedOnce = false;
	for (size_t i = 0; i < allGameObjects.size(); i++)
	{
		if (allGameObjects[i]->GetLevelSymbol() != FLOOR && allGameObjects[i]->isActive() && !allGameObjects[i]->IsColliderTrigger())
		{
			if (GetDistanceBetweenTwoPoints(allGameObjects[i]->GetPostion(), pos) < 64, IsColliding(pos, colliderDimentions, allGameObjects[i]->GetPostion(), allGameObjects[i]->GetCollider()->GetCollisionDimensions()))
			{
				if (CollidedOnce == true) // This is done because every gameobject will collide with itself first as it will be part of "allGameObjects"
				{
					return true;
				}
				else
				{
					CollidedOnce = true;
				}
			}
		}
	}
	return false;
}

