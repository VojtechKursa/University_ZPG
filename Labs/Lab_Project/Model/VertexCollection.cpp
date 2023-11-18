#include "VertexCollection.h"



void VertexCollection::add(Vertex vertex)
{
	vec.push_back(vertex);
}

float* VertexCollection::toBufferArray(size_t& vertexSize, size_t& vertexCount)
{
	vertexCount = vec.size();
	vertexSize = 11;	// number of values in each vertex

	size_t len = vertexSize * vertexCount;
	float* arr = new float[len];
	float* base = arr;
	Vertex vert;

	for (size_t i = 0; i < vec.size(); i++)
	{
		vert = vec[i];

		base[0] = vert.Position[0];
		base[1] = vert.Position[1];
		base[2] = vert.Position[2];

		base[3] = vert.Normal[0];
		base[4] = vert.Normal[1];
		base[5] = vert.Normal[2];
		
		base[6] = vert.Texture[0];
		base[7] = vert.Texture[1];
		
		base[8] = vert.Tangent[0];
		base[9] = vert.Tangent[1];
		base[10] = vert.Tangent[2];
		
		base += vertexSize;
	}
	
	return arr;
}
