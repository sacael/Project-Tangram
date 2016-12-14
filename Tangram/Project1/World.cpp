#include "World.h"

#include "NextLevel.h"

World::World()
{
}


World::~World()
{
}

// Loads the folder Level located in ../Levels/ ending by levelIndex
void World::loadLevel(int levelIndex) {
	// Concate index with the level's path
	std::stringstream sstm;
	sstm << LEVELS_PATH << levelIndex << "/";
	std::string ans = sstm.str();
	char * concatenatedIndex = (char *)ans.c_str();
	std::cout << "Loading level : " << levelIndex << std::endl;
	// Loop through this directory
	DIR *pDIR;
	struct dirent *entry;
	if (pDIR = opendir(concatenatedIndex)) {
		// Foreach file, check if it is part of the target or not
		while (entry = readdir(pDIR)) {
			// Avoid looping on . and .. files
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				//Concat path and index to make the fullpath
				std::string buf(concatenatedIndex);
				buf.append(entry->d_name);
				// It is not the target, add it to objects
				if (strcmp(entry->d_name, "target.obj") != 0) {
					std::cout << buf.c_str() << std::endl;
					objects.push_back(*OBJReader::ReadOBJ(buf.c_str()));
				}
				// It is the target, add it to target objects
				else if (strcmp(entry->d_name, "target.obj") == 0) {
					std::cout << buf.c_str() << std::endl;
					targetObjects.push_back(*OBJReader::ReadOBJ(buf.c_str()));
				}
			}
		}
		closedir(pDIR);
	}
}

// Calls the load of current level's objects
void World::InitLevel()
{
	pause = false;
	objects.clear();
	targetObjects.clear();
	UI.clear();	
	this->nextLevelButton = nullptr;
	loadLevel(currentLevel + 1);
	std::cout << "Done" << std::endl;
	this->initializeColors();
}

