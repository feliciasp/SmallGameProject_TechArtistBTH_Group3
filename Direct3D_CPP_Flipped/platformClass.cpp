#include "platformClass.h"

platformClass::platformClass()
{
	obj = 0;
}


platformClass::platformClass(const platformClass & other)
{
}

platformClass::~platformClass()
{
}

bool platformClass::initlialize(ID3D11Device * device, const char* filename)
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
	return true;
}

void platformClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
}

///testestestet

objectClass * platformClass::getObj()
{
	return this->obj;
}

int platformClass::getMeshCount()
{
	return this->obj->getMeshCount();
}
