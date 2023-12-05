#pragma once

#include <string>

#include "ModelFormat.h"



class HeaderModelDefinition
{
public:
	const std::string name;
	const float* data;
	const ModelFormat format;
	const size_t size;

	HeaderModelDefinition(const std::string name, const float* data, const ModelFormat format, const size_t size)
		: name(name), data(data), format(format), size(size)
	{ }
};