//verification of the victory
float World::verificationVictory()
{
	float vict = 0;
	int size = 0;
		//we check for each target objects if some points are also on objects
		for(GLobject target:targetObjects)
		{
			for (int i = target.minX; i < target.maxX; i+=5) {
				for (int j = target.minY; j < target.maxY; j+=5) {
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
	if (vict > limit) {
		this->drawNextLevelButton();
	}
	//return of the % of completion
	return vict * 100;
}

void World::drawNextLevelButton() {
	pause = true;
	UI.clear();
	this->nextLevelButton = new NextLevel(500, 650, 500, 550, this);
	UI.push_back(this->nextLevelButton);
}

void World::redrawNextLevelButton() {
	if (this->nextLevelButton == nullptr) return;

	pause = true;
	UI.clear();
	this->nextLevelButton = new NextLevel(500, 650, 500, 550, this);
	UI.push_back(this->nextLevelButton);
	
}
//multiply the vector by the matrix
GLfloat* World::multVectMat(Point4 vect, GLfloat *mat)
{
	GLfloat * res = new GLfloat[4];

	for (int i = 0; i<4; i++) {

		res[i] = 0;
		res[i] += vect.X*mat[i];
		res[i] += vect.Y*mat[4 + i];
		res[i] += vect.Z*mat[8 + i];
		res[i] += vect.W*mat[12 + i];
	}

	return res;
}

//multiply the transfomatrix
void World::multiplyTransfoMatrix(GLfloat *mat)
{
	GLfloat temp[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int pos = 4 * i + j;
			temp[pos] = 0;
			temp[pos] += transfoMatrix[4 * i] * mat[j];
			temp[pos] += transfoMatrix[4 * i + 1] * mat[4 + j];
			temp[pos] += transfoMatrix[4 * i + 2] * mat[8 + j];
			temp[pos] += transfoMatrix[4 * i + 3] * mat[12 + j];
		}
	}
	for (int i = 0; i < 16; i++)
	{
		transfoMatrix[i] = temp[i];
	}
}

//application of the transfomatrix on the current object
void World::computeTransformation()
{
	bool valid = true;

	if (currentObject < objects.size()) {
		GLobject obj = objects[currentObject];
		GLfloat **transVert = new GLfloat*[obj.triangles.size() * 3];
		Point4** points = obj.getPoints();
		for (int i = 0; i < obj.triangles.size() * 3; i++) {
			transVert[i] = new GLfloat[4];
			transVert[i] = multVectMat((*points[i]), transfoMatrix);
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
	}
}

void World::initTransfoMatrix(void)
{
	for (int i = 0; i<16; i++)
	{
		transfoMatrix[i] = 0.0f;
	}

	transfoMatrix[0] = transfoMatrix[5] = transfoMatrix[10] = transfoMatrix[15] = 1.0f;
}

void World::initTempMatrix(void)
{
	for (int i = 0; i<16; i++)
	{
		tempMatrix[i] = 0.0f;
	}

	tempMatrix[0] = tempMatrix[5] = tempMatrix[10] = tempMatrix[15] = 1.0f;
}

//rotation around the center of the object
void World::rotate(float angle,AXIS axis) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {

		Position = objects[currentObject].center;
		initTransfoMatrix();
		transfoMatrix[12] = -Position.X;
		transfoMatrix[13] = -Position.Y;
		transfoMatrix[14] = -Position.Z;
		initTempMatrix();
		float radangle = angle*PI / 180.0;
		float cosA = cos(radangle);
		float sinA = sin(radangle);
		switch (axis) {
		case(AXIS::X): {
			tempMatrix[5] = cosA;
			tempMatrix[6] = -sinA;
			tempMatrix[9] = sinA;
			tempMatrix[10] = cosA;
			break;
			}
		case(AXIS::Y): {
			tempMatrix[0] = cosA;
			tempMatrix[2] = -sinA;
			tempMatrix[8] = sinA;
			tempMatrix[10] = cosA;
			break;
		}
		case(AXIS::Z): {
			tempMatrix[0] = cosA;
			tempMatrix[1] = -sinA;
			tempMatrix[4] = sinA;
			tempMatrix[5] = cosA;
			break;
		}
		}

		multiplyTransfoMatrix(tempMatrix);
		initTempMatrix();
		tempMatrix[12] = Position.X;
		tempMatrix[13] = Position.Y;
		tempMatrix[14] = Position.Z;
		multiplyTransfoMatrix(tempMatrix);
		computeTransformation();
	}
}
//projection of the object on a plane
void World::project(AXIS axis) {
	if (currentObject < objects.size()) {
		initTransfoMatrix();
		switch (axis) {
			case(AXIS::X): {
				transfoMatrix[0] = 0;
				break;
			}
			case(AXIS::Y): {
				transfoMatrix[5] = 0;
				break;
			}
			case(AXIS::Z): {
				transfoMatrix[10] = 0;
				break;
			}
		}
		computeTransformation();
	}
}
void World::reflect(AXIS axis){
	if (currentObject < objects.size()) {
		initTransfoMatrix();
		switch (axis) {
		case(AXIS::X): {
			transfoMatrix[0] = -1;
			break;
		}
		case(AXIS::Y): {
			transfoMatrix[5] = -1;
			break;
		}
		case(AXIS::Z): {
			transfoMatrix[10] = -1;
			break;
		}
		}
		computeTransformation();
	}
}
//translation of the object by a certain vector
void World::translate(GLfloat x, GLfloat y,GLfloat z) {
	initTransfoMatrix();
	transfoMatrix[12] = x;
	transfoMatrix[13] = y;
	transfoMatrix[14] = z;
	computeTransformation();
}
void World::shearing(GLfloat x, GLfloat y, GLfloat z) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		transfoMatrix[12] = -Position.X;
		transfoMatrix[13] = -Position.Y;
		transfoMatrix[14] = -Position.Z;
		initTempMatrix();
		tempMatrix[1] = x;
		tempMatrix[4] = y;
		tempMatrix[9] = z;
		multiplyTransfoMatrix(tempMatrix);
		initTempMatrix();
		tempMatrix[12] = Position.X;
		tempMatrix[13] = Position.Y;
		tempMatrix[14] = Position.Z;
		multiplyTransfoMatrix(tempMatrix);
		computeTransformation();
	}
}
void World::scale(GLfloat x, GLfloat y, GLfloat z) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		transfoMatrix[12] = -Position.X;
		transfoMatrix[13] = -Position.Y;
		transfoMatrix[14] = -Position.Z;
		initTempMatrix();
		tempMatrix[0] = x;
		tempMatrix[5] = y;
		tempMatrix[10] = y;
		multiplyTransfoMatrix(tempMatrix);
		initTempMatrix();
		tempMatrix[12] = Position.X;
		tempMatrix[13] = Position.Y;
		tempMatrix[14] = Position.Z;
		multiplyTransfoMatrix(tempMatrix);
		computeTransformation();
	}
}


//initialisation of the vector of colors
void World::initializeColors() {
	for (int i = 0; i < this->objects.size(); i++) {
		std::vector<float> color = std::vector<float>();
		for (int j = 0; j < 3; j++) {
			color.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		}

		this->colorArray.push_back(color);
	}
}