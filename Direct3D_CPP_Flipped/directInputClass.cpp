#include "directInputClass.h"

directInput::directInput()
{
	directInputOther = 0;
	keyboard = 0;
	mouse = 0;
	gamepadIndex = 0;
	deadzoneX = 0.1f;
	deadzoneY = 0.1f;
	leftStickX = 0.0f;
	leftStickY = 0.0f;

	rightStickX = 0.0f;
	rightStickY = 0.0f;
}

directInput::directInput(const directInput & other)
{

}

directInput::~directInput()
{
}

bool directInput::initialize(HINSTANCE hInstance, HWND hwnd, int widthS, int heightS)
{
	HRESULT result;

	//use for positioning the mouse
	width = widthS;
	height = heightS;

	// Initialize mouse location
	mouseX = 0;
	mouseY = 0;

	//init main direct input interface
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInputOther, NULL);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error init main driect input interface",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//create device
	result = directInputOther->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error create keyboard obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;

	}
	//set data format
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error set data format keyboard",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//set if you want you keypressed to be registered only from you app or other too
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error set coop lvls keyboard",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//get acces to kayboard
	result = keyboard->Acquire();
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error acc keyboard",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	////MOUSE
	result = directInputOther->CreateDevice(GUID_SysMouse, &mouse, NULL);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error init mouse",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	// Set the data format
	result = mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error set mouse data",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	// set coop
	result = mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error setting coop",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	// get mouse
	result = mouse->Acquire();
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error getting mouse",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void directInput::shutdown()
{
	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = 0;
	}
	if (directInputOther)
	{
		directInputOther->Release();
		directInputOther = 0;
	}
	if (mouse)
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = 0;
	}

}

bool directInput::frame(double dt)
{
	bool result;
	//read current state of keyboard
	result = readKeyboard(dt);
	if (!result)
	{
		MessageBox(NULL, L"Error reading keyboard",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//read current state of mouse
	result = readMouse();
	if (!result)
	{
		MessageBox(NULL, L"Error reading mouse",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	result = readGamepad();
	
	/*if (!result)
	{
		MessageBox(NULL, L"Error reading gamePad",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}*/

	return true;
}

bool directInput::isEscapePressed()
{

	if (keyboardState[DIK_ESCAPE] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isSpacePressed()
{
	if (keyboardState[DIK_SPACE] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isAPressed()
{
	if (keyboardState[DIK_A] & 0x80 || (leftStickX < -0.5f))
	{
		return true;
	}
	return false;
}

bool directInput::isDPressed()
{
	if (keyboardState[DIK_D] & 0x80 || (leftStickX > 0.5f))
	{
		return true;
	}
	return false;
}

bool directInput::isTPressed()
{
	if (keyboardState[DIK_T] & 0x80)
	{
		return true;
	}
	return false;
}

bool directInput::isEnterPressed()
{
	if (keyboardState[DIK_RETURN] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isOPressed()
{
	if (keyboardState[DIK_O] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isArrowRightPressed()
{
	if (keyboardState[DIK_RIGHTARROW] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isArrowLeftPressed()
{
	if (keyboardState[DIK_LEFTARROW] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isWPressed()
{
	if (keyboardState[DIK_W] & 0x80 || (leftStickY > 0.5f))
	{
		return true;
	}
	return false;
}

bool directInput::isArrowUpPressed()
{
	if (keyboardState[DIK_UPARROW] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isArrowDownPressed()
{
	if (keyboardState[DIK_DOWNARROW] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isPPressed()
{
	if (keyboardState[DIK_P] & 0x80 || ((state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0))
	{
		return true;
	}
	return false;
}

bool directInput::isEPressed()
{
	if (keyboardState[DIK_E] & 0x80 || (leftTrigger > 0.8f) || (rightTrigger > 0.8f))
	{
		return true;
	}
	return false;
}



//player->handleMovement(player - ZgetObj()->getInput());
//
//handeMovement(moveObj)
//{
//	if (moveObj->checkSpace())
//	{
//		do this;
//	}
//	if(moveObj->checkD())
//}

//void directInput::isMovementPressed(double dt, bool collisionCheck)
//{
//	keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
//
//	if (keyboardState[DIK_D] & 0x80)
//	{
//		moveValX += 10.0f * dt;
//		OutputDebugString(L"func move right called");
//	}
//	if (keyboardState[DIK_A] & 0x80)
//	{
//		moveValX += -10.0f * dt;
//		OutputDebugString(L"func move left called");
//	}
//	if (keyboardState[DIK_SPACE] & 0x80)
//	{
//		if (!isJumping)
//		{
//			upSpeed = 30.5f;
//			OutputDebugString(L"upSpeed set");
//		}
//		isJumping = true;
//	}
//
//	moveValY += upSpeed * dt;
//
//	if (!collisionCheck && upSpeed > -1.0f)
//	{
//		upSpeed += -0.1 - moveValY * dt;
//		
//	}
//	else if (!collisionCheck > 0)
//	{
//		upSpeed += -0.1 - -upSpeed * dt;
//	}
//	else
//	{
//		upSpeed = 0.0f;
//		isJumping = false;
//	}
//	
//}

//float directInput::getMoveValX()
//{
//	return this->moveValX;
//}
//float directInput::getMoveValY()
//{
//	return this->moveValY;
//}
//float directInput::getMoveValZ()
//{
//	return this->moveValZ;
//}
//
//void directInput::getMoveMat(XMMATRIX& mat)
//{
//	mat = moveMatInputClass;
//}
//
//void directInput::setMoveMat(float x, float y)
//{
//	moveMatInputClass = XMMatrixTranslation(x, y, 0.0f);
//}
//void directInput::setMoveMatEnemy( float y)
//{
//	moveMatInputClass = XMMatrixTranslation(0.0f, y, 0.0f);
//}
//
//void directInput::updateFalling()
//{
//	
//}


bool directInput::readKeyboard(double dt)
{
	HRESULT result;
	//read keyboard device
	result = keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard->Acquire();
		}
		else
		{
			MessageBox(NULL, L"could not get keyboard back",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}

	return true;
}


bool directInput::readMouse()
{
	HRESULT result;
	// Read the mouse device.
	result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	if (FAILED(result))
	{
		//if mouse focus was lost get it back
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mouse->Acquire();
		}
		else
		{
			MessageBox(NULL, L"could not get mouse back",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}

	return true;
}

void directInput::processInput()
{
	// Update mouse location from frame
	mouseX += mouseState.lX;
	mouseY += mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (mouseX < 0)
	{
		mouseX = 0; 
	}
	if (mouseY < 0) 
	{ 
		mouseY = 0; 
	}

	if (mouseX > width) 
	{
		mouseX = width; 
	}
	if (mouseY > height) 
	{ 
		mouseY = height; 
	}

}

XINPUT_GAMEPAD * directInput::getState()
{
	return &state.Gamepad;
}

bool directInput::checkConnection()
{
	XINPUT_STATE tState;
	ZeroMemory(&tState, sizeof(XINPUT_STATE));
	if (XInputGetState(0, &tState) == ERROR_SUCCESS)
	{
		return true;
	}
	
	
	return false;
}

bool directInput::readGamepad()
{
	
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	if (XInputGetState(0, &state) != ERROR_SUCCESS)
	{
		return false;
	}
	leftTrigger = float(state.Gamepad.bLeftTrigger) / 255;
	rightTrigger = float(state.Gamepad.bRightTrigger) / 255;

	//Left Thumbstick
	float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
	float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

	leftStickX = (fabs(normLX) < deadzoneX ? 0 : (fabs(normLX) - deadzoneX) * (normLX / fabs(normLX)));
	leftStickY = (fabs(normLY) < deadzoneY ? 0 : (fabs(normLY) - deadzoneY) * (normLY / fabs(normLY)));

	if (deadzoneX > 0)
	{
		leftStickX *= 1 / (1 - deadzoneX);
	}

	if (deadzoneY > 0)
	{
		leftStickY *= 1 / (1 - deadzoneY);
	}

	//Right ThumbStick

	float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
	float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

	rightStickX = (fabs(normRX) < deadzoneX ? 0 : (fabs(normRX) - deadzoneX) * (normRX / fabs(normRX)));
	rightStickY = (fabs(normRY) < deadzoneY ? 0 : (fabs(normRY) - deadzoneY) * (normRY / fabs(normRY)));

	if (deadzoneX > 0)
	{
		rightStickX *= 1 / (1 - deadzoneX);
	}

	if (deadzoneY > 0)
	{
		rightStickY *= 1 / (1 - deadzoneY);
	}

	return true;
}
