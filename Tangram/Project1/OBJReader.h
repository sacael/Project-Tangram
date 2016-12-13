#ifndef _OBJ_READER
#define _OBJ_READER

#include <Windows.h>
#include "GLobject.h"
#include <vector>
#include "Point4.h"
#include "GL/glut.h"

/*
OBJReader.h : Reads the vertexes and faces of small .obj files
*/
class OBJReader
{
public:
	static GLobject* ReadOBJ(const char* filename);
private:
	OBJReader() {};
};
#endif