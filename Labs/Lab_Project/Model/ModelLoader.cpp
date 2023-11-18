#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/ext.hpp>

#include "Vertex.h"
#include "VertexCollection.h"



const std::string ModelLoader::modelFolder = "Assets/Models/";



Model* ModelLoader::loadModel(std::string filename)
{
    Assimp::Importer importer;
    unsigned int importOptions = 
          aiProcess_OptimizeMeshes              // sloučení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy



    const aiScene* scene = importer.ReadFile(modelFolder + filename, importOptions);



    if (scene)
    {
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());

            aiColor4D d;

            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }

        VertexCollection col;
        Vertex vert;
        aiFace face;
        aiMesh* mesh;
        int vert_id;

        for (unsigned int m = 0; m < scene->mNumMeshes; m++)                      //Objects
        {
            mesh = scene->mMeshes[m];

            for (unsigned int f = 0; f < mesh->mNumFaces; f++)
            {
                face = mesh->mFaces[f];

                for(unsigned int v = 0; v < 3; v++)
                {
                    vert_id = face.mIndices[v];
                    
                    if (mesh->HasPositions())
                    {
                        vert.Position[0] = mesh->mVertices[vert_id].x;
                        vert.Position[1] = mesh->mVertices[vert_id].y;
                        vert.Position[2] = mesh->mVertices[vert_id].z;
                    }

                    if (mesh->HasNormals())
                    {
                        vert.Normal[0] = mesh->mNormals[vert_id].x;
                        vert.Normal[1] = mesh->mNormals[vert_id].y;
                        vert.Normal[2] = mesh->mNormals[vert_id].z;
                    }

                    if (mesh->HasTextureCoords(0))
                    {
                        vert.Texture[0] = mesh->mTextureCoords[0][vert_id].x;
                        vert.Texture[1] = mesh->mTextureCoords[0][vert_id].y;
                    }

                    if (mesh->HasTangentsAndBitangents())
                    {
                        vert.Tangent[0] = mesh->mTangents[vert_id].x;
                        vert.Tangent[1] = mesh->mTangents[vert_id].y;
                        vert.Tangent[2] = mesh->mTangents[vert_id].z;
                    }

                    col.add(vert);
                }
            }
        }

        VBO* vbo = new VBO();
        size_t vertexSize, vertexCount;
        float* arr = col.toBufferArray(vertexSize, vertexCount);
        vbo->buffer(arr, vertexSize * vertexCount * sizeof(float));
        delete[] arr;

        VAO* vao = new VAO();
        vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, nullptr);
        vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, sizeof(float) * 3);
        vao->enableVertexAttributes(vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, sizeof(float) * 6);
        vao->enableVertexAttributes(vbo, 3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vertexSize, sizeof(float) * 8);

        return new Model(vao, vertexCount);
    }

	return nullptr;
}
