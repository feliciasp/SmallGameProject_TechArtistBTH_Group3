#include "GUItest.h"

GUItestClass::GUItestClass()
{
	obj = 0;
	input = 0;
	isDestroy = false;
	checkIfSetToObjHolder = false;
	checkIfKeyStateWasTrueLastFrame = false;
	fakeTimer = 0;
	fakeTimer2 = 0;
	isBought = false;
}
void GUItestClass::resetGUI()
{
	isDestroy = false;
	checkIfSetToObjHolder = false;
	checkIfKeyStateWasTrueLastFrame = false;
	fakeTimer = 0;
	fakeTimer2 = 0;
}

void GUItestClass::updateDestroy2(double dt)
{
	input->readKeyboard(dt);
	if (this->input->isEnterPressed() && fakeTimer2 <= 0)
	{
		fakeTimer2 = 200;
		if (this->isDestroy == true)
		{
			this->isDestroy = false;
		}
	}
	else
	{
		fakeTimer2 -= 1;
	}
}

void GUItestClass::setIsBought(bool check)
{
	this->isBought = check;
}

bool GUItestClass::getIsBought()
{
	return this->isBought;
}

void GUItestClass::clone(GUItestClass & other)
{
	obj = new objectClass;
	obj->clone(*other.obj);
	obj->setType(1);
	
}


GUItestClass::GUItestClass(const GUItestClass & other)
{

}

GUItestClass::~GUItestClass()
{
}

bool GUItestClass::initlialize(ID3D11Device * device, const char* filename, HINSTANCE hInstance, HWND hwnd, int width, int height)
{
	HRESULT result;
	obj = new objectClass;

	if (!obj)
	{
		MessageBox(NULL, L"Error create bakcground obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = obj->initlialize(device, filename);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	obj->setType(1);

	input = new directInput;
	if (!input)
	{
		MessageBox(NULL, L"Error create object obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = input->initialize(hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void GUItestClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
	if (input)
	{
		input->shutdown();
		delete input;
		input = 0;
	}
}

bool GUItestClass::getIsDestry()
{
	return this->isDestroy;
}

void GUItestClass::setIsDestroy(bool check)
{
	this->isDestroy = check;
}

bool GUItestClass::updateDestroyState(double dt)
{
	bool check = false;
	input->readKeyboard(dt);

	if (this->input->isEnterPressed() && fakeTimer <= 0)
	{
		fakeTimer = 100;
		if (this->isDestroy == true)
		{
			this->isDestroy = false;
			check = true;
		}
	}
	else
	{
		fakeTimer -= 1;
	}
	return check;
}

bool GUItestClass::getCheckIfObjHolder()
{
	return this->checkIfSetToObjHolder;
}

void GUItestClass::setCheckIfObjHolder(bool check)
{
	this->checkIfSetToObjHolder = check;
}

objectClass * GUItestClass::getObj()
{
	return this->obj;
}
