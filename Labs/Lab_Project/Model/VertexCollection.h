#pragma once

#include "Vertex.h"

#include <vector>
#include <stdlib.h>



class VertexCollection
{
private:
	std::vector<Vertex> vec;

public:
	void add(Vertex vertex);

	float* toBufferArray(size_t& vertexSize, size_t& vertexCount);
};
