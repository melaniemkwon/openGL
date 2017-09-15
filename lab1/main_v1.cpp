//
//  main.cpp
//  83117
//
//  LAB 1
//  Created by Melanie Kwon on 8/31/17.
//  Copyright © 2017 Melanie Kwon. All rights reserved.
//

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#include <ctime>

const int screenWidth = 500;
const int screenHeight = 500;
int mouseState;
int mx;
int my;

struct GLintPoint {
    GLint x, y;
};

GLintPoint pts[4];
int NoOfPts=0;

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

void myMouse(int button, int state, int x, int y)
{
    // if the left button was pressed,
    // store the mouse location into the pts[],
    // and increment # of points
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON){
            // mouseState, mx, and my are user-defined global variable
            mouseState = 1; mx = x; my = y;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mouseState = 2; mx = x; my = y;
        }
    }
    glutPostRedisplay(); // invoke display callback function
    
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case 'c': {
            // change the current background color into a new one
            srand((unsigned)time(0));
            float red = (float)rand()/RAND_MAX;
            float green = (float)rand()/RAND_MAX;
            float blue = (float)rand()/RAND_MAX;
            glClearColor(red, green, blue, 0.0f); // Random color
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            break;
        }
        default:
            break;		      // do nothing
    }
    
    glutPostRedisplay(); // implicitly call myDisplay
}


// <<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    
    // draw either a polygon(rectangle) using the points in pts[]
    // To access a point in pts[], use the syntax like pts[index].x or pts[index].y
    if(mouseState == 1) {
        // If pts array does not exceed 3, add coordinates to pts array
//        if (NoOfPts < 4) {
            GLintPoint glpoint;
            glpoint.x = mx;
            glpoint.y = screenHeight - my;
            pts[NoOfPts] = glpoint;
            NoOfPts++;
            std::cout << "m1 NoOfPts < 4, " << NoOfPts << std::endl;
//        }
        if (NoOfPts >= 4) {
            // Else if pts array equals or exceeds 4, reset NoOfPts back to 0
            // Note: no need to wipe array...?
            NoOfPts = 0;
            std::cout << "m1 NoOfPts >= 4, " << NoOfPts << std::endl;
        }
    }
    if (mouseState == 2) {
        // Upon right mouse click, finish drawing the square shape
        if (NoOfPts == 3) {
            GLintPoint glpoint;
            glpoint.x = mx;
            glpoint.y = screenHeight - my;
            pts[NoOfPts] = glpoint;
            NoOfPts++;
            std::cout << "m2 NoOfPts == 3, " << NoOfPts << std::endl;
        } else if (NoOfPts >= 4) {
            // Else if pts array equals or exceeds 4, reset NoOfPts back to 0
            // Note: no need to wipe array...?
            NoOfPts = 0;
            std::cout << "m2 NoOfPts < 4, " << NoOfPts << std::endl;
        }
    }
    
    glPointSize(5.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < NoOfPts; i++) {
        glVertex2i( pts[i].x, pts[i].y );
    }
    glEnd();
    
    glFlush();
}

// <<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics - Lab1"); // open the screen window
    
    glutDisplayFunc(myDisplay);     // register redraw function
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    
    myInit();
    
    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}



/* C++ code segment to generate random numbers: between 1 and 50
 
 #include <ctime>
 
 ...
 
	srand((unsigned)time(0));
	int randomInt = rand()%50 + 1;
	float randomFloat = (float)rand()/RAND_MAX;
	cout << "Random Integer between 1 and 50 = " << randomInt << endl; 
	cout << "Random Float between 0 and 1 = " << randomFloat << endl;
 */
