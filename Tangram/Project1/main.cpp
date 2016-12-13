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


int sizeX = 1400;
int sizeY = 1000;
float step = 0.1f;
float angle = 45;
int leftButton = 0;
int middleButton = 0;
int rightButton = 0;
int leftButtonUp = 0;
int downX, downY;
std::string tuto[3] = {"rotate : q,e","translate : mouse","shear : o,l"};
int nbtuto = 3;
bool pressedleft = false;

void mouse(int button, int state, int x, int y);
void motion(int x, int y);

void displayCursor(void);
void draw_axis(bool drawPoints, float scale);

void computeCollision();
void callback_idle(void);
void renderInstructions();
void renderObjects();

World world;
void init(void)
{
    
	world.InitLevel();
	world.maxX = sizeX;
	world.maxY = sizeY;
}


void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	renderObjects();
	renderInstructions();
	glFlush();
}

void reshape (int width, int height)
{

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, sizeX, sizeY, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
void renderInstructions(){
	for (int i = 0; i < nbtuto; i++) {
		glColor3d(0, 1.0f, 0.0f);
		glRasterPos2f(15,15+i*20);
		int len = tuto[i].length();
		for (int j = 0; j < len; j++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tuto[i][j]);
		}
	}


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
	glColor3f(1.0, 1.0, 0.0);
	for (GLobject obj : world.objects) {
		Point4** points = obj.getPoints();
		for (int i = 0; i<(obj.triangles.size()) *3; i++) {
			glVertex3f((*points[i]).X, (*points[i]).Y, (*points[i]).Z);
		}
		delete[] points;
	}
	glColor3f(1.0, 0, 1.0);
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
			glColor3d(0, 1.0f, 0.0f);
			glRasterPos2f(obj->minX + 5,(obj->maxY + obj->minY)/2+12);
			int len = obj->Text.length();
			for (int i = 0; i < len; i++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, obj->Text[i]);
			}
		}
	}
	

    
}



void callback_idle(void)
{
    glutPostRedisplay();    
}
