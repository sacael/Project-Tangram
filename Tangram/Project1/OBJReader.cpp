#include "OBJReader.h"
#include <iostream>

// Reads a .obj located at the location filename
// Loads the points into a GLobject in memory
GLobject* OBJReader::ReadOBJ(const char* filename) {
	FILE * file = fopen(filename, "r");
	GLfloat vertexX, vertexY, vertexZ;
	GLint faceVertexX, faceVertexY, faceVertexZ;
	// Buffer of 128 vertices - enlarge this to be able to load larger obj files
	// TODO : Dynamically allocate size depending on the file's number of vertices and faces lines.
	GLfloat tempVertices[128] = {};
	GLfloat faceVertices[256] = {};
	int count = 0;
	int nbPoints = 0;
	int i = 0, l = 0;
	int j = 1, m = 1;
	int k = 2, n = 2;
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return nullptr;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break;
		}
		// read vertices
		if (strcmp(lineHeader, "v") == 0) {
			fscanf(file, "%f %f %f\n", &vertexX, &vertexY, &vertexZ);
			tempVertices[i] = vertexX;
			tempVertices[j] = vertexY;
			tempVertices[k] = vertexZ;
			i+=3;
			j+=3;
			k+=3;
			nbPoints += 1;
		}
		// read faces
		else if (strcmp(lineHeader, "f") == 0) {
			fscanf(file, "%i %i %i\n", &faceVertexX, &faceVertexY, &faceVertexZ);
			faceVertices[l] = tempVertices[(faceVertexX - 1)*3];
			faceVertices[m] = tempVertices[(faceVertexX - 1) * 3 + 1];
			faceVertices[n] = tempVertices[(faceVertexX - 1) * 3 + 2];
			l+=3;
			m+=3;
			n+=3;
			faceVertices[l] = tempVertices[(faceVertexY - 1) * 3];
			faceVertices[m] = tempVertices[(faceVertexY - 1) * 3 + 1];
			faceVertices[n] = tempVertices[(faceVertexY - 1) * 3 + 2];
			l+=3;
			m+=3;
			n+=3;
			faceVertices[l] = tempVertices[(faceVertexZ - 1) * 3];
			faceVertices[m] = tempVertices[(faceVertexZ - 1) * 3 + 1];
			faceVertices[n] = tempVertices[(faceVertexZ - 1) * 3 + 2];
			l+=3;
			m+=3;
			n+=3;
			count += 9;
		}
	}
	// In progress log
	std::cout << "Loading Obj..." << std::endl;
	return new GLobject(faceVertices, count);;
}