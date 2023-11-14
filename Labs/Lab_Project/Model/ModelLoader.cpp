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
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // sloučení malých plošek
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

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
        {
            aiMesh* mesh = scene->mMeshes[i];

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions())
                {
                    vert.Position[0] = mesh->mVertices[i].x;
                    vert.Position[1] = mesh->mVertices[i].y;
                    vert.Position[2] = mesh->mVertices[i].z;
                }

                if (mesh->HasNormals())
                {
                    vert.Normal[0] = mesh->mNormals[i].x;
                    vert.Normal[1] = mesh->mNormals[i].y;
                    vert.Normal[2] = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0))
                {
                    vert.Texture[0] = mesh->mTextureCoords[0][i].x;
                    vert.Texture[1] = mesh->mTextureCoords[0][i].y;
                }

                if (mesh->HasTangentsAndBitangents())
                {
                    vert.Tangent[0] = mesh->mTangents[i].x;
                    vert.Tangent[1] = mesh->mTangents[i].y;
                    vert.Tangent[2] = mesh->mTangents[i].z;
                }

                col.add(vert);
            }

            unsigned int* pIndices = nullptr;

            if (mesh->HasFaces())
            {
                pIndices = new unsigned int[mesh->mNumFaces * 3];

                for (unsigned int i = 0; i < mesh->mNumFaces; i++)
                {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            delete[] pIndices;
        }

        VBO* vbo = new VBO();
        size_t size;
        float* arr = col.toBufferArray(size);
        vbo->buffer(arr, size);

        VAO* vao = new VAO();
        vao->enableVertexAttributes(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, nullptr);
        vao->enableVertexAttributes(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, sizeof(float) * 3);
        vao->enableVertexAttributes(vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, sizeof(float) * 6);
        vao->enableVertexAttributes(vbo, 3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, sizeof(float) * 8);

        Model* model = new Model(vao, size / 11);

        delete[] arr;

        return model;
    }

	return nullptr;
}
