#include "World.h"

#include "NextLevel.h"
World::World()
{
}


World::~World()
{
}
void World::InitLevel()
{
	pause = false;
	objects.clear();
	targetObjects.clear();
	switch (currentLevel) {
		case 0: {
			GLfloat objectVertices[] = { 50, 50, 0,
				50, 150, 0,
				150,50, 0,
				50, 150, 0,
				150,50, 0,
				150, 150, -0 };
			objects.push_back(GLobject(objectVertices, 18));
			GLfloat objectVertices2[] = { 50, 50, 0,
				50, 150, 0,
				150,50, 0, };
			objects.push_back(GLobject(objectVertices2, 9));
			GLfloat objectVerticesT[] = { 200, 200, 0,
				200, 300, 0,
				300,200, 0,
				200, 300, 0,
				300, 200, 0,
				300,300, 0,
				300, 200, 0,
				300, 300, 0,
				400,300, 0 };
			targetObjects.push_back(GLobject(objectVerticesT, 27));
			break;
		}
		case 1: {
			GLfloat objectVertices[] = { 50, 50, 0,
				50, 150, 0,
				150,50, 0,
				50, 150, 0,
				150,50, 0,
				150, 150, -0 };
			objects.push_back(GLobject(objectVertices, 18));
			GLfloat objectVertices2[] = { 50, 50, 0,
				50, 150, 0,
				150,50, 0, };
			objects.push_back(GLobject(objectVertices2, 9));
			objects.push_back(GLobject(objectVertices2, 9));
			GLfloat objectVerticesT[] = { 200, 200, 0,
				200, 300, 0,
				300,200, 0,
				200, 300, 0,
				300, 200, 0,
				300,300, 0,
				300, 200, 0,
				300, 300, 0,
				400,300, 0,
				400, 300, 0,
				300, 300, 0,
				400,400, 0 };
			targetObjects.push_back(GLobject(objectVerticesT, 36));
			break;
		}
	}
}
void World::verificationVictory()
{
	float vict = 0;
	int size = 0;
		for(GLobject target:targetObjects)
		{
			for (int i = target.minX; i < target.maxX; i+=4) {
				for (int j = target.minY; j < target.maxY; j+=4) {
					if (target.pointInObject(i, j)) {
						size++;
						bool valid = false;
						int k = 0;
						while (!valid&& k < objects.size())
						{
							valid = valid || objects[k].pointInObject(i, j);
							k++;
						}
						if (valid) {
							vict += 1;
						}
					}
			}
		}

	}
	vict /= (size);
	if (vict > 0.999f) {
		pause = true;
		UI.push_back(new NextLevel(500, 600, 500, 600, this));
	}
	
}
GLfloat* World::multVectMat(Point4 vect, GLfloat *mat)
{
	GLfloat * res = new GLfloat[4]; //{0.0f,0.0f,0.0f,1.0f};

	for (int i = 0; i<4; i++) {

		res[i] = 0;
		res[i] += vect.X*mat[i];
		res[i] += vect.Y*mat[4 + i];
		res[i] += vect.Z*mat[8 + i];
		res[i] += vect.W*mat[12 + i];
	}

	return res;
}

void World::multiplyTransfoMatrice(GLfloat *mat)
{
	GLfloat temp[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int pos = 4 * i + j;
			temp[pos] = 0;
			temp[pos] += tranfoMatrice[4 * i] * mat[j];
			temp[pos] += tranfoMatrice[4 * i + 1] * mat[4 + j];
			temp[pos] += tranfoMatrice[4 * i + 2] * mat[8 + j];
			temp[pos] += tranfoMatrice[4 * i + 3] * mat[12 + j];
		}
	}
	for (int i = 0; i < 16; i++)
	{
		tranfoMatrice[i] = temp[i];
	}
}
void World::computeTransformation()
{
	bool valid = true;

	if (currentObject < objects.size()) {
		GLobject obj = objects[currentObject];
		GLfloat **transVert = new GLfloat*[obj.triangles.size() * 3];
		Point4** points = obj.getPoints();
		for (int i = 0; i < obj.triangles.size() * 3; i++) {
			transVert[i] = new GLfloat[4];
			transVert[i] = multVectMat((*points[i]), tranfoMatrice); //apres multiplcation par la matrice de transformations
																  //printf(" for %d :  %.2f  %.2f  %.2f   \n", i, transVert[0], transVert[1],transVert[2]);
			valid = valid && transVert[i][0] > minX && transVert[i][0]<maxX && transVert[i][1]>minY&& transVert[i][1] < maxY;
			}
		if (valid) {
			for (int i = 0; i < obj.triangles.size() * 3; i++) {
				glVertex3f((*points[i]).X, (*points[i]).Y, (*points[i]).Z);
				(*points[i]).X = transVert[i][0];
				(*points[i]).Y = transVert[i][1];
				(*points[i]).Z = transVert[i][2];
				delete transVert[i];
			}
		}
		delete transVert;
		delete points;
		objects[currentObject].updateValues();
		verificationVictory();
	}
}
void World::initTransfoMatrix(void)
{
	for (int i = 0; i<16; i++)
	{
		tranfoMatrice[i] = 0.0f;
	}

	tranfoMatrice[0] = tranfoMatrice[5] = tranfoMatrice[10] = tranfoMatrice[15] = 1.0f;
}
void World::initTempMatrix(void)
{
	for (int i = 0; i<16; i++)
	{
		tempMatrice[i] = 0.0f;
	}

	tempMatrice[0] = tempMatrice[5] = tempMatrice[10] = tempMatrice[15] = 1.0f;
}
void World::rotate(float angle) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		tranfoMatrice[12] = -Position.X;
		tranfoMatrice[13] = -Position.Y;
		initTempMatrix();
		float radangle = angle*PI / 180.0;
		float cosA = cos(radangle);
		float sinA = sin(radangle);
		tempMatrice[0] = cosA;
		tempMatrice[1] = -sinA;
		tempMatrice[4] = sinA;
		tempMatrice[5] = cosA;
		multiplyTransfoMatrice(tempMatrice);
		initTempMatrix();
		tempMatrice[12] = Position.X;
		tempMatrice[13] = Position.Y;
		multiplyTransfoMatrice(tempMatrice);
		computeTransformation();
	}
}
void World::translate(GLfloat x, GLfloat y) {
	initTransfoMatrix();
	tranfoMatrice[12] = x;
	tranfoMatrice[13] = y;
	computeTransformation();
}
void World::shearing(GLfloat x, GLfloat y) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		tranfoMatrice[12] = -Position.X;
		tranfoMatrice[13] = -Position.Y;
		initTempMatrix();
		tempMatrice[1] = x;
		tempMatrice[4] = y;
		multiplyTransfoMatrice(tempMatrice);
		initTempMatrix();
		tempMatrice[12] = Position.X;
		tempMatrice[13] = Position.Y;
		multiplyTransfoMatrice(tempMatrice);
		computeTransformation();
	}
}
void World::scale(GLfloat x, GLfloat y) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		tranfoMatrice[12] = -Position.X;
		tranfoMatrice[13] = -Position.Y;
		initTempMatrix();
		tempMatrice[0] = x;
		tempMatrice[5] = y;
		multiplyTransfoMatrice(tempMatrice);
		initTempMatrix();
		tempMatrice[12] = Position.X;
		tempMatrice[13] = Position.Y;
		multiplyTransfoMatrice(tempMatrice);
		computeTransformation();
	}
}