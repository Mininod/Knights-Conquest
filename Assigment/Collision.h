#pragma once
#include <vector>
#include "Vector2.h"

class GameObject;

enum coords // to make it easier to know what is what
{
	X, Y, WIDTH, HEIGHT
};

enum Direction
{
	Direction_UP, Direction_LEFT, Direction_RIGHT, Direction_DOWN
};

class Collision
{
public:
	Collision(float x, float y, float width, float height);
	~Collision();
	bool IsColliding(Vector2 objectAPos, std::vector<float> objectAColDim, Vector2 objectBPos, std::vector<float> objectBColDim);
	std::vector<float> GetCollisionDimensions();
	void SetCollisionDimensions(float x, float y, float width, float height); //Vector set up as follows: 0 = X, 1 = Y, 2 = Width, 3 = Height
	bool IsWall(Vector2 pos);
	std::vector<GameObject*> FindGameObjectsColliding(Vector2 position, std::vector<float> colDim);
	float GetDistanceBetweenTwoPoints(Vector2 posA, Vector2 posB);
	bool IsSpaceFree(Vector2 pos, std::vector<float> colliderDimentions, float moveAmount, Direction moveDirection);
	bool IsCollidingWithAnyGameObjects(Vector2 pos, std::vector<float> colliderDimentions);
private:
	std::vector<float> mDimensions;
};

