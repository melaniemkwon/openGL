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

const int MAX_BALLS = 5; // Render up to five balls
Ball balls[MAX_BALLS];
int noOfBalls = 1;
int selectedBall = 1;

void createBalls() {
    int ballId = 1;
    for (int i = 0; i < MAX_BALLS; i++) {
        balls[i] = Ball(ballId, 50, 50, 5, 5, 5, true);
        balls[i].setNextCoord(100, 100);
        balls[i].setRGB((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX);
        ballId++;
    }
}

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);       // background color white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is initally black
    glMatrixMode(GL_PROJECTION);         // set "camera shape"
    glLoadIdentity();
    lt = -10;
    rt = 100;
    bt = -10;
    tp = 100;
    
    createBalls();
    
    gluOrtho2D(lt, rt, bt, tp);          // set the world window
}

void myMouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mx = x; my = y;
        selected = true;
    }
    glutPostRedisplay();  // implicitly call myDisplay
    
}
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case 'a':
            std::cout << "add ball" << std::endl;
            if (noOfBalls < 5) { noOfBalls++; }
            break;
        case 'r':
            std::cout << "remove ball" << std::endl;
            if (noOfBalls > 1) { noOfBalls--; }
            break;
        case '1':
            std::cout << "select ball 1" << std::endl;
            selectedBall = 1;
            break;
        case '2':
            std::cout << "select ball 2" << std::endl;
            selectedBall = 2;
            break;
        case '3':
            std::cout << "select ball 3" << std::endl;
            selectedBall = 3;
            break;
        case '4':
            std::cout << "select ball 4" << std::endl;
            selectedBall = 4;
            break;
        case '5':
            std::cout << "select ball 5" << std::endl;
            selectedBall = 5;
            break;
        case 'p':
            balls[selectedBall-1].toggleFilled();
            break;
        case 'n':
            std::cout << "reset" << std::endl;
            createBalls();
            break;
        case 'q':
            std::cout << "quit" << std::endl;
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    int radiusIncrement = 1;
    switch(theKey) {
        case GLUT_KEY_PAGE_UP:
            std::cout << "increment radius. mass and velocity updated." << std::endl;
            balls[selectedBall-1].incRadius(radiusIncrement);
            break;
        case GLUT_KEY_PAGE_DOWN:
            std::cout << "decrement radius. mass and velocity udpated." << std::endl;
            balls[selectedBall-1].decRadius(radiusIncrement);
            break;
        // TODO: velocity increment and decrement
        case GLUT_KEY_UP:
            std::cout << "increase velocity" << std::endl;
            break;
        case GLUT_KEY_DOWN:
            std::cout << "decrease velocity" << std::endl;
            break;
        default:
            break;
    }
    
    glutPostRedisplay(); // implicitly call myDisplay
}

void drawCircles() {
    
    for (int i = 0; i < noOfBalls; i++) {
        Ball ball = balls[i];
        glColor3f(ball.getColorRed(), ball.getColorGreen(), ball.getColorBlue());
        
        std::cout << "BALL" << ball.getId() << " -- x:" << ball.getX() << " y:" << ball.getY() << " radius:" << ball.getRadius()
        << " mass:" << ball.getMass() << " velocity:" << ball.getVelocity() << " fill: " << ball.isFilled() << std::endl;
        //std::cout << "BALL" << ball.getId() << " to x:" << ball.getNextX() << " y:" << ball.getNextY() << std::endl;

        if (ball.isFilled()) {
            int triangleAmount = 20; // # of triangles used to draw circle
            
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(ball.getX(), ball.getY()); // center of circle
            for(int j = 0; j <= triangleAmount; j++) {
                glVertex2f(
                           ball.getX() + (ball.getRadius() * cos(j * 2*PI / triangleAmount)),
                           ball.getY() + (ball.getRadius() * sin(j * 2*PI / triangleAmount)));
            }
            glEnd();
        } else {
            int numVertices = 30;   // # of vertices on circle
            
            glBegin(GL_LINE_LOOP);
            float t = 0; // Angle parameter.
            for (int j = 0; j < numVertices; j++) {
                glVertex2f(
                           ball.getX() + ball.getRadius() * cos(t),
                           ball.getY() + ball.getRadius() * sin(t));
                t += 2 * PI / numVertices;
            }
            glEnd();
        }
    }
}

void myIdle() {
    std::cout << "myIdle()" << std::endl;
}

// <<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    glColor3f(0.0, 0.0, 0.0);
    
    drawCircles();
    
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
    glutInitWindowPosition(screenWidth, screenHeight); // set window position on screen
    glutCreateWindow("Computer Graphics - HW1"); // open the screen window
    
    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutMouseFunc(myMouse);
    //glutIdleFunc(myIdle);
    
    myInit();
    
    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}
