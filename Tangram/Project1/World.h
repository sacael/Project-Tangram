#pragma once
#include <windows.h>
#include <gl/GL.h>
#include "Point4.h"
#include <vector>
#include "GLobject.h"
#include "Button.h"
#include "OBJReader.h"
#include<stdio.h>
#include<cstdlib>
#include<string.h>
#include <sstream>
#include <string>
#include <iostream>
#include"dirent.h"
#include <time.h>

#define PI 3.14159265
#define LEVELS_PATH "../Levels/Level" //The path to the levels with their identifier
typedef enum AXIS { X, Y, Z };
class NextLevel;
class Button;
class World
{
public:
	World();
	~World();

	std::vector<GLobject> objects = std::vector<GLobject>();
	std::vector<GLobject> targetObjects = std::vector<GLobject>();
	std::vector<Button*> UI = std::vector<Button*>();
	int currentObject = 0;
	GLfloat step = 0.1f;
	void rotate(float angle,AXIS axis);
	void project(AXIS axis);
	void reflect(AXIS axis);
	void translate(GLfloat x, GLfloat y, GLfloat z=0);
	void shearing(GLfloat x, GLfloat y, GLfloat z=0);
	void scale(GLfloat x, GLfloat y, GLfloat z=1);
	float maxX = 900;
	float maxY = 900;
	float minX = 0;
	float minY = 0;
	int nbLevels = 5;
	int currentLevel=0;
	bool pause = false;
	void InitLevel();
	float verificationVictory();
	void redrawNextLevelButton();
	std::vector<std::vector<float>> colorArray;
private:
	GLfloat * multVectMat(Point4 vect, GLfloat * mat);
	void loadLevel(int levelIndex);
	void computeTransformation();
	void initTransfoMatrix(void);
	void initTempMatrix(void);
	void multiplyTransfoMatrice(GLfloat * mat);
	void drawNextLevelButton();
	void initializeColors();
	NextLevel* nextLevelButton = nullptr;
	GLfloat tranfoMatrice[16] = { 1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0,0,0,1.0f };  // derniere de la matrice 4x4 permet de traduire les translations sous forme matricielle
	GLfloat tempMatrice[16] = { 1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0,0,0,1.0f };
};

