#include "deltaTimeClass.h"

deltatime::deltatime()
{
	/*deltaInMili = 0;*/
	t = 0.0;
	dt = 1 / 60.0;
	deltaTime = 0;
	currentTime = timeGetTime() / 1000.0;
	newTime = 0;
	frameTime = 0;
}

deltatime::deltatime(deltatime & other)
{
}

deltatime::~deltatime()
{
}

void deltatime::setDeltaTime()
{
	/*QueryPerformanceFrequency(&clockFreq);
	QueryPerformanceCounter(&startTime);*/


}

void deltatime::updateDeltaTime()
{
	/*QueryPerformanceCounter(&endTime);
	delta.QuadPart = endTime.QuadPart - startTime.QuadPart;

	deltaInMili = (float)delta.QuadPart / clockFreq.QuadPart;*/
	newTime = timeGetTime() / 1000.0;
	frameTime = newTime - currentTime;
	currentTime = newTime;


}

float deltatime::getDeltaTime()
{
	/*return this->deltaInMili;*/

	t += frameTime;

	return frameTime;

}