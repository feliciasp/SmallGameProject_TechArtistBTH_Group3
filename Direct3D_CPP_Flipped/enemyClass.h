#pragma once
#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#include "objectClass.h"

class enemyClass 
{
	public:
		enemyClass();
		enemyClass(const enemyClass& other);
		~enemyClass();

		bool initlialize(ID3D11Device* device, const char* filename);
		void shutdown();
		void setTranslation(float x);

		objectClass* getObj();
		void getTranslationMat(XMMATRIX& other);
		void getTranslationMatStart(XMMATRIX& other);
		void setStartMat(float x);

		float getMove();
		void setMove(float x);
		void resetMove();

		XMVECTOR getTriggerCheck();
		void updateFalling(double dt);
		void getFallingMat(XMMATRIX& other);

		void setTriggerVector(XMVECTOR x);
		XMVECTOR getTriggerVector();

		void resetEnemy();

		bool getCheckIfObjHolder();
		void setCheckIfObjHolder(bool other);

		void setIsActive(bool check);
		bool getIsActive();

		void setEnemyHP(int x);
		int getEnemyHP();

		bool hurtState();
		void timeCountdown();

		bool attackCooldown();
		void updateAttackCooldownTimer();
		
		void setFacing(bool other);
		bool getFacing();

		void setRoationCheck(bool other);
		bool getRoationCheck();

		void checkCollisions(bool top, bool left, bool right, bool bot);

		void setRangeVector(XMVECTOR x);
		XMVECTOR getRangeVector();

		bool getIfAttack();
		
		int getAttackCooldown();

		//VAPEN
		void setBboxMaxWeaponRight(XMVECTOR vector);
		void setBboxMinWeaponRight(XMVECTOR vector);

		XMVECTOR getBboxMaxWeaponRight();
		XMVECTOR getBboxMinWeaponRight();

		void setBboxMaxWeaponLeft(XMVECTOR vector);
		void setBboxMinWeaponLeft(XMVECTOR vector);

		XMVECTOR getBboxMaxWeaponLeft();
		XMVECTOR getBboxMinWeaponLeft();

		XMVECTOR getStartPos();
		int getHurt();

	private:
		objectClass* obj;
		bool isActive;
		bool checkIfObjHolder;

		float temptest;
		float moveVal;
		XMMATRIX translation;
		XMMATRIX transStart;
		XMMATRIX translationInY;

		XMVECTOR triggerVector;
		XMVECTOR triggerCheck;

		XMVECTOR rangeVector;
		XMVECTOR rangeCheck;

		XMVECTOR startPos;

		int HP;
		bool isHurt;
		bool isAttack;
		int fakeTimer;

		void setEnemyHurt(bool check);
		bool getEnemyHurt();

		bool isFacingRight;
		bool useRotation;

		float oldMoveValY;

		bool isHit;
		bool isAttacking;
		void checkIfAttacking();

		//VAPEN

		XMVECTOR bboxMaxLeft;
		XMVECTOR bboxMinLeft;

		XMVECTOR bboxMaxRight;
		XMVECTOR bboxMinRight;
		int tonsOfDmg;
		int hurt;
};


#endif
