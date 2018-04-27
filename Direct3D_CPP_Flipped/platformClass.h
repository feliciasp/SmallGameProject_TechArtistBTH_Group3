#pragma once
#ifndef PLATFORMCLASS_H
#define PLATFORMCLASS_H

#include "objectClass.h"

class platformClass
{
public:
	platformClass();
	platformClass(const platformClass& other);
	~platformClass();

	bool initlialize(ID3D11Device* device, const char* filename);
	void shutdown();

	objectClass* getObj();
	int getMeshCount();

private:
	objectClass * obj;
};


#endif