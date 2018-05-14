#ifndef MESH_FORMAT
#define MESH_FORMAT

struct MyFormat {
	int meshCount;
	int materialCount;
	int poseCount;
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
	int jointCount;
	int animationCount;
};

struct Weight
{
	float value = 0.0f;
	int jointIndex = -1;
};

struct AnimationHeader {
	int animationLength = 0;
};

struct Vertex {
	float x, y, z;
	float nx, ny, nz;

	float r, g, b;
	float u, v;

	Weight weights[4];
};

struct Joint {
	char name[100];
	int index;
	int parentIndex;
	float globalBindposeInverse[4][4];
};

struct animatedJoint {
	char name[100];
	int keyFrame;
	int index;
	int parentIndex;
	float keyFrameTransform[4][4];
};





#endif // !MESH_FORMAT
