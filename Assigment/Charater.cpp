#include "Charater.h"

Charater::Charater(std::string name, GameObjectSymbols Symbol, Vector2 position) : GameObject(name, Symbol, position)
{
}

Charater::Charater(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight) : GameObject(newName, symbol, position, colliderPosition , collierWidthHeight)
{
}

Charater::~Charater()
{
}

void Charater::Move()
{
	std::cout << "No implmentation of Move for '" << GetName() << "'" << std::endl;
}

void Charater::Attack()
{
	std::cout << "No implmentation of Attack for '" << GetName() << "'" << std::endl;
}

float Charater::GetMoveSpeed()
{
	return mMoveSpeed;
}

void Charater::SetMoveSpeed(float speed)
{
	mMoveSpeed = speed;
}

float Charater::GetMaxHealth()
{
	return mMaxHealth;
}

void Charater::SetMaxHealth(float maxHealth)
{
	mMaxHealth = maxHealth;
}

float Charater::GetHealth()
{
	return mHealth;
}

void Charater::SetHealth(float health)
{
	mHealth = health;
}

float Charater::GetAttackDamage()
{
	return mAttackDamage;
}

void Charater::SetAttackDamage(float attackDamage)
{
	mAttackDamage = attackDamage;
}

bool Charater::IsSafeSpace(Direction directon)
{
	bool output = GetCollider()->IsSpaceFree(GetPostion(), GetCollider()->GetCollisionDimensions(), GetMoveSpeed(), directon);
	return output;
}

int Charater::GetAttackCoolDown()
{
	return mAttackCoolDown;
}

void Charater::SetAttackCoolDown(int coolDown)
{
	mAttackCoolDown = coolDown;
}

int Charater::GetMaxCoolDown()
{
	return mMaxCoolDown;
}

void Charater::SetMaxCoolDown(int maxCoolDown)
{
	mMaxCoolDown = maxCoolDown;
}
