#pragma once

#include "Vertex.h"

#include <vector>



class VertexCollection
{
private:
	std::vector<Vertex> vec;

public:
	void add(Vertex vertex);

	float* toBufferArray(size_t& len);
};
