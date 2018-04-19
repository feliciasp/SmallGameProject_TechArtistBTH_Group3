#include <windows.h>

#include <dinput.h>	//for input

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "bth_image.h"
#include <vector>
#include <stdint.h>

#include <fstream>	//for reading file
#include <istream>	//for reading file
#include <sstream> //for reading file

#define STB_IMAGE_IMPLEMENTATION	//for reading image
#include "stb_image.h"				//for reading image

using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "winmm.lib")

#pragma comment (lib, "dinput8.lib")	//for input
#pragma comment (lib, "dxguid.lib")		//for input


struct TriangleVertex
{
	float x, y, z;
	float u, v;
	float nx, ny, nz;
	float tx, ty, tz;	//FOR TANGENT AND NORMAL MAPPING

	int startWeight;
	int weightCount;
};


struct texImage
{
	int texWidth;
	int texHeight;
	int texBBP;
	unsigned char* texPixels;
};

//-----------MD5 MODEL-------------

struct MD5Joint
{
	std::string jointName;
	int parentID;

	XMFLOAT3 jointPos;
	XMFLOAT4 jointOrientation;

};

struct MD5Weight
{
	int jointID;
	float bias;
	XMFLOAT3 weightPos;
};

struct MD5Mesh
{
	int textureArrIndex;
	int numOfTris;

	std::vector<TriangleVertex> loadedVertices;
	std::vector<DWORD> indices;
	std::vector<MD5Weight> loadedWeights;

	std::vector<XMFLOAT3> positions;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};



//-----------MD5 Animation----------
struct MD5BoundingBox
{
	XMFLOAT3 bbMin;
	XMFLOAT3 bbMax;
};

struct Frame
{
	int frameID;
	std::vector<float> frameInfo;
};

struct animationJoint
{
	std::string animJointName;
	int jointParentId;
	int flags;
	int startIndex;
};

struct MD5Animation
{
	int nrOfKeyFrames;
	int nrOfJoints;
	int fps;
	int nrAnimatedSubsets;

	float keyFrameTime;
	float totalAnimationTime;
	float currentAnimationTime;

	std::vector<animationJoint> jointInfo;
	std::vector<MD5BoundingBox> bounds;
	std::vector<MD5Joint> baseJoints;
	std::vector<Frame> frameData;
	std::vector<std::vector<MD5Joint>> skeleton;			//An array with another array in it. First array is the skeleton, so which pose we are using at that frame
															//Next array is an array of joints
};

struct MD5Model
{
	int numberOfMeshes;
	int numberOfJoints;

	std::vector<MD5Joint> loadedJoints;
	std::vector<MD5Mesh> loadedMeshes;

	std::vector<MD5Animation> loadedAnimations;
};

bool loadMD5Texture(const char* fileName, std::vector<texImage> &modelTex)
{
	texImage tImage; 
	tImage.texPixels = stbi_load(fileName, &tImage.texHeight, &tImage.texWidth, &tImage.texBBP, 4);
	if (!tImage.texPixels)
	{
		std::wstring test = L"ERROR";
		MessageBox(0, test.c_str(), L"TEST", MB_OK);
		return false;
	}

	modelTex.push_back(tImage);
	return true;
}

//--------------LOAD MD5 MODEL---------------
bool loadMD5File(std::wstring filename, MD5Model& model, std::vector<texImage> &modelTex, ID3D11Device* gDevice)
{
	std::ifstream openFile(filename.c_str());
	std::string storeString;



	if (openFile)	//Loops until the end of the file
	{
		while (openFile)
		{
			openFile >> storeString;


			//Check what the next line is and decide what to do
			if (storeString == "MD5Version")
				std::getline(openFile, storeString);	//IGNORE LINE/NEXT LINE

			else if (storeString == "commandline")
				std::getline(openFile, storeString);	//IGNORE LINE/NEXT LINE

			else if (storeString == "numJoints")
				openFile >> model.numberOfJoints;

			else if (storeString == "numMeshes")
				openFile >> model.numberOfMeshes;


			//JOINTS
			else if (storeString == "joints")
			{
				MD5Joint tempJoint;

				openFile >> storeString;	//Skip char

				for (int i = 0; i < model.numberOfJoints; i++)
				{

					openFile >> tempJoint.jointName;

					openFile >> tempJoint.parentID;
					openFile >> storeString;		//SKIP CHAR

					openFile >> tempJoint.jointPos.x >> tempJoint.jointPos.z >> tempJoint.jointPos.y;	//Swap y and z if stuff isn't working
					openFile >> storeString >> storeString;												//SKIP CHAR
					openFile >> tempJoint.jointOrientation.x >> tempJoint.jointOrientation.z >> tempJoint.jointOrientation.y;

					tempJoint.jointName.erase(0, 1);
					tempJoint.jointName.erase(tempJoint.jointName.size() - 1, 1);

					//Compute w axis of quaternion
					float tempW = 1.0f - (tempJoint.jointOrientation.x * tempJoint.jointOrientation.x)
						- (tempJoint.jointOrientation.y * tempJoint.jointOrientation.y)
						- (tempJoint.jointOrientation.z * tempJoint.jointOrientation.z);

					float epsilon = 0.001f;

					if (tempW < epsilon)
						tempJoint.jointOrientation.w = 0.0f;
					else
						tempJoint.jointOrientation.w = -sqrtf(tempW);

					std::getline(openFile, storeString);			//NEXT LINE
					model.loadedJoints.push_back(tempJoint);
				}

				openFile >> storeString;							//SKIP CHAR

			}


			//MESH/SUBSETS
			else if (storeString == "mesh")
			{
				MD5Mesh tempMesh;

				int numberOfVerts, numberOfTris, numberOfWeights;
				std::string textureFilePath;

				std::getline(openFile, storeString);		//SKIP LINE


				openFile >> storeString;
				while (storeString != "}")
				{
					if (storeString == "shader")
					{
						openFile >> textureFilePath;
						textureFilePath.erase(0, 1);
						textureFilePath.erase(textureFilePath.size() - 1, 1);

						loadMD5Texture(textureFilePath.c_str(), modelTex);

						std::wstring test = std::to_wstring(modelTex.size());
						//MessageBox(0, test.c_str(), L"TEST", MB_OK);
						
						std::getline(openFile, storeString);		//SKIP TEXTURES THAT WE DON'T WANNA ADD FOR NOW
					}

					else if (storeString == "numverts")
					{
						openFile >> numberOfVerts;
						std::getline(openFile, storeString);	//NEXT LINE

						for (int i = 0; i < numberOfVerts; i++)
						{
							TriangleVertex tempVertex;

							openFile >> storeString >> storeString >> storeString;		//SKIP CHARS

							openFile >> tempVertex.u >> tempVertex.v;
							openFile >> storeString;		//SKIP CHAR
							openFile >> tempVertex.startWeight;
							openFile >> tempVertex.weightCount;

							std::getline(openFile, storeString);						//NEXT LINE
							tempMesh.loadedVertices.push_back(tempVertex);
						}
						//std::wstring testMessage = std::to_wstring(tempMesh.loadedVertices.size());
						//MessageBox(0, testMessage.c_str(), L"Error", MB_OK);							//Check if loadedVertices is added

					}

					else if (storeString == "numtris")
					{
						openFile >> numberOfTris;
						tempMesh.numOfTris = numberOfTris;

						std::getline(openFile, storeString);		//NEXT LINE

						for (int i = 0; i < numberOfTris; i++)
						{
							DWORD tempIndex;
							openFile >> storeString;
							openFile >> storeString;				//SKIP CHARS

							for (int j = 0; j < 3; j++)
							{
								openFile >> tempIndex;
								tempMesh.indices.push_back(tempIndex);
							}

							std::getline(openFile, storeString);		//NEXT LINE
						}
					}

					else if (storeString == "numweights")
					{
						openFile >> numberOfWeights;
						std::getline(openFile, storeString);			//NEXT LINE

						for (int i = 0; i < numberOfWeights; i++)
						{
							MD5Weight tempWeight;
							openFile >> storeString >> storeString;				//SKIP CHARS
							openFile >> tempWeight.jointID;
							openFile >> tempWeight.bias;
							openFile >> storeString;							//SKIP CHARS

							openFile >> tempWeight.weightPos.x >> tempWeight.weightPos.z >> tempWeight.weightPos.y;		//Swap y and z if stuff isn't working

							std::getline(openFile, storeString);				//NEXT LINE

							tempMesh.loadedWeights.push_back(tempWeight);
						}
					}

					else
						std::getline(openFile, storeString);					//NEXT LINE
					openFile >> storeString;
				}





				//Calculate vertex position//
				for (int i = 0; i < tempMesh.loadedVertices.size(); i++)
				{
					TriangleVertex tVertex = tempMesh.loadedVertices[i];
					tVertex.x = 0.0f;
					tVertex.y = 0.0f;
					tVertex.z = 0.0f;

					for (int j = 0; j < tVertex.weightCount; j++)
					{
						MD5Weight tWeight = tempMesh.loadedWeights[tVertex.startWeight + j];
						MD5Joint tJoint = model.loadedJoints[tWeight.jointID];

						XMVECTOR jointOrientation = XMVectorSet(tJoint.jointOrientation.x, tJoint.jointOrientation.y, tJoint.jointOrientation.z, tJoint.jointOrientation.w);
						XMVECTOR tWeightPosition = XMVectorSet(tWeight.weightPos.x, tWeight.weightPos.y, tWeight.weightPos.z, 0.0f);

						//Conjugate of quaternion is just the xyz inverse
						XMVECTOR tJointConjugate = XMVectorSet(-tJoint.jointOrientation.x, -tJoint.jointOrientation.y, -tJoint.jointOrientation.z, tJoint.jointOrientation.w);

						XMFLOAT3 rotPoint;
						XMStoreFloat3(&rotPoint, XMQuaternionMultiply(XMQuaternionMultiply(jointOrientation, tWeightPosition), tJointConjugate));

						tVertex.x += (tJoint.jointPos.x + rotPoint.x) * tWeight.bias;
						tVertex.y += (tJoint.jointPos.y + rotPoint.y) * tWeight.bias;
						tVertex.z += (tJoint.jointPos.z + rotPoint.z) * tWeight.bias;
					}

					XMFLOAT3 tPositions = XMFLOAT3(tVertex.x, tVertex.y, tVertex.z);
					tempMesh.positions.push_back(tPositions);
				}

				for (int i = 0; i < tempMesh.loadedVertices.size(); i++)
				{
					tempMesh.loadedVertices[i].x = tempMesh.positions[i].x;
					tempMesh.loadedVertices[i].y = tempMesh.positions[i].y;
					tempMesh.loadedVertices[i].z = tempMesh.positions[i].z;
				}

				
				
				
				
				//Calculate normals for face just like we always do, take cross product of two vertices. 
				std::vector<XMFLOAT3> unNormal;
				XMFLOAT3 normal = XMFLOAT3(0.0f, 0.0f, 0.0f);

				///////////////**************new**************////////////////////
				//tangent stuff
				std::vector<XMFLOAT3> tempTangent;
				XMFLOAT3 tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
				float tcU1, tcV1, tcU2, tcV2;
				///////////////**************new**************////////////////////

				
				XMVECTOR uv = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				XMVECTOR uw = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

				for (int i = 0; i < tempMesh.numOfTris; i++)
				{
					uv = XMVectorSet(tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].x - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 2]].x,
						tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].y - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 2]].y,
						tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].z - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 2]].z, 1.0f);

					uw = XMVectorSet(tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].x - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 1]].x,
						tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].y - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 1]].y,
						tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].z - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 1]].z, 1.0f);

					XMStoreFloat3(&normal, XMVector3Cross(uv, uw));
					unNormal.push_back(normal);

					///////////////TANGENT AND NORMAL MAP////////////////////
					//Find first texture coordinate edge 2d vector
					tcU1 = tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].u - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 2]].u;
					tcV1 = tempMesh.loadedVertices[tempMesh.indices[(i * 3)]].v - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 2]].v;

					//Find second texture coordinate edge 2d vector
					tcU2 = tempMesh.loadedVertices[tempMesh.indices[(i * 3)+2]].u - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 1]].u;
					tcV2 = tempMesh.loadedVertices[tempMesh.indices[(i * 3)+2]].v - tempMesh.loadedVertices[tempMesh.indices[(i * 3) + 1]].v;

					//Find tangent using both tex coord edges and position edges
					tangent.x = (tcV1 * XMVectorGetX(uv) - tcV2 * XMVectorGetX(uw)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
					tangent.y = (tcV1 * XMVectorGetY(uv) - tcV2 * XMVectorGetY(uw)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
					tangent.z = (tcV1 * XMVectorGetZ(uv) - tcV2 * XMVectorGetZ(uw)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));

					tempTangent.push_back(tangent);

				}
				
			
				//Compute normal for vertex
				//Check the faces that are connected to this vertex, sum up their normal 
				//value and divide by how many faces the vertex is connected to. 
				XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);	////////////////////NEW TANGET STUFF
				XMVECTOR sumNormals = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				int usedFaces = 0;
				float tempX, tempY, tempZ;

				for (int i = 0; i < tempMesh.loadedVertices.size(); i++)
				{
					for (int j = 0; j < tempMesh.numOfTris; j++)
					{
						if (tempMesh.indices[(j * 3)] == i ||
							tempMesh.indices[(j * 3) + 1] == i ||
							tempMesh.indices[(j * 3) + 2] == i)
						{
							tempX = XMVectorGetX(sumNormals) + unNormal[j].x;
							tempY = XMVectorGetY(sumNormals) + unNormal[j].y;
							tempZ = XMVectorGetZ(sumNormals) + unNormal[j].z;

							sumNormals = XMVectorSet(tempX, tempY, tempZ, 0.0f);
							
							//TANGENT
							tempX = XMVectorGetX(tangentSum) + tempTangent[j].x;
							tempY = XMVectorGetY(tangentSum) + tempTangent[j].y;
							tempZ = XMVectorGetZ(tangentSum) + tempTangent[j].z;

							tangentSum = XMVectorSet(tempX, tempY, tempZ, 0.0f); //sum up face tangents using this vertex
							//

							usedFaces++;
						}
					}

					sumNormals = sumNormals / usedFaces;
					tangentSum = tangentSum / usedFaces; //TENGANT

					//Normalize the normalSum vector and tangent
					sumNormals = XMVector3Normalize(sumNormals);
					tangentSum = XMVector3Normalize(tangentSum); //TANGENT


					tempMesh.loadedVertices[i].nx = -XMVectorGetX(sumNormals);
					tempMesh.loadedVertices[i].ny = -XMVectorGetY(sumNormals);
					tempMesh.loadedVertices[i].nz = -XMVectorGetZ(sumNormals);

					/////TANGET
					tempMesh.loadedVertices[i].tx = XMVectorGetX(tangentSum);
					tempMesh.loadedVertices[i].ty = XMVectorGetY(tangentSum);
					tempMesh.loadedVertices[i].tz = XMVectorGetZ(tangentSum);
					/////TANGENT

					usedFaces = 0;
					sumNormals = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

					////TANGENT
					tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				}

				
				//MODEL INDEX BUFFER
				D3D11_BUFFER_DESC indexBuffDesc;
				ZeroMemory(&indexBuffDesc, sizeof(indexBuffDesc));

				indexBuffDesc.Usage = D3D11_USAGE_DEFAULT;
				indexBuffDesc.ByteWidth = sizeof(DWORD) * tempMesh.numOfTris * 3;
				indexBuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				indexBuffDesc.CPUAccessFlags = 0;
				indexBuffDesc.MiscFlags = 0;

				D3D11_SUBRESOURCE_DATA indexData;
				indexData.pSysMem = &tempMesh.indices[0];
				gDevice->CreateBuffer(&indexBuffDesc, &indexData, &tempMesh.indexBuffer);



				//MODEL VERTEX BUFFER
				D3D11_BUFFER_DESC modelVertexBuffDesc;
				ZeroMemory(&modelVertexBuffDesc, sizeof(modelVertexBuffDesc));

				modelVertexBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
				modelVertexBuffDesc.ByteWidth = sizeof(TriangleVertex) * tempMesh.loadedVertices.size();
				modelVertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				modelVertexBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				modelVertexBuffDesc.MiscFlags = 0;

				D3D11_SUBRESOURCE_DATA modelVertexBuffData;
				ZeroMemory(&modelVertexBuffData, sizeof(modelVertexBuffData));
				modelVertexBuffData.pSysMem = &tempMesh.loadedVertices[0];
				HRESULT hr = gDevice->CreateBuffer(&modelVertexBuffDesc, &modelVertexBuffData, &tempMesh.vertexBuffer);

				model.loadedMeshes.push_back(tempMesh);
			}

		}


	}

	else
	{
		exit(-1);
	}

	return true;
}

bool loadMD5Animation(std::wstring filename, MD5Model& model)
{
	MD5Animation tempAnimation;

	std::ifstream openFile(filename.c_str());
	std::string storeString;

	if (openFile)
	{
		while (openFile)
		{
			openFile >> storeString;


			//Check what line/part of line we stored and decide what to do. 
			//Upper part just adding nr of joints, frames, animated components, framerate.
			if (storeString == "MD5Version")
				std::getline(openFile, storeString);		//SKIP LINE

			else if (storeString == "commandline")
				std::getline(openFile, storeString);		//SKIP LINE

			else if (storeString == "numFrames")
				openFile >> tempAnimation.nrOfKeyFrames;

			else if (storeString == "frameRate")
				openFile >> tempAnimation.fps;

			else if (storeString == "numJoints")
				openFile >> tempAnimation.nrOfJoints;

			else if (storeString == "numAnimatedComponents")
				openFile >> tempAnimation.nrAnimatedSubsets;


			//Joint names and their hierarchy. 
			else if (storeString == "hierarchy")
			{
				openFile >> storeString;					//SKIP CHAR

															//Load the indo on the joints(name, parentsID, flags, startIndex) of all the joints by looping through the hierarchy.  
				for (int i = 0; i < tempAnimation.nrOfJoints; i++)
				{
					animationJoint tempAnimJoint;

					openFile >> tempAnimJoint.animJointName;
					tempAnimJoint.animJointName.erase(0, 1);
					tempAnimJoint.animJointName.erase(tempAnimJoint.animJointName.size() - 1, 1);

					openFile >> tempAnimJoint.jointParentId;
					openFile >> tempAnimJoint.flags;
					openFile >> tempAnimJoint.startIndex;
					tempAnimation.jointInfo.push_back(tempAnimJoint);

					std::getline(openFile, storeString);			//SKIP REST OF LINE AND GO TO NEXT ONE
				}

			}
			else if (storeString == "bounds")
			{
				openFile >> storeString;					//SKIP CHAR

				for (int i = 0; i < tempAnimation.nrOfKeyFrames; i++)
				{
					MD5BoundingBox tempBoundBox;

					openFile >> storeString;				//SKIP CHAR
					openFile >> tempBoundBox.bbMin.x >> tempBoundBox.bbMin.z >> tempBoundBox.bbMin.y;
					openFile >> storeString >> storeString;	//SKIP CHAR
					openFile >> tempBoundBox.bbMax.x >> tempBoundBox.bbMax.z >> tempBoundBox.bbMax.y;
					openFile >> storeString;				//SKIP CHAR

					tempAnimation.bounds.push_back(tempBoundBox);
				}
			}

			else if (storeString == "baseframe")
			{
				openFile >> storeString;					//SKIP CHAR

				for (int i = 0; i < tempAnimation.nrOfJoints; i++)
				{
					MD5Joint tempBaseFrame;


					openFile >> storeString;				//SKIP CHAR
					openFile >> tempBaseFrame.jointPos.x >> tempBaseFrame.jointPos.z >> tempBaseFrame.jointPos.y;
					openFile >> storeString >> storeString;	//SKIP CHAR
					openFile >> tempBaseFrame.jointOrientation.x >> tempBaseFrame.jointOrientation.z >> tempBaseFrame.jointOrientation.y;
					openFile >> storeString;				//SKIP CHAR

					tempAnimation.baseJoints.push_back(tempBaseFrame);


				}
			}

			else if (storeString == "frame")
			{
				Frame tFrame;

				openFile >> tFrame.frameID;
				openFile >> storeString;					//SKIP CHAR

				for (int i = 0; i < tempAnimation.nrAnimatedSubsets; i++)
				{
					float tData;
					openFile >> tData;

					tFrame.frameInfo.push_back(tData);
				}

				tempAnimation.frameData.push_back(tFrame);

				std::vector<MD5Joint> tSkeleton;

				for (int i = 0; i < tempAnimation.jointInfo.size(); i++)
				{

					int j = 0;

					MD5Joint tFrameJoint = tempAnimation.baseJoints[i];

					tFrameJoint.parentID = tempAnimation.jointInfo[i].jointParentId;

					if (tempAnimation.jointInfo[i].flags & 1)
						tFrameJoint.jointPos.x = tFrame.frameInfo[tempAnimation.jointInfo[i].startIndex + j++];

					if (tempAnimation.jointInfo[i].flags & 2)
						tFrameJoint.jointPos.z = tFrame.frameInfo[tempAnimation.jointInfo[i].startIndex + j++];

					if (tempAnimation.jointInfo[i].flags & 4)
						tFrameJoint.jointPos.y = tFrame.frameInfo[tempAnimation.jointInfo[i].startIndex + j++];

					if (tempAnimation.jointInfo[i].flags & 8)
						tFrameJoint.jointOrientation.x = tFrame.frameInfo[tempAnimation.jointInfo[i].startIndex + j++];

					if (tempAnimation.jointInfo[i].flags & 16)
						tFrameJoint.jointOrientation.z = tFrame.frameInfo[tempAnimation.jointInfo[i].startIndex + j++];

					if (tempAnimation.jointInfo[i].flags & 32)
						tFrameJoint.jointOrientation.y = tFrame.frameInfo[tempAnimation.jointInfo[i].startIndex + j++];

					float tempW = 1.0f - (tFrameJoint.jointOrientation.x * tFrameJoint.jointOrientation.x)
						- (tFrameJoint.jointOrientation.y * tFrameJoint.jointOrientation.y)
						- (tFrameJoint.jointOrientation.z * tFrameJoint.jointOrientation.z);
					if (tempW < 0.0f)
						tFrameJoint.jointOrientation.w = 0.0f;
					else
						tFrameJoint.jointOrientation.w = -sqrtf(tempW);

					if (tFrameJoint.parentID >= 0)
					{
						MD5Joint pJoint = tSkeleton[tFrameJoint.parentID];

						XMVECTOR pJointOrientation = XMVectorSet(pJoint.jointOrientation.x, pJoint.jointOrientation.y, pJoint.jointOrientation.z, pJoint.jointOrientation.w);
						XMVECTOR tJointPos = XMVectorSet(tFrameJoint.jointPos.x, tFrameJoint.jointPos.y, tFrameJoint.jointPos.z, 0.0f);
						XMVECTOR pJointConjugate = XMVectorSet(-pJoint.jointOrientation.x, -pJoint.jointOrientation.y, -pJoint.jointOrientation.z, pJoint.jointOrientation.w);

						XMFLOAT3 rotatedPos;
						XMStoreFloat3(&rotatedPos, XMQuaternionMultiply(XMQuaternionMultiply(pJointOrientation, tJointPos), pJointConjugate));

						tFrameJoint.jointPos.x = rotatedPos.x + pJoint.jointPos.x;
						tFrameJoint.jointPos.y = rotatedPos.y + pJoint.jointPos.y;
						tFrameJoint.jointPos.z = rotatedPos.z + pJoint.jointPos.z;

						XMVECTOR tJointOrientation = XMVectorSet(tFrameJoint.jointOrientation.x, tFrameJoint.jointOrientation.y, tFrameJoint.jointOrientation.z, tFrameJoint.jointOrientation.w);
						tJointOrientation = XMQuaternionMultiply(pJointOrientation, tJointOrientation);

						tJointOrientation = XMQuaternionNormalize(tJointOrientation);

						XMStoreFloat4(&tFrameJoint.jointOrientation, tJointOrientation);
					}


					tSkeleton.push_back(tFrameJoint);
				}

				tempAnimation.skeleton.push_back(tSkeleton);
				openFile >> storeString;
			}
		}

		//Other data
		tempAnimation.keyFrameTime = 1.0f / tempAnimation.fps;
		tempAnimation.totalAnimationTime = tempAnimation.nrOfKeyFrames * tempAnimation.keyFrameTime;
		tempAnimation.currentAnimationTime = 0.0f;

		model.loadedAnimations.push_back(tempAnimation);
	}
	else
	{
		exit(-1);
	}

	return true;
}

