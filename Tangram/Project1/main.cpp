//
//  main.cpp
//  SampleOpenGL
//
//  Created by Bob Antoine J Menelas on 16-11-21.
//  Copyright © 2016 Bob. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <math.h>  
#include "GL/glut.h" 
#include "Point4.h"
#include "GLobject.h"
#include <vector>
#include "World.h"


const int WIDTH = 1400;
const int HEIGHT = 1000;
const float ASPECT = float(WIDTH) / HEIGHT;

int sizeX = 1400;
int sizeY = 1000;
float step = 0.1f;
float angle = 45;
int leftButton = 0;
int middleButton = 0;
int rightButton = 0;
int leftButtonUp = 0;
int downX, downY;
std::string tuto[3] 
	= {"Rotation: Q, E", "Translation: Mouse", "Shearing: O, L"};
int nbtuto = 3;
bool pressedleft = false;

void mouse(int button, int state, int x, int y);
void motion(int x, int y);

void displayCursor(void);
void draw_axis(bool drawPoints, float scale);

void computeCollision();
void initializeColors(int);
void callback_idle(void);
void renderBackground();
void renderInstructions();
void renderObjects();
GLuint loadBMP_custom(const char * imagepath);

World world;
void init(void)
{
	world.InitLevel();
	world.maxX = sizeX;
	world.maxY = sizeY;
	GLuint texture = loadBMP_custom("texture.bmp");
	srand(time(NULL));
}

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	renderBackground();
	renderObjects();
	renderInstructions();
	glFlush();
}

void reshape (int width, int height)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int w = height * ASPECT;           // w is width adjusted for aspect ratio
	glViewport(0, 0, w, height);       // fix up the viewport to maintain aspect ratio
	gluOrtho2D(0, WIDTH, HEIGHT, 0);   // only the window is changing, not the camera
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();


	world.redrawNextLevelButton();
}

//fonction permettant de zoomer et de tourner avec la souris

void mouse(int button, int state, int x, int y)
{
    downX = x; downY = y;
    leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
    middleButton = ((button == GLUT_MIDDLE_BUTTON) &&  (state == GLUT_DOWN));
    rightButton = ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN));
	leftButtonUp = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP));

	if (leftButtonUp)
		world.verificationVictory();

	if (leftButton) {
		bool found = false;
		int i = 0;
		while (!found && i < world.UI.size())
		{
			found = found || world.UI[i]->pointInObject(x, y);
			i++;
		}
		if (found) {
			world.UI[i - 1]->actionOnClick();
		}
		else {
			while (!found && i < world.objects.size())
			{
				found = found || world.objects[i].pointInObject(x, y);
				i++;
			}
			if (found) {
				pressedleft = true;
				world.currentObject = i - 1;
				world.translate(-(downX - x), -(downY - y));
			}
			else {
				world.currentObject = i;
			}
		}
	}
    glutPostRedisplay();
}

void motion(int x, int y)
{
    if (leftButton)
	{
		if (world.pause == true) {
			bool found = false;
			int i = 0;
			while (!found && i < world.UI.size())
			{
				found = found || world.UI[i]->pointInObject(x, y);
				i++;
			}
			if (found) {
				world.UI[i - 1]->actionOnClick();
			}
		}
		else if (pressedleft) {
			world.translate(-(downX - x), -(downY - y));
		}
		else {
			
			
		}
		
    }

    downX = x;   downY = y;
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{

   switch (key) {
		
        case 27:
            exit(0);
            break;
            
            case 'a': //left
				world.translate(-step,0);
				 break;
            
            case 'd': //right
				world.translate(step,0);
				 break;
        case 'w': //up
			world.translate(0,step);
            break;
            
        case 's': //down
			world.translate(0, -step);
            break;
		case 'q':
			world.rotate(angle);
			break;
		case 'e':
			
			world.rotate(-angle);
			break;

        case 'o': 
			world.shearing(0,1);
            break;
            
        case 'l': //shearing  Hxy (-s,-t)
			world.shearing(0,-1);
            break;
            
        
        case 'g': //scale along XYZ
			world.scale(1.25,1.25);
			break;
            
        case 'h': //scale along XYZ
			world.scale(0.8,0.8);
            break;
            
    }
}

int main(int argc, char** argv)
{
    //logitek->AfficherJoysConnectes();
    
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (sizeX, sizeY);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Cube");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(callback_idle);
    glutMainLoop();
    return 0;
    
}
void renderInstructions() {
	for (int i = 0; i < nbtuto; i++) {
		glColor3d(.4f, .4f, .4f);
		glRasterPos2f(15, 15+i*20);
		int len = tuto[i].length();

		for (int j = 0; j < len; j++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tuto[i][j]);
		}
	}


}

