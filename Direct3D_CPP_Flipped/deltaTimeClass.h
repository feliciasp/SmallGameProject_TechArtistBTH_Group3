#pragma once
#ifndef DELTATIMECLASS_H
#define DELTATIMECLASS_H

#include <Windows.h>
#include <DirectXMath.h>
#include <chrono>


class deltatime
{
public:
	deltatime();
	deltatime(deltatime& other);
	~deltatime();

	void updateDeltaTime();

	float getDeltaTime();

private:
	double newTime;
	double frameTime;

	double currentTime;
	double totalElapsedTime;
};

#endif
