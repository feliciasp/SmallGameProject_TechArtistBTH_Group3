#pragma once
#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#include "objectClass.h"
#include "playerClass.h"

class enemyClass 
{
	public:
		enemyClass();
		enemyClass(const enemyClass& other);
		~enemyClass();

		bool initlialize(ID3D11Device* device, const char* filename);
		void shutdown();

		objectClass* getObj();

		void getTranslationMatStart(XMMATRIX& other);
		void setStartMat(float x, float y);

		void getMoveMat(XMMATRIX other);
		void resetMove();

		XMVECTOR getTriggerCheck();

		void setTriggerVector(XMVECTOR x);
		XMVECTOR getTriggerVector();

		void resetEnemy();

		void handleMovement(double dt);

		bool getCheckIfObjHolder();
		void setCheckIfObjHolder(bool other);

		void setIsActive(bool check);
		bool getIsActive();

		void setEnemyHP(int x);
		int getEnemyHP();

		bool hurtState();
		void timeCountdown(double dt);
		
		void setFacing(bool other);
		bool getFacing();

		void setRotationCheck(bool other);
		bool getRotationCheck();

		void checkCollisions(bool top, bool left, bool right, bool bot);

		void setLengthBetween(float length1, float length2);

		void updateInteraction(playerClass player);

	private:

		objectClass* obj;
		bool isActive;
		bool checkIfObjHolder;

		float temptest;
		float moveVal;

		float moveValX;
		float moveValY;
		float moveValZ;

		XMMATRIX transStart;
		XMMATRIX translationInY;

		XMMATRIX moveMat;

		XMVECTOR triggerVector;
		XMVECTOR triggerCheck;

		int HP;
		bool isHurt;
		int hurtCooldown;

		void setEnemyHurt(bool check);
		bool getEnemyHurt();

		bool isFacingRight;
		bool useRotation;

		float oldMoveValY;
		float oldMoveValX;

		float upSpeed;

		float lengthBetween1;
		float lengthBetween2;
		
		float turningDelay;

		
};


#endif
