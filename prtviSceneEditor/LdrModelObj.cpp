#include "LdrModelObj.h"

LdrModelObj::LdrModelObj(const char * filename)
{
	this->filename = filename;
	this->processModel();
}

LdrModelObj::~LdrModelObj()
{
}

std::vector<Mesh> LdrModelObj::getMeshes()
{
	return this->meshes;
}

void LdrModelObj::processModel()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(this->filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		LOG(ERROR) << "LdrMeshObj::loadModel() " << importer.GetErrorString();
		return;
	}

	aiNode *node = scene->mRootNode; // node will contain indices to mesh data stored in the scene

	LOG(INFO) << "LdrMeshObj::loadModel() meshes " << node->mNumMeshes;
	LOG(INFO) << "LdrMeshObj::loadModel() children " << node->mNumChildren;

	this->processNode(node, scene);
}

void LdrModelObj::processNode(aiNode * node, const aiScene * scene)
{
	// Iterate over each mesh within the model
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// get mesh
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(processMesh(mesh));
	}

	// Iterate over the model children and call processNode
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh LdrModelObj::processMesh(aiMesh * mesh)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector3;

		// vertices
		vector3.x = mesh->mVertices[i].x;
		vector3.y = mesh->mVertices[i].y;
		vector3.z = mesh->mVertices[i].z;
		vertex.position = vector3;

		// normals
		vector3.x = mesh->mNormals[i].x;
		vector3.y = mesh->mNormals[i].y;
		vector3.z = mesh->mNormals[i].z;
		vertex.normal = vector3;

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vector2;
			// vertexes can contain 8 different texture coordinates.
			// FOr now just take the first set.
			vector2.x = mesh->mTextureCoords[0][i].x;
			vector2.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vector2;
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		// tangent
		vector3.x = mesh->mTangents[i].x;
		vector3.y = mesh->mTangents[i].y;
		vector3.z = mesh->mTangents[i].z;
		vertex.tangent = vector3;
		// bitangent
		vector3.x = mesh->mBitangents[i].x;
		vector3.y = mesh->mBitangents[i].y;
		vector3.z = mesh->mBitangents[i].z;
		vertex.bitangent = vector3;
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(vertices, indices);
}
