#pragma once
#ifndef BACKGROUNDPLANECLASS_H
#define BACKGROUNDPLANECLASS_H

#include "objectClass.h"

class backgroundClass
{
public:
	backgroundClass();
	backgroundClass(const backgroundClass& other);
	~backgroundClass();

	bool initlialize(ID3D11Device* device, const char* filename);
	void shutdown();

	objectClass* getObj();

private:
	objectClass* obj;

};


#endif