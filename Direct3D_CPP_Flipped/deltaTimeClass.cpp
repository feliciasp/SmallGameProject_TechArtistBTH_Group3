#include "deltaTimeClass.h"




deltatime::deltatime()
{
	newTime = 0;
	frameTime = 0;

	auto startTime = std::chrono::high_resolution_clock::now();
	auto msTime = std::chrono::time_point_cast<std::chrono::milliseconds>(startTime);
	auto epoch = msTime.time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

	currentTime = time.count();

	totalElapsedTime = 0;
}

deltatime::deltatime(deltatime & other)
{
}

deltatime::~deltatime()
{
}


void deltatime::updateDeltaTime()
{
	

	auto startTime = std::chrono::high_resolution_clock::now();
	auto msTime = std::chrono::time_point_cast<std::chrono::milliseconds>(startTime);
	auto epoch = msTime.time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);

	double newTime = time.count();
	frameTime = newTime - currentTime;
	currentTime = newTime;

	totalElapsedTime += frameTime / 1000.0;
}

float deltatime::getDeltaTime()
{

	return frameTime / 1000.0;

}