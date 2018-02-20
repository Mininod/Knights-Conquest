#include "GameObject.h"
#include "Global.h"
#include "Player.h"
#include "Collision.h"
#include "Bitmap.h"

GameObject::GameObject(std::string name, GameObjectSymbols symbol, Vector2 position)
{
	mName = name;
	mLevelSymbol = symbol;
	mPosition = position;
	mpBitmap = new Bitmap;
	SetActiveState(true);
}

GameObject::GameObject(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight) : GameObject(newName, symbol, position)
{
	
	mpBoxCollider = new Collision(colliderPosition.x, colliderPosition.y, collierWidthHeight.x, collierWidthHeight.y);
}

GameObject::~GameObject()
{
	if (mpBitmap)
	{
		delete mpBitmap;
		mpBitmap = nullptr;
	}

	if (mpBoxCollider)
	{
		delete mpBitmap;
		mpBoxCollider = nullptr;
	}
}

void GameObject::Debug()
{
	std::cout << "Name: " << GetName() << " | isActive: " << isActive() << " | Symbol: " << GetLevelSymbol() << " | Position: " << GetPostion().x << "," << GetPostion().y << std::endl;
	std::vector<float> foo = GetCollider()->GetCollisionDimensions();
	std::cout << "Collider Position: " << foo[X] << "," << foo[Y] << " | Collider Width: " << foo[WIDTH] << " | Collider Height: " << foo[HEIGHT] << std::endl;
}

bool GameObject::IsColliderTrigger()
{
	return mIsColliderTrigger;
}

std::string GameObject::GetName()
{
	return mName;
}

bool GameObject::isActive()
{
	return mIsActive;
}

void GameObject::SetActiveState(bool isActive)
{
	mIsActive = isActive;
}

void GameObject::Update()
{
	std::cout << "Error: '"  << GetName() << "' using GameObject Update. Should be using its own" << std::endl;
}


void GameObject::Draw()
{
	mpBitmap->DrawBitmap(mPosition);
}

Vector2 GameObject::GetPostion()
{
	return mPosition;
}

Collision * GameObject::GetCollider()
{
	return mpBoxCollider;
}

char GameObject::GetLevelSymbol()
{
	return mLevelSymbol;
}

void GameObject::SetPostion(Vector2 pos)
{
	mPosition = pos;
}

Bitmap * GameObject::GetBitmap()
{
	return mpBitmap;
}

void GameObject::Start()
{
	std::cout << "Error: No 'Start' implmented for object '" << GetName() << "'" << std::endl;
}

void GameObject::SetIsColliderTrigger(bool foo)
{
	mIsColliderTrigger = foo;
}
