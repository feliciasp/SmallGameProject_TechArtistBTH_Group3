#include "backgroundPlaneClass.h"

backgroundClass::backgroundClass()
{
	obj = 0;
	isInObjHolder = false;
}

backgroundClass::backgroundClass(const backgroundClass & other)
{
}

backgroundClass::~backgroundClass()
{
}

bool backgroundClass::initlialize(ID3D11Device * device, const char* filename)
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

void backgroundClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
}

objectClass * backgroundClass::getObj()
{
	return this->obj;
}

bool backgroundClass::getIsInObjHolder()
{
	return isInObjHolder;
}

void backgroundClass::setIsInObjHolder(bool x)
{
	this->isInObjHolder = x;
}
