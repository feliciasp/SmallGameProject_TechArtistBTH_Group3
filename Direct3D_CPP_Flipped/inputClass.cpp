#pragma once

#include "inputClass.h"

inputClass::inputClass()
{
}

inputClass::inputClass(const inputClass & other)
{
}

inputClass::~inputClass()
{
}

void inputClass::initialize()
{
	int i;
	//initialize all tha keys to being realeased and not pressed
	for (int i = 0; i < 256; i++)
	{
		keys[i] = false;
	}

	return;
}

bool inputClass::isKeyDown(unsigned int keyID)
{
	return keys[keyID];
}

void inputClass::keyDown(unsigned int keyID)
{
	//if key is pressed save that state in key array
	keys[keyID] = true;
	return;
}

void inputClass::keyUp(unsigned int keyID)
{
	//if key is realased then clar state
	keys[keyID] = false;
	return;
}
