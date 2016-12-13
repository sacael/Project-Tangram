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

float World::verificationVictory()
{
	float vict = 0;
	int size = 0;
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
	if (vict > 0.97f) {
		this->drawNextLevelButton();
	}
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
		//verificationVictory();
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
void World::rotate(float angle,AXIS axis) {
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
		switch (axis) {
		case(AXIS::X): {
			tempMatrice[5] = cosA;
			tempMatrice[6] = -sinA;
			tempMatrice[9] = sinA;
			tempMatrice[10] = cosA;
			break;
			}
		case(AXIS::Y): {
			tempMatrice[0] = cosA;
			tempMatrice[2] = -sinA;
			tempMatrice[8] = sinA;
			tempMatrice[10] = cosA;
			break;
		}
		case(AXIS::Z): {
			tempMatrice[0] = cosA;
			tempMatrice[1] = -sinA;
			tempMatrice[4] = sinA;
			tempMatrice[5] = cosA;
			break;
		}
		}

		multiplyTransfoMatrice(tempMatrice);
		initTempMatrix();
		tempMatrice[12] = Position.X;
		tempMatrice[13] = Position.Y;
		multiplyTransfoMatrice(tempMatrice);
		computeTransformation();
	}
}
void World::project(AXIS axis) {
	if (currentObject < objects.size()) {
		initTransfoMatrix();
		switch (axis) {
			case(AXIS::X): {
				tranfoMatrice[0] = 0;
				break;
			}
			case(AXIS::Y): {
				tranfoMatrice[5] = 0;
				break;
			}
			case(AXIS::Z): {
				tranfoMatrice[10] = 0;
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
			tranfoMatrice[0] = -1;
			break;
		}
		case(AXIS::Y): {
			tranfoMatrice[5] = -1;
			break;
		}
		case(AXIS::Z): {
			tranfoMatrice[10] = -1;
			break;
		}
		}
		computeTransformation();
	}
}
void World::translate(GLfloat x, GLfloat y,GLfloat z) {
	initTransfoMatrix();
	tranfoMatrice[12] = x;
	tranfoMatrice[13] = y;
	tranfoMatrice[14] = z;
	computeTransformation();
}
void World::shearing(GLfloat x, GLfloat y, GLfloat z) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		tranfoMatrice[12] = -Position.X;
		tranfoMatrice[13] = -Position.Y;
		tranfoMatrice[14] = -Position.Z;
		initTempMatrix();
		tempMatrice[1] = x;
		tempMatrice[4] = y;
		tempMatrice[9] = z;
		multiplyTransfoMatrice(tempMatrice);
		initTempMatrix();
		tempMatrice[12] = Position.X;
		tempMatrice[13] = Position.Y;
		tempMatrice[14] = Position.Z;
		multiplyTransfoMatrice(tempMatrice);
		computeTransformation();
	}
}
void World::scale(GLfloat x, GLfloat y, GLfloat z) {
	Point4 Position = Point4();
	if (currentObject < objects.size()) {
		Position = objects[currentObject].center;
		initTransfoMatrix();
		tranfoMatrice[12] = -Position.X;
		tranfoMatrice[13] = -Position.Y;
		tranfoMatrice[14] = -Position.Z;
		initTempMatrix();
		tempMatrice[0] = x;
		tempMatrice[5] = y;
		tempMatrice[10] = y;
		multiplyTransfoMatrice(tempMatrice);
		initTempMatrix();
		tempMatrice[12] = Position.X;
		tempMatrice[13] = Position.Y;
		tempMatrice[14] = Position.Z;
		multiplyTransfoMatrice(tempMatrice);
		computeTransformation();
	}
}



void World::initializeColors() {
	for (int i = 0; i < this->objects.size(); i++) {
		std::vector<float> color = std::vector<float>();
		for (int j = 0; j < 3; j++) {
			color.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		}

		this->colorArray.push_back(color);
	}
}