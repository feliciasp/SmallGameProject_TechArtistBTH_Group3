#include "directInputClass.h"

directInput::directInput()
{
	directInputOther = 0;
	keyboard = 0;
}

directInput::directInput(const directInput & other)
{

}

directInput::~directInput()
{
}

bool directInput::initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result;

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

	return true;
}

bool directInput::isEscapePressed()
{

	if (keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}
	return false;
}

bool directInput::isSpacePressed()
{
	if (keyboardState[DIK_SPACE] & 0x80)
	{
		return true;
	}
	return false;
}

bool directInput::isAPressed()
{
	if (keyboardState[DIK_A] & 0x80)
	{
		return true;
	}
	return false;
}

bool directInput::isDPressed()
{
	if (keyboardState[DIK_D] & 0x80)
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
	if (keyboardState[DIK_O] & 0x80)
	{
		return true;
	}
	return false;
}

bool directInput::isOPressed()
{
	if (keyboardState[DIK_O] & 0x80)
	{
		return true;
	}
	return false;
}

bool directInput::isArrowRightPressed()
{
	if (keyboardState[DIK_RIGHTARROW] & 0x80)
	{
		return true;
	}
	return false;
}
bool directInput::isArrowLeftPressed()
{
	if (keyboardState[DIK_LEFTARROW] & 0x80)
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
		MessageBox(NULL, L"Error reading kayboard",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}
