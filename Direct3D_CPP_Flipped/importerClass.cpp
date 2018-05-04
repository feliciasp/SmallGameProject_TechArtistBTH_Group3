#include "importerClass.h"

Importer::Importer()
{
	this->header.meshCount = 0;
	this->header.materialCount = 0;
}

Importer::~Importer()
{
	if (this->header.meshCount > 0)
	{
		for (int i = 0; i < this->header.meshCount; i++)
			delete[] this->loadedMeshes[i].vertices;

		delete[] this->loadedMeshes;
		this->header.meshCount = 0;
	}

	if (this->header.materialCount > 0)
	{
		delete[] this->loadedMaterials;

		this->header.materialCount = 0;
	}
}

void Importer::clone(const Importer & other)
{
	//header = other.header;
	header.meshCount = other.header.meshCount;
	header.materialCount = other.header.materialCount;
	loadedMeshes = new LoadedMesh[other.header.meshCount];
	for (int i = 0; i < other.header.meshCount; i++)
	{
		//loadedMeshes[i].meshHeader = other.loadedMeshes[i].meshHeader;
		loadedMeshes[i].meshHeader.vertexCount = other.loadedMeshes[i].meshHeader.vertexCount;
		loadedMeshes[i].meshHeader.minX = other.loadedMeshes[i].meshHeader.minX;
		loadedMeshes[i].meshHeader.minY = other.loadedMeshes[i].meshHeader.minY;
		loadedMeshes[i].meshHeader.minZ = other.loadedMeshes[i].meshHeader.minZ;
		loadedMeshes[i].meshHeader.maxX = other.loadedMeshes[i].meshHeader.maxX;
		loadedMeshes[i].meshHeader.maxY = other.loadedMeshes[i].meshHeader.maxY;
		loadedMeshes[i].meshHeader.maxZ = other.loadedMeshes[i].meshHeader.maxZ;
		loadedMeshes[i].vertices = new Vertex[other.loadedMeshes[i].meshHeader.vertexCount];
		memcpy(loadedMeshes[i].vertices, other.loadedMeshes[i].vertices, sizeof(other.loadedMeshes[i].vertices));
	}
}

bool Importer::loadMesh(const char * filename)
{
	if (this->header.meshCount > 0)
	{
		for (int i = 0; i < this->header.meshCount; i++)
			delete[] this->loadedMeshes[i].vertices;

		delete[] this->loadedMeshes;

		this->header.meshCount = 0;
	}



	std::ifstream infile(filename, std::ifstream::binary);

	if (infile)
	{
		MyFormat h;

		infile.read((char*)&h, sizeof(MyFormat));

		this->header.meshCount = h.meshCount;
		this->header.poseCount = h.poseCount;
		this->loadedMeshes = new LoadedMesh[h.meshCount];

		for (int i = 0; i < h.meshCount; i++)
		{
			infile.read((char*)&loadedMeshes[i].meshHeader, sizeof(Mesh));
			this->loadedMeshes[i].vertices = new Vertex[loadedMeshes[i].meshHeader.vertexCount];
			infile.read((char*)loadedMeshes[i].vertices, sizeof(Vertex) * loadedMeshes[i].meshHeader.vertexCount);

			this->loadedMeshes[i].poses = new Pose[h.poseCount];
			for (int j = 0; j < h.poseCount; j++)
			{
				OutputDebugString(L"\nPose created!\n");

				this->loadedMeshes[i].poses[j].vertices = new Vertex[loadedMeshes[i].meshHeader.vertexCount];
				infile.read((char*)loadedMeshes[i].poses[j].vertices, sizeof(Vertex) * loadedMeshes[i].meshHeader.vertexCount);
			}
			

		}

		return true;
	}

	return false;
}

bool Importer::loadMaterial(const char * filename)
{

	return false;
}


int Importer::getVertexCount() const
{
	if (this->header.meshCount > 0)
		return this->loadedMeshes->meshHeader.vertexCount;
}

int Importer::getVertexCount(const char* meshName) const
{
	for (int i = 0; i < this->header.meshCount; i++)
	{
		if (!strcmp(this->loadedMeshes[i].meshHeader.meshName, meshName))
			return this->loadedMeshes[i].meshHeader.vertexCount;
	}

	return -1;
}

int Importer::getVertexCount(int meshID) const
{
	return this->loadedMeshes[meshID].meshHeader.vertexCount;
}

char* Importer::getMaterialID(const char* meshName) const
{
	for (int i = 0; i < this->header.meshCount; i++)
	{
		if (!strcmp(this->loadedMeshes[i].meshHeader.meshName, meshName))
			return this->loadedMeshes[i].meshHeader.materialName;
	}

	return nullptr;
}

int Importer::getMeshCount() const
{
	return this->header.meshCount;
}

int Importer::getPoseCount() const
{
	return this->header.poseCount;
}

void Importer::getMinBBox(float & minX, float & minY, float & minZ)
{
	minX = this->loadedMeshes->meshHeader.minX;
	minY = this->loadedMeshes->meshHeader.minY;
	minZ = this->loadedMeshes->meshHeader.minZ;
}

void Importer::getMaxBBox(float & maxX, float & maxY, float & maxZ)
{
	maxX = this->loadedMeshes->meshHeader.maxX;
	maxY = this->loadedMeshes->meshHeader.maxY;
	maxZ = this->loadedMeshes->meshHeader.maxZ;
}

void Importer::getMinBBox(float & minX, float & minY, float & minZ, int meshID)
{
	minX = this->loadedMeshes[meshID].meshHeader.minX;
	minY = this->loadedMeshes[meshID].meshHeader.minY;
	minZ = this->loadedMeshes[meshID].meshHeader.minZ;
}

void Importer::getMaxBBox(float & maxX, float & maxY, float & maxZ, int meshID)
{
	maxX = this->loadedMeshes[meshID].meshHeader.maxX;
	maxY = this->loadedMeshes[meshID].meshHeader.maxY;
	maxZ = this->loadedMeshes[meshID].meshHeader.maxZ;
}

Vertex * Importer::getPoseVertices(int posIndex)
{
	return this->loadedMeshes[0].poses[posIndex].vertices;
}

LoadedMesh Importer::getMesh() const
{
	return LoadedMesh();
}


Vertex * Importer::getVertices() const
{
	return this->loadedMeshes[0].vertices;
}

Vertex * Importer::getVertices(const char* meshName) const
{
	for (int i = 0; i < this->header.meshCount; i++)
	{
		if (!strcmp(this->loadedMeshes[i].meshHeader.meshName, meshName))
			return this->loadedMeshes[i].vertices;
	}

	return nullptr;
}

Vertex * Importer::getVertices(int meshID) const
{
	return this->loadedMeshes[meshID].vertices;
}


void Importer::destroyMesh()
{
	if (this->header.meshCount > 0)
	{
		for (int i = 0; i < this->header.meshCount; i++)
			delete[] this->loadedMeshes[i].vertices;

		delete[] this->loadedMeshes;

		this->header.meshCount = 0;
	}

	if (this->header.materialCount > 0)
	{
		delete[] this->loadedMaterials;

		this->header.materialCount = 0;
	}



}