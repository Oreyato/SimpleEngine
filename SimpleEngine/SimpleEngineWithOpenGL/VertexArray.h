#pragma once

constexpr float vertices[] = {
	-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left [of the screen] = 0 
	 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right = 1
	 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right = 2
	-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left = 3
					 // ^ UV -> needed to position textures
};

constexpr unsigned int indices[] = { // indices are corresponding to the = ... above
	0, 1, 2, // first triangle TL, TR, BR
	2, 3, 0  // second triangle BR, BL, TL
};

class VertexArray
{
public:
	VertexArray(const float* verticesP, unsigned int nbVerticesP, const unsigned int* indicesP, unsigned int nbIndicesP);
	~VertexArray();

	void setActive();

	unsigned int getNbVertices() const { return nbVertices; }
	unsigned int getNbIndices() const { return nbIndices; }

private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	// OpenGL ID of the vertex buffer
	unsigned int vertexBuffer;
	// OpenGL ID of the index buffer, used to store data
	unsigned int indexBuffer;
	// OpenGL ID of the vertex array object
	unsigned int vertexArray;
};

