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

		void getTranslationMatStart(XMMATRIX& other);
		void setStartMat(float x);

		float getMove();
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
		void timeCountdown();
		
		void setFacing(bool other);
		bool getFacing();

		void setRoationCheck(bool other);
		bool getRoationCheck();

		void checkCollisions(bool top, bool left, bool right, bool bot);


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
		int fakeTimer;

		void setEnemyHurt(bool check);
		bool getEnemyHurt();

		bool isFacingRight;
		bool useRotation;

		float oldMoveValY;
		float oldMoveValX;

		float upSpeed;
		
};


#endif