void cleanUpMD5(MD5Model& model)
{
	for (int i = 0; i < model.numberOfMeshes; i++)
	{
		model.loadedMeshes[i].indexBuffer->Release();
		model.loadedMeshes[i].vertexBuffer->Release();
	}
}

void updateMD5Animation(MD5Model& model, float deltaTime, int animation, ID3D11DeviceContext* gDeviceContext)
{
	model.loadedAnimations[animation].currentAnimationTime += deltaTime;

	if (model.loadedAnimations[animation].currentAnimationTime > model.loadedAnimations[animation].totalAnimationTime)
		model.loadedAnimations[animation].currentAnimationTime = 0.0f;

	float currentFrame = model.loadedAnimations[animation].currentAnimationTime * model.loadedAnimations[animation].fps;		//Current frame is a float value and not really the frame number

	int frame0 = floorf(currentFrame);					//floorf return the greatest integer value that isn't bigger than the value in (), so here we get int of the frame we are on
	int frame1 = frame0 + 1;							//This is the next frame, that has the next pose we want to blend into

	if (frame0 == model.loadedAnimations[animation].nrOfKeyFrames - 1)
		frame1 = 0;															//This makes sure that the animation loops

																			//We need an interpolated skeleton so we can blend from one pose into another. 
	float interpol = currentFrame - frame0;
	std::vector<MD5Joint> interSkeleton;

	//Compute skeleton
	for (int i = 0; i < model.loadedAnimations[animation].nrOfJoints; i++)
	{
		MD5Joint tJoint;
		MD5Joint joint0 = model.loadedAnimations[animation].skeleton[frame0][i];
		MD5Joint joint1 = model.loadedAnimations[animation].skeleton[frame1][i];

		tJoint.parentID = joint0.parentID;

		//Interpolate positions for smooth transitioning between the positions
		tJoint.jointPos.x = joint0.jointPos.x + (interpol * (joint1.jointPos.x - joint0.jointPos.x));
		tJoint.jointPos.y = joint0.jointPos.y + (interpol * (joint1.jointPos.y - joint0.jointPos.y));
		tJoint.jointPos.z = joint0.jointPos.z + (interpol * (joint1.jointPos.z - joint0.jointPos.z));


		tJoint.jointOrientation.x = (joint1.jointOrientation.x * interpol) + (joint0.jointOrientation.x * (1 - interpol));
		tJoint.jointOrientation.y = (joint1.jointOrientation.y * interpol) + (joint0.jointOrientation.y * (1 - interpol));
		tJoint.jointOrientation.z = (joint1.jointOrientation.z * interpol) + (joint0.jointOrientation.z * (1 - interpol));
		tJoint.jointOrientation.w = (joint1.jointOrientation.w * interpol) + (joint0.jointOrientation.w * (1 - interpol));

		interSkeleton.push_back(tJoint);
	}

	//Compute the new vertex position and normals
	for (int k = 0; k < model.numberOfMeshes; k++)
	{
		MD5Mesh tempMesh;
		for (int i = 0; i < model.loadedMeshes[k].loadedVertices.size(); ++i)
		{
			TriangleVertex tVertex = model.loadedMeshes[k].loadedVertices[i];
			tVertex.x = 0.0f;
			tVertex.y = 0.0f;
			tVertex.z = 0.0f;

			tVertex.nx = 0.0f;
			tVertex.ny = 0.0f;
			tVertex.nz = 0.0f;

			for (int j = 0; j < tVertex.weightCount; ++j)
			{
				MD5Weight tWeight = model.loadedMeshes[k].loadedWeights[tVertex.startWeight + j];
				MD5Joint tJoint = interSkeleton[tWeight.jointID];

				float tWeightBias = tWeight.bias;

				//Convert to vectors
				XMVECTOR jointOrientation = XMVectorSet(tJoint.jointOrientation.x, tJoint.jointOrientation.y, tJoint.jointOrientation.z, tJoint.jointOrientation.w);
				XMVECTOR tWeightPosition = XMVectorSet(tWeight.weightPos.x, tWeight.weightPos.y, tWeight.weightPos.z, 0.0f);

				//Conjugate of quaternion is just the xyz inverse
				XMVECTOR tJointConjugate = XMVectorSet(-tJoint.jointOrientation.x, -tJoint.jointOrientation.y, -tJoint.jointOrientation.z, tJoint.jointOrientation.w);

				XMFLOAT3 rotPoint;
				//Multiplies the weight pos with the joint orientation, and then multiplies that with 
				//the "conjugate" of the quaternion to convert it to object local space. 
				XMStoreFloat3(&rotPoint, XMQuaternionMultiply(XMQuaternionMultiply(jointOrientation, tWeightPosition), tJointConjugate));

				//The sumn of all the weight bias(which is how much a weight is affecting the
				//vertex) should be 1.0
				tVertex.x += (tJoint.jointPos.x + rotPoint.x) * tWeight.bias;
				tVertex.y += (tJoint.jointPos.y + rotPoint.y) * tWeight.bias;
				tVertex.z += (tJoint.jointPos.z + rotPoint.z) * tWeight.bias;
				
				XMVECTOR tempNormal = XMVectorSet(tVertex.nx + rotPoint.x * tWeight.bias,
					tVertex.ny + rotPoint.y * tWeight.bias, tVertex.nz + rotPoint.z * tWeight.bias, 0.0f);

				tempNormal = XMVector3Normalize(tempNormal);
				tVertex.nx = XMVectorGetX(tempNormal);
				tVertex.ny = XMVectorGetY(tempNormal);
				tVertex.nz = XMVectorGetZ(tempNormal);
			}

			tempMesh.loadedVertices.push_back(tVertex);
		}

		for (int i = 0; i < model.loadedMeshes[k].loadedVertices.size(); i++)
		{
			model.loadedMeshes[k].loadedVertices[i].x = tempMesh.loadedVertices[i].x;
			model.loadedMeshes[k].loadedVertices[i].y = tempMesh.loadedVertices[i].y;
			model.loadedMeshes[k].loadedVertices[i].z = tempMesh.loadedVertices[i].z;

			model.loadedMeshes[k].loadedVertices[i].nx = tempMesh.loadedVertices[i].nx;					//FIX THIS
			model.loadedMeshes[k].loadedVertices[i].ny = tempMesh.loadedVertices[i].ny;
			model.loadedMeshes[k].loadedVertices[i].nz = tempMesh.loadedVertices[i].nz;
		}

		//UPDATE VERTEX BUFFER
		D3D11_MAPPED_SUBRESOURCE mapVertexBuff;

		HRESULT hr = gDeviceContext->Map(model.loadedMeshes[k].vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapVertexBuff);
		memcpy(mapVertexBuff.pData, &model.loadedMeshes[k].loadedVertices[0], (sizeof(TriangleVertex) * model.loadedMeshes[k].loadedVertices.size()));
		gDeviceContext->Unmap(model.loadedMeshes[k].vertexBuffer, 0);
	}
}
