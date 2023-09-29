#pragma once

#include <GL/glew.h>

#include <vector>

#include "VBO.h"



class VAO
{
private:
	GLuint vaoId;
	std::vector<VBO*> vbos;

	void addVbo(VBO* vbo);

public:
	VAO();
	~VAO();

	void bind();

	/*
	Data reading from VBO described by VAO works approximately like:
	pos = beginning;
	len_bytes = size_of_datatype * lengthOfData;
	while(readAttribute)
	{
		read(start=pos, amount=len_bytes);
		if(shift == 0)
			pos += len_bytes;
		else
			pos += len_bytes + (shift - len_bytes)
	}
	*/

	void enableVertexAttributes(VBO* vbo, GLuint attributeIndex, GLint lengthOfData, GLenum dataType, GLboolean normalized, GLsizei shift, size_t beginning);

	/*!
	* \param vbo The VBO whose attribute array should be modified.
	* \param attributeIndex Specifies the index of the generic vertex attribute to be modified.
	* \param lengthOfData Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
	* \param dataType Specifies the data type of each component in the array.
	* \param normalized Specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
	* \param shift Specifies the offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. (IN BYTES)
	* \param beginning Specifies the offset of the first component of the first generic vertex attribute in the array. (IN BYTES)
	*/
	void enableVertexAttributes(VBO* vbo, GLuint attributeIndex, GLint lengthOfData, GLenum dataType, GLboolean normalized, GLsizei shift, const void* beginning);
};
