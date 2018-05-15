#pragma once

#ifndef DIRECTINPUTCLASS_H
#define DIRECTINPUTCLASS_H
#include <d3d11.h>
#include <directxmath.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <dinput.h>

using namespace DirectX;

class directInput 
{
	public:
		directInput();
		directInput(const directInput& other);
		~directInput();

		bool initialize(HINSTANCE hInstance, HWND hwnd, int w, int h);
		void shutdown();
		bool frame(double dt);

		bool isEscapePressed();
		bool isSpacePressed();
		bool isDPressed();
		bool isAPressed();
		bool isTPressed();
		bool isEnterPressed();
		bool isOPressed();
		bool isPPressed();
		bool isArrowRightPressed();
		bool isArrowLeftPressed();

		bool isArrowUpPressed();
		bool isArrowDownPressed();

		bool isEPressed();

		bool readKeyboard(double dt);
		bool readMouse();
		void processInput();

	private:
		IDirectInput8 * directInputOther;
		IDirectInputDevice8* keyboard;
		IDirectInputDevice8* mouse;
		unsigned char keyboardState[256];
		DIMOUSESTATE mouseState;

		int width;
		int height;
		int mouseX;
		int mouseY;


};

#endif