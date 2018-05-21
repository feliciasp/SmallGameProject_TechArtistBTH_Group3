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
		void clone(const enemyClass& other, float x, float y);

		bool initlialize(ID3D11Device* device, const char* filename);
		void shutdown();
		void setTranslation(float x);

		objectClass* getObj();
		void getTranslationMat(XMMATRIX& other);
		void getTranslationMatStart(XMMATRIX& other);
		void setStartMat(float x, float y);

		float getMove();
		void setMove(float x);
		void resetMove();

		/*bool getCollidingX();*/

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
		void timeCountdown(float dt);

		bool attackCooldown();
		void updateAttackCooldownTimer(float dt);
		
		void setFacing(bool other);
		bool getFacing();

		void setRoationCheck(bool other);
		bool getRoationCheck();

		void checkCollisionsY(bool top, bool bot);
		void checkCollisionsX(bool left, bool right);

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

		void getMasterMovementEnemy(XMMATRIX &other);
		void setMasterMovementEnemy(XMMATRIX & other);

		void getEnemyTranslationMatrix(XMMATRIX &other);
		void setEnemyTranslationMatrix(XMMATRIX & other);

	private:
		objectClass* obj;
		bool isActive;
		bool checkIfObjHolder;

		float temptest;
		float moveVal;

		
		XMMATRIX translation;
		XMMATRIX transStart;
		//ENEMY FALLING MAT
		XMMATRIX translationInY;
		XMMATRIX masterMoveMat;
		XMMATRIX tranlsationInXMatrix;

		XMVECTOR triggerVector;
		XMVECTOR triggerCheck;

		XMVECTOR rangeVector;
		XMVECTOR rangeCheck;

		XMVECTOR startPos;

		int HP;
		bool isHurt;
		bool isAttack;
		float attackTimer;

		float hurtTimer;

		void setEnemyHurt(bool check);
		bool getEnemyHurt();

		bool isFacingRight;
		bool useRotation;

		float oldMoveValY;

		bool isHit;
		bool isAttacking;
		void checkIfAttacking();

		bool collidingRight;
		bool collidingLeft;
		//VAPEN

		XMVECTOR bboxMaxLeft;
		XMVECTOR bboxMinLeft;

		XMVECTOR bboxMaxRight;
		XMVECTOR bboxMinRight;
		int tonsOfDmg;
		int hurt;

		//NEW SHIT

};


#endif