void generateColors(int objects)
{
	
}

void renderObjects()
{
    GLfloat r,g,b;
    
    r=1.0f;
    g=1.0f;
    b=0.0f;
    
    glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	for (GLobject obj : world.targetObjects) {
		Point4** points = obj.getPoints();
		for (int i = 0; i<(obj.triangles.size()) * 3; i++) {
			glVertex3f((*points[i]).X, (*points[i]).Y, (*points[i]).Z);
		}
		delete[] points;
	}
	//glColor3f(1.0, 1.0, 0.0);
	int i = 0;
	for (GLobject obj : world.objects) {
		std::vector<float> color = world.colorArray.at(i++);
		glColor3f(color.at(0), color.at(1), color.at(2));
		Point4** points = obj.getPoints();
		for (int i = 0; i<(obj.triangles.size()) *3; i++) {
			glVertex3f((*points[i]).X, (*points[i]).Y, (*points[i]).Z);
		}
		delete[] points;
	}
	glColor3f(0.5, .5, 1.0);
	for (Button* obj : world.UI) {
		Point4** points = obj->getPoints();
		for (int i = 0; i<6; i++) {
			glVertex3f((*points[i]).X, (*points[i]).Y, (*points[i]).Z);
		}
		delete[] points;
	}
	glEnd();
	for (Button* obj : world.UI) {
		if (obj->Text.length() > 0) {
			glColor3d(1.0f, 1.0f, 1.0f);
			glRasterPos2f(obj->minX + 5,(obj->maxY + obj->minY)/2+12);
			int len = obj->Text.length();
			for (int i = 0; i < len; i++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, obj->Text[i]);
			}
		}
	}    
}

void callback_idle(void)
{
    glutPostRedisplay();    
}

void renderBackground() {
	int realTextureSize = 256;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), 
		-1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glDisable(GL_LIGHTING);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);

	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort);

	int currentWidth = glutGet(GLUT_WINDOW_WIDTH);
	int currentHeight = glutGet(GLUT_WINDOW_HEIGHT);
	int textureSizeX = realTextureSize*currentWidth / WIDTH;
	int textureSizeY = realTextureSize*currentHeight/ HEIGHT;

	if (textureSizeX == 0) {
		textureSizeX = 1;
	}

	if (textureSizeY == 0) {
		textureSizeY = 1;
	}

	float tmpMaxX = currentWidth / textureSizeX;
	float tmpMaxY = currentHeight / textureSizeY;
	int maxX = ceil(tmpMaxX) * textureSizeX;
	int maxY = ceil(tmpMaxY) * textureSizeY;

	// Draw a textured quad
	glBegin(GL_QUADS);

	for (int i = 0; i <= maxX; i = i + textureSizeX) {
		for (int j = 0; j <= maxY; j = j + textureSizeY) {
			glTexCoord2f(0, 0); glVertex3f(0+i , 0+j, 0);
			glTexCoord2f(0, 1); glVertex3f(0+i, textureSizeY+j, 0);
			glTexCoord2f(1, 1); glVertex3f(textureSizeX +i, textureSizeY+j, 0);
			glTexCoord2f(1, 0); glVertex3f(textureSizeX +i, 0+j, 0);
		}
	}

	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

}

GLuint loadBMP_custom(const char * imagepath) {

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height, bpp;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	// Read the header, i.e. the 54 first bytes

	// If less than 54 byes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return false;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	bpp = 3;

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54;

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	// Swap Red and Blue component for each texel of the image
	unsigned char t;
	for (unsigned int i = 0; i < imageSize; i += 3)
	{
		t = data[i];
		data[i] = data[i + 2];
		data[i + 2] = t;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (bpp == 3 ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Return the ID of the texture we just created
	return textureID;
}