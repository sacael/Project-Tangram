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
/*
Class object of the world of the game
*/
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

	std::vector<GLobject> objects = std::vector<GLobject>();//list of the movable objects
	std::vector<GLobject> targetObjects = std::vector<GLobject>();//list of the target objects
	std::vector<Button*> UI = std::vector<Button*>();//list of the UI elements
	int currentObject = 0;// position of the selected object
	GLfloat step = 0.1f;//step of an increment 
	void rotate(float angle,AXIS axis);//rotation of the selected object around the center
	void project(AXIS axis);//projection of the selected object onto a plane normal to the axis
	void reflect(AXIS axis);//reflection of an object by a plane normal to the axis
	void translate(GLfloat x, GLfloat y, GLfloat z=0);//translation of the current object along a vector
	void shearing(GLfloat x, GLfloat y, GLfloat z=0);//shearing of the current selected object
	void scale(GLfloat x, GLfloat y, GLfloat z=1);//scaling of the selected object
	float maxX = 900;//information on the size of the world
	float maxY = 900;
	float minX = 0;
	float minY = 0;
	int currentLevel=0;//number of the currentLevel
	bool pause = false;//state of the pause
	void InitLevel();//initiation of the level
	float verificationVictory();//verification of the completion of the level
	void redrawNextLevelButton();//redraw of the nextLevelButton
	std::vector<std::vector<float>> colorArray;//arrayofpossiblecolors
private:
	GLfloat * multVectMat(Point4 vect, GLfloat * mat);//multiplication of a position by a matrix
	void loadLevel(int levelIndex);//load a certain level
	void computeTransformation();//compute the current transformation on the current object
	void initTransfoMatrix(void);//initiation of the transfomatrix
	void initTempMatrix(void);//initiation of the tempmatrix
	void multiplyTransfoMatrix(GLfloat * mat);//multiplication of the transfomatrix by another one
	void drawNextLevelButton();//first draw of the next level button
	void initializeColors();//initialisation of the colors
	NextLevel* nextLevelButton = nullptr;
	GLfloat transfoMatrix[16] = { 1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0,0,0,1.0f };  //matrix of current transformation
	GLfloat tempMatrix[16] = { 1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0,0,0,1.0f };//temporary matrix for transformation
};

