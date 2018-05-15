#pragma once
#ifndef GUITEST_H
#define GUITEST_H

#include "objectClass.h"

class GUItestClass
{
public:
	GUItestClass();
	GUItestClass(const GUItestClass& other);
	~GUItestClass();



	bool initlialize(ID3D11Device* device, const char* filename, HINSTANCE hInstance, HWND hwnd, int width, int height);
	void shutdown();

	bool getIsDestry();
	void setIsDestroy(bool check);

	bool updateDestroyState(double dt);

	bool getCheckIfObjHolder();
	void setCheckIfObjHolder(bool check);

	objectClass* getObj();

	void resetGUI();

	void updateDestroy2(double dt);

	void setIsBought(bool check);
	bool getIsBought();

	void clone(GUItestClass& other);
private:
	objectClass* obj;
	directInput* input;
	bool isDestroy;

	bool checkIfSetToObjHolder;
	bool checkIfKeyStateWasTrueLastFrame;
	int fakeTimer;
	int fakeTimer2;

	bool isBought;

};


#endif