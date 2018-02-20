#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Collision.h"

class Charater : public GameObject
{
public:
	Charater(std::string name, GameObjectSymbols Symbol, Vector2 position);
	Charater(std::string newName, GameObjectSymbols symbol, Vector2 position, Vector2 colliderPosition, Vector2 collierWidthHeight);
	~Charater();

	float GetHealth();
	float GetMaxHealth();
	float GetAttackDamage();
	float GetMoveSpeed();
	void SetHealth(float health);
	int GetAttackCoolDown();
protected:
	virtual void Move();
	virtual void Attack();
	void SetMoveSpeed(float speed);
	void SetMaxHealth(float maxHealth);
	void SetAttackDamage(float attackDamage);
	bool IsSafeSpace(Direction directon);
	void SetAttackCoolDown(int coolDown);
	int GetMaxCoolDown();
	void SetMaxCoolDown(int maxCoolDown);
private:
	float mMoveSpeed;
	float mMaxHealth;
	float mHealth;
	float mAttackDamage;
	int mAttackCoolDown;
	int mMaxCoolDown;
};


