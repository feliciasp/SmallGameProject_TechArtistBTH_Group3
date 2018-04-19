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
		void updateFalling(objectClass* platform, float dt, bool checkCollision);
		void getFallingMat(XMMATRIX& other);

		void setTriggerVector(XMVECTOR x);
		XMVECTOR getTriggerVector();

		void resetEnemy();

	private:
		objectClass* obj;

		float temptest;
		float moveVal;
		XMMATRIX translation;
		XMMATRIX transStart;
		XMMATRIX translationInY;

		XMVECTOR triggerVector;
		XMVECTOR triggerCheck;

};


#endif
