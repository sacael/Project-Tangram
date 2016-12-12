#include "GLobject.h"



Point4 ** GLobject::getPoints()
{
	Point4** returnpoints = new Point4*[triangles.size() * 3];
	int i = 0;
	while (i < triangles.size()) {
		returnpoints[i * 3] = triangles[i]->trianglePoints[0];
		returnpoints[i * 3+1] = triangles[i]->trianglePoints[1];
		returnpoints[i * 3+2] = triangles[i]->trianglePoints[2];
		i++;
	}
	return returnpoints;
}

void GLobject::updateValues()
{
	updateCenter();
	updateBox();
}

GLobject::GLobject(GLfloat points[], int nbP)
{
	triangles = std::vector<GLTriangle*>();
	int nbr = nbP;
	int i = 0;
	while (nbr >= 9) {
		triangles.push_back(new GLTriangle(points[i], points[i + 1], points[i + 2], points[i + 3], points[i + 4], points[i + 5], points[i + 6], points[i + 7], points[i + 8]));
			i+=9;
			nbr -= 9;
	}
	updateValues();
}

GLobject::~GLobject()
{
}

bool GLobject::pointInObject(GLfloat xp, GLfloat yp)
{
	if (xp<minX||xp>maxX|| yp<minY || yp>maxY) {
		return false;
	}
	bool inobject = false;
	int i = 0;
	while (inobject ==false&&i<triangles.size()){
		inobject = inobject || triangles[i]->pointInTriangle(xp, yp);
		i++;
	}
	return inobject;
}
void GLobject::updateCenter() {
	Point4 tempPoint = Point4();
	for (int i = 0; i<triangles.size(); i++) {
		tempPoint =tempPoint + triangles[i]->getCenter();
	}
	center = tempPoint / triangles.size();
}
void GLobject::updateBox()
{
	if (triangles.size() != 0) {
		float tempmaxX = triangles[0]->trianglePoints[0]->X;
		float tempminX = triangles[0]->trianglePoints[0]->X;
		float tempmaxY = triangles[0]->trianglePoints[0]->Y;
		float tempminY = triangles[0]->trianglePoints[0]->Y;
		float tempmaxZ = triangles[0]->trianglePoints[0]->Z;
		float tempminZ = triangles[0]->trianglePoints[0]->Z;
		for(int i=0;i<triangles.size();i++){
			for (int j = 0; j < 3; j++) {
				tempmaxX = std::max(triangles[i]->trianglePoints[j]->X,tempmaxX);
				tempminX = std::min(triangles[i]->trianglePoints[j]->X, tempminX);
				tempmaxY = std::max(triangles[i]->trianglePoints[j]->Y, tempmaxY);
				tempminY = std::min(triangles[i]->trianglePoints[j]->Y, tempminY);
				tempmaxZ = std::max(triangles[i]->trianglePoints[j]->Z, tempmaxZ);
				tempminZ = std::min(triangles[i]->trianglePoints[j]->Z, tempminZ);
			}
		}
		maxX = tempmaxX;
		minX = tempminX;
		maxY = tempmaxY;
		minY = tempminY;
		maxZ = tempmaxZ;
		minZ = tempminZ;
	}
}
