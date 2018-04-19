#ifndef MESH_FORMAT
#define MESH_FORMAT

struct MyFormat {
	int meshCount;
	int materialCount;
};

struct Material {
	char materialName[100];
	char textureName[100];

	float r, g, b, a;
};

struct Mesh {
	char meshName[100];
	int vertexCount;
	char materialName[100];
	float minX, maxX, minY, maxY, minZ, maxZ;
};

struct Vertex {
	float x, y, z;
	float nx, ny, nz;
	float r, g, b;
	float u, v;
};






#endif // !MESH_FORMAT
