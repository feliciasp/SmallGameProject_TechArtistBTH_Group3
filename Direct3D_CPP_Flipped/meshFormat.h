#ifndef MESH_FORMAT
#define MESH_FORMAT

struct MyFormat {
	int meshCount;
	int materialCount;
	//int fps;
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
	//int animationCount;
};

struct BlendShapesHeader
{
	int nrOfBlendShapes;
	int nrOfKeyFrames;
};
struct BlendShape
{
	int keyFrame;
	//vertexArray
};

struct Vertex {
	float x, y, z;
	float nx, ny, nz;
	float r, g, b;
	float u, v;
	//float tu, tv;
};






#endif // !MESH_FORMAT
