#pragma once
#ifndef DELTATIMECLASS_H
#define DELTATIMECLASS_H

#include <Windows.h>
#include <DirectXMath.h>

class deltatime
{
public:
	deltatime();
	deltatime(deltatime& other);
	~deltatime();

	void setDeltaTime();
	void updateDeltaTime();

	float getDeltaTime();

private:
	/*LARGE_INTEGER delta;
	LARGE_INTEGER clockFreq;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	float deltaInMili;*/

	double t;
	double dt;
	float deltaTime;
	double newTime;
	double frameTime;

	double currentTime;
};

#endif
