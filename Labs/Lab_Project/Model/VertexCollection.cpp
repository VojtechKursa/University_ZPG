#include "VertexCollection.h"

void VertexCollection::add(Vertex vertex)
{
	vec.push_back(vertex);
}

float* VertexCollection::toBufferArray(size_t& len)
{
	int size = 11;

	len = size * vec.size();
	float* arr = new float[size * vec.size()];
	float* base;
	Vertex vert;

	for (size_t i = 0; i < vec.size(); i++)
	{
		base = &arr[size * i];
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
	}

	return arr;
}
