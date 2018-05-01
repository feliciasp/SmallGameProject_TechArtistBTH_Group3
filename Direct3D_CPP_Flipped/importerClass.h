#ifndef IMPORTER_CLASS
#define IMPORTER_CLASS

#include "meshFormat.h"
#include <string.h>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <iostream>

struct BlendShapeFrame
{
	BlendShape blendShapeHeader;
	Vertex* blendShapesVertices;
};

struct LoadedMesh
{
	Mesh meshHeader;
	Vertex* vertices;
	////For animations
	//BlendShapesHeader blendShapesHeader;
	//BlendShapeFrame* blendShapeTimeline;
};

class Importer {
private:

	MyFormat header;
	LoadedMesh* loadedMeshes;
	Material* loadedMaterials;

public:

	Importer();
	~Importer();

	//bool loadMesh(const char* filename, const char* meshName);
	bool loadMesh(const char* filename);

	bool loadMaterial(const char* filename);

	int getVertexCount() const;
	int getVertexCount(const char* meshName) const;
	int getVertexCount(int meshID) const;
	char* getMaterialID(const char * meshName) const;
	int getMeshCount() const;

	void getMinBBox(float &minX, float &minY, float &minZ);
	void getMaxBBox(float &maxX, float &maxY, float &maxZ);

	void getMinBBox(float &minX, float &minY, float &minZ, int meshID);
	void getMaxBBox(float &maxX, float &maxY, float &maxZ, int meshID);


	LoadedMesh getMesh() const;

	Vertex* getVertices() const;
	Vertex* getVertices(const char* meshName) const;
	Vertex* getVertices(int meshID) const;

	void destroyMesh();
};

#endif // !IMPORTER_CLASS