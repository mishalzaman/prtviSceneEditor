#ifndef LDR_MESH_OBJ
#define LDR_MESH_OBJ

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "vendor/easylogging++.h"
#include "Mesh.h"

class LdrModelObj
{
public:
	LdrModelObj(const char* filename);
	~LdrModelObj();
	std::vector<Mesh> getMeshes();
private:
	const char* filename;
	std::vector<Mesh> meshes;
	void processModel();
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh);
};

#endif LDR_MESH_OBJ

