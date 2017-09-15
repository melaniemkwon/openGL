//
//  main.cpp
//  HW1
//
//  Created by Melanie Kwon on 9/5/17.
//  Copyright © 2017 Melanie Kwon. All rights reserved.
//

#include <iostream>
#include <math.h>	// included for random number generation
#include "ball.h"

//Computer Graphics Lab : Drawing an object and changing world view
#ifdef _WIN32
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#endif

const int screenWidth = 500;
const int screenHeight = 500;
bool selected = false;
int mx;
int my;
#define PI 3.14159265358979324

// left, right, bottom, top
float lt, rt, bt, tp;

//static float R = 40.0; // Radius of circle.
//static float X = 50.0; // X-coordinate of center of circle.
//static float Y = 50.0; // Y-coordinate of center of circle.
const int MAX_BALLS = 5; // Render up to five balls
Ball balls[MAX_BALLS];
int noOfBalls = 1;
static int numVertices = 30; // Number of vertices on circle.

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
    glLoadIdentity();
    lt = -10;
    rt = 100;
    bt = -10;
    tp = 100;
    
    // Create balls
    for (int i = 0; i < MAX_BALLS; i++) {
        balls[i] = Ball(i, 50, 50, 20, true);
    }
    
    gluOrtho2D(lt, rt, bt, tp);	// set the world window
}
void myMouse(int button, int state, int x, int y)
{
    // TODO: find out why mouse click not registering...
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mx = x; my = y;
        selected = true;
    }
    glutPostRedisplay(); // invoke display callback function
    
}
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case 'a':
            std::cout << "add ball" << std::endl;
            break;
        case 'r':
            std::cout << "remove ball" << std::endl;
            break;
        case '1':
            std::cout << "select ball 1" << std::endl;
            break;
        case '2':
            std::cout << "select ball 2" << std::endl;
            break;
        case '3':
            std::cout << "select ball 3" << std::endl;
            break;
        case '4':
            std::cout << "select ball 4" << std::endl;
            break;
        case '5':
            std::cout << "select ball 5" << std::endl;
            break;
        case 'p':
            std::cout << "toggle ball fill and non-filled" << std::endl;
            break;
        case 'n':
            std::cout << "reset" << std::endl;
            break;
        case 'q':
            std::cout << "quit" << std::endl;
            break;
        default:
            break;		      // do nothing
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case GLUT_KEY_PAGE_UP:
            std::cout << "increment radius. mass and velocity updated." << std::endl;
            break;
        case GLUT_KEY_PAGE_DOWN:
            std::cout << "decrement radius. mass and velocity udpated." << std::endl;
            break;
        case GLUT_KEY_UP:
            std::cout << "increase velocity" << std::endl;
            break;
        case GLUT_KEY_DOWN:
            std::cout << "decrease velocity" << std::endl;
            break;
        default:
            break;		      // do nothing
    }
    
    glutPostRedisplay(); // implicitly call myDisplay
}

// <<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    glColor3f(0.0, 0.0, 0.0);
    
    for (int i = 0; i < noOfBalls; i++) {
        Ball ball = balls[i];
        std::cout << "BALL" << ball.getId() << "  x:" << ball.getX() << " y:" << ball.getY() << " radius:" << ball.getRadius() << std::endl;
        
        if (ball.isFilled()) {
            glBegin(GL_POLYGON);
            float t = 0; // Angle parameter.
            for (int j = 0; j < numVertices; j++) {
                glVertex2i(ball.getX() + ball.getRadius() * cos(t), ball.getY() + ball.getRadius() * sin(t));
                t += 2 * PI / numVertices;
            }
            glEnd();
        } else {
            glBegin(GL_LINE_LOOP);
            float t = 0; // Angle parameter.
            for (int i = 0; i < numVertices; i++) {
                //glColor3f((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX);
                glVertex3f(ball.getX() + ball.getRadius() * cos(t), ball.getY() + ball.getRadius() * sin(t), 0.0);
                t += 2 * PI / numVertices;
            }
            glEnd();
        }
        
    }
    
    if (selected) {
        std::cout << "left mouse clicked" << std::endl;
    }
    
    glutSwapBuffers();
    glFlush();
}


// --------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

// <<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics - Lab"); // open the screen window
    
    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    
    myInit();
    
    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}
