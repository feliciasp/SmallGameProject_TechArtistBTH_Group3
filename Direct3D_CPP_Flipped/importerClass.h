#ifndef IMPORTER_CLASS
#define IMPORTER_CLASS

#include "meshFormat.h"
#include <string.h>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <iostream>

struct Pose
{
	Vertex* vertices;
};

struct LoadedMesh
{
	Mesh meshHeader;
	Vertex* vertices;
	Pose* poses;
};

class Importer {
private:

	MyFormat header;
	LoadedMesh* loadedMeshes;
	Material* loadedMaterials;

public:

	Importer();
	~Importer();

	void clone(const Importer& other);

	//bool loadMesh(const char* filename, const char* meshName);
	bool loadMesh(const char* filename);

	bool loadMaterial(const char* filename);

	int getVertexCount() const;
	int getVertexCount(const char* meshName) const;
	int getVertexCount(int meshID) const;
	char* getMaterialID(const char * meshName) const;
	int getMeshCount() const;
	int getPoseCount() const;

	void getMinBBox(float &minX, float &minY, float &minZ);
	void getMaxBBox(float &maxX, float &maxY, float &maxZ);

	void getMinBBox(float &minX, float &minY, float &minZ, int meshID);
	void getMaxBBox(float &maxX, float &maxY, float &maxZ, int meshID);

	Vertex * getPoseVertices(int posIndex);

	LoadedMesh getMesh() const;

	Vertex* getVertices() const;
	Vertex* getVertices(const char* meshName) const;
	Vertex* getVertices(int meshID) const;

	void destroyMesh();
};

#endif // !IMPORTER_CLASS