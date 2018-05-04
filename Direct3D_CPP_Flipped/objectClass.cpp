#include "objectClass.h"

objectClass::objectClass()
{
	vertexBuffer = 0;
	collision = 0;
	type = 0;
	timer = 0;
	frame = 0.5f;
}

objectClass::objectClass(const objectClass & other)
{

}

objectClass::~objectClass()
{
}

void objectClass::clone(const objectClass & other)
{
	mesh.clone(other.mesh);
	vertexBuffer = new ID3D11Buffer*[other.mesh.getMeshCount()];

	memcpy(vertexBuffer, other.vertexBuffer, sizeof(other.vertexBuffer));
	collision = new collisionClass;
	memcpy(collision, other.collision, sizeof(other.collision));
	matName = other.matName;
}

bool objectClass::initlialize(ID3D11Device * device, const char* filename)
{
	if (this->mesh.loadMesh(filename))
	{
		vertexBuffer = new ID3D11Buffer*[this->mesh.getMeshCount()];
	}
	bool result;

	for (int i = 0; i < this->mesh.getMeshCount(); i++)
	{
		result = initializeBuffer(device, this->mesh.getVertexCount(i), i);
		if (!result)
		{
			MessageBox(NULL, L"Error init buffers in objClass",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}
	
	//init vertex and index buffer
	
	collision = new collisionClass;

	return true;
	
}

void objectClass::shutdown()
{
	shutdownBuffer();
}

void objectClass::setVtrxIndexBufferToPipline(ID3D11DeviceContext* deviceCon, int meshID)
{
	setBuffers(deviceCon, meshID);
}

int objectClass::getVertexCount(int meshID)
{
	return this->mesh.getVertexCount(meshID);
}

int objectClass::getMeshCount()
{
	return this->mesh.getMeshCount();
}

XMVECTOR objectClass::getBoundingBoxMin()
{
	float x, y, z;

	this->mesh.getMinBBox(x, y, z);

	XMFLOAT3 vPos = { x, y, z };
	XMVECTOR vecVPos = XMLoadFloat3(&vPos);

	return vecVPos;
}

XMVECTOR objectClass::getBoundingBoxMax()
{
	float x, y, z;

	this->mesh.getMaxBBox(x, y, z);

	XMFLOAT3 vPos = { x, y, z };
	XMVECTOR vecVPos = XMLoadFloat3(&vPos);

	return vecVPos;
}

XMVECTOR objectClass::getBoundingBoxMin(int meshID)
{
	float x, y, z;

	this->mesh.getMinBBox(x, y, z, meshID);
	
	XMFLOAT3 vPos = {x, y, z};
	XMVECTOR vecVPos = XMLoadFloat3(&vPos);

	return vecVPos;
}

XMVECTOR objectClass::getBoundingBoxMax(int meshID)
{
	float x, y, z;

	this->mesh.getMaxBBox(x, y, z, meshID);

	XMFLOAT3 vPos = { x, y, z };
	XMVECTOR vecVPos = XMLoadFloat3(&vPos);

	return vecVPos;
}

collisionClass * objectClass::getCollisionClass()
{
	return this->collision;
}

//creating the vertexBuffer and idnexbuffer
bool objectClass::initializeBuffer(ID3D11Device * device, int count, int meshID)
{

	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;


	//subresource data
	
	vertexData.pSysMem = this->mesh.getVertices(meshID);
	//create our buffers
	memset(&vertexBufferDesc, 0, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//create vtx buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer[meshID]);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating vertexBuffer2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}


	return true;
}

void objectClass::shutdownBuffer()
{
	if (vertexBuffer)
	{
		delete[] vertexBuffer;
		vertexBuffer = 0;
	}
	if (collision)
	{
		delete collision;
		collision = 0;
		
	}
	
	this->mesh.destroyMesh();
}

void objectClass::setBuffers(ID3D11DeviceContext* deviceCon, int meshID)
{
	unsigned int vertexSize = sizeof(Vertex);
	unsigned int offset = 0;

	// specify which vertex buffer to use next.
	deviceCon->IASetVertexBuffers(0, 1, &vertexBuffer[meshID], &vertexSize, &offset);
	// specify the topology to use when drawing
	deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void objectClass::updatePosition(XMMATRIX mat)
{
	XMFLOAT3 vPos = { this->mesh.getVertices()[0].x,
		this->mesh.getVertices()[0].y, this->mesh.getVertices()[0].z };
	XMVECTOR vecVPos = XMLoadFloat3(&vPos);

	XMVector3Transform(vecVPos, mat);
}

XMVECTOR objectClass::getPosition()
{
	XMFLOAT3 vPos = { this->mesh.getVertices()[0].x,
		this->mesh.getVertices()[0].y, this->mesh.getVertices()[0].z };
	XMVECTOR vecVPos = XMLoadFloat3(&vPos);

	return vecVPos;
}

void objectClass::getWorldMatrix(XMMATRIX & other)
{
	other = this->objWorld;
}

void objectClass::setWorldMatrix(XMMATRIX & other)
{
	this->objWorld = other;
}

int objectClass::getType()
{
	return this->type;
}

void objectClass::setType(int type)
{
	this->type = type;
}

void objectClass::setMaterialName(std::string name)
{
	this->matName = name;
}

 std::string objectClass::getMaterialName()
{
	return this->matName;
}

 void objectClass::playAnimation(ID3D11DeviceContext* deviceCon, float dt)
 {
	 if (timer < 0.5f)
	 {
		 D3D11_MAPPED_SUBRESOURCE mappedVertBuff;
		 HRESULT result = deviceCon->Map(*vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertBuff);
		 /* mappedVertBuff.pData = mesh.getPoseVertices(0);*/
		 memcpy(mappedVertBuff.pData, mesh.getPoseVertices(0), sizeof(Vertex) * mesh.getVertexCount());
		 deviceCon->Unmap(*vertexBuffer, 0);
	 }
	 else if (timer > 0.5f)
	 {
		 D3D11_MAPPED_SUBRESOURCE mappedVertBuff;
		 HRESULT result = deviceCon->Map(*vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertBuff);
		 /* mappedVertBuff.pData = mesh.getPoseVertices(0);*/
		 memcpy(mappedVertBuff.pData, mesh.getPoseVertices(1), sizeof(Vertex) * mesh.getVertexCount());
		 deviceCon->Unmap(*vertexBuffer, 0);
	 }
	 
	 if (timer > 1.0f)
	 {
		 timer = 0;
	 }
	 timer += 1.0f * dt;
 }
