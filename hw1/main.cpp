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

// OpenGL Programming : Bouncing Balls
#ifdef _WIN32
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#include <unistd.h>
#endif

#define SCREENSIZE 500
const int screenWidth = SCREENSIZE;
const int screenHeight = SCREENSIZE;
bool selected = false;
double mx;
double my;
#define PI 3.14159265358979324
GLdouble t = 0.0; // Initial time value

// left, right, bottom, top
float lt, rt, bt, tp;

const int MAX_BALLS = 5; // Render up to five balls
Ball balls[MAX_BALLS];
int noOfBalls = 2;
int selectedBall = 1;

void createBalls() {
    int ballId = 1;
    
    // x, y, radius, velocity direction (as unit vector coords), velocity magnitude
    double ballInit[MAX_BALLS][6] = {
        {10,10,5,0.5,sqrt(3/2),1},
        {25,25,5,sqrt(3/2),-0.5,1},
        {40,40,5,-sqrt(2)/2,sqrt(2)/2,1},
        {65,65,5,-sqrt(2)/2,-sqrt(2)/2,1},
        {80,80,5,-sqrt(3/2),0.5,1}
    };
    
    for (int i = 0; i < MAX_BALLS; i++) {
        balls[i] = Ball(ballId, ballInit[i][0], ballInit[i][1], ballInit[i][2], true);
        balls[i].setVelocity(ballInit[i][3], ballInit[i][4], ballInit[i][5]); // direction (in degrees) and magnitude
        balls[i].setMass(5);
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
    lt = 0;
    rt = 100;
    bt = 0;
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
bool isBallAreaInMouseSelection(double x, double y, int r) {
    std::cout << "isBallAreaInMouseSelection" << std::endl;
    std::cout << "mouse coord: " << mx << "," << my << std::endl;
    
    std::cout << "x-r = " << x-r << std::endl;
    std::cout << "x+r = " << x+r << std::endl;
    std::cout << "y-r = " << y-r << std::endl;
    std::cout << "y+r = " << y+r << std::endl;
    
    return (mx >= x-r && mx <= x+r && my >= y-r && my <= y+r);
}
void myMotion(int x, int y) {
    // ####### TODO: Allow user to pick a ball to change its velocity by using mouse (left-click, drag and drop)
    mx = x; my = y;
    std::cout << "myMotion called at " << mx << "," << my << std::endl;
    
    for (int i = 0; i < noOfBalls; i++) {
        if ( isBallAreaInMouseSelection(balls[i].getX(), screenHeight - balls[i].getY(), balls[i].getRadius()) ) {
            std::cout << "SELECTED BALL" << balls[i].getId() << std::endl;
        }
    }
    
    glutPostRedisplay();
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
            noOfBalls = 2;
            break;
        case 'q':
            std::cout << "quit" << std::endl;
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    int radiusIncrement = 1;
    switch(theKey) {
        case GLUT_KEY_PAGE_UP:
            std::cout << "BALL" << balls[selectedBall-1].getId() << " increment radius. mass and velocity updated." << std::endl;
            balls[selectedBall-1].incRadius(radiusIncrement);
            break;
        case GLUT_KEY_PAGE_DOWN:
            std::cout << "BALL" << balls[selectedBall-1].getId() << " decrement radius. mass and velocity updated." << std::endl;
            balls[selectedBall-1].decRadius(radiusIncrement);
            break;
        case GLUT_KEY_UP:
            std::cout << "increase velocity magnitude" << std::endl;
            balls[selectedBall-1].incVelocityMagnitude(1);
            break;
        case GLUT_KEY_DOWN:
            std::cout << "decrease velocity magnitude" << std::endl;
            balls[selectedBall-1].decVelocityMagnitude(1);
            break;
        default:
            break;
    }
    
    glutPostRedisplay(); 
}

void drawCircles() {
    
    for (int i = 0; i < noOfBalls; i++) {
        Ball ball = balls[i];
        glColor3f(ball.getColorRed(), ball.getColorGreen(), ball.getColorBlue());
        
        std::cout << "BALL" << ball.getId() << " -- x:" << ball.getX() << " y:" << ball.getY() << " radius:" << ball.getRadius()
        << " mass:" << ball.getMass() << " velocity: (" << ball.getVelocityVectorX() << "," << ball.getVelocityVectorY() << ") magn:" << ball.getVelocityMagnitude() << " fill:" << ball.isFilled() << std::endl;

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

void calcVectorReflection(double &ax, double &ay, double nx, double ny) {
    
    // normalize vectors a and n
    double ax_norm = ax / (sqrt(ax*ax + ay*ay));
    double ay_norm = ay / (sqrt(ax*ax + ay*ay));
    double nx_norm = nx / (sqrt(nx*nx + ny*ny));
    double ny_norm = ny / (sqrt(nx*nx + ny*ny));
    //std::cout << "Normalized vectors: " << ax_norm << "," << ay_norm << " " << nx_norm << "," << ny_norm << std::endl;

    // direction of reflected array, from the center of ball
    // r = a-2(a·n)n
    ax = ax_norm - 2 * (ax_norm * nx_norm + ay_norm * ny_norm) * nx_norm;
    ay = ay_norm - 2 * (ax_norm * nx_norm + ay_norm * ny_norm) * ny_norm;
    
}

/*
 * Input:   Ball b1, Ball b2  (passed by reference)
 *
 *          v1 and v2 (velocity of each ball before collision),
 *          c1 and c2 (center locations of two balls when two balls collide),
 *          M1 and M2 (mass of each ball)
 *
 * Output:  v1’ and v2’ (new velocity of each ball after collision) updated in b1 and b2
 */
void calcBallCollision(Ball &b1, Ball &b2) {
    // Calculate the distance D = |c1c2| between 2 points of collision where c1 and c2 are center locations of two balls.
    double D = sqrt( pow(b1.getX() - b2.getX(), 2) + pow(b1.getY() - b2.getY(), 2) );
    
    // Find the unit vector n from the point of collision for the first ball and the point of collision of the second ball.
    double nx = (b1.getX() - b2.getX()) / D;
    double ny = (b1.getY() - b2.getY()) / D;
    
    // Calculate the K-value that takes into account the velocities of both balls.
    // A1 = v1 ⋅ n
    // A2 = v2 ⋅ n
    // K =  2(𝑣1 ∙ 𝑛 − 𝑣2 ⋅ 𝑛) / (𝑀1+𝑀2)
    double A1 = b1.getVelocityVectorX() * nx + b1.getVelocityVectorY() * ny;
    double A2 = b2.getVelocityVectorX() * nx + b2.getVelocityVectorY() * ny;
    double K = (2 * (A1 - A2)) / (b1.getMass() + b2.getMass());
    
    // Update the new velocity of each ball using K-value
    // 𝑣1′ =𝑣1−𝐾∗𝑀2∗𝑛
    // 𝑣2′ =𝑣2+𝐾∗𝑀1∗𝑛
    b1.setVelocityVector(b1.getVelocityVectorX() - K * b2.getMass() * nx, b1.getVelocityVectorY() - K * b2.getMass() * ny);
    b2.setVelocityVector(b2.getVelocityVectorX() + K * b1.getMass() * nx, b2.getVelocityVectorY() + K * b1.getMass() * ny);
}

void myIdle() {

    t = 1;
    //if(t > 1) { t = 0; }
    
    int counter = 0;  //for j
    
    // Ball animation. Update coordinates of active balls.
    for (int i = 0; i < noOfBalls; i++) {
        
        int id = balls[i].getId();
        int radius = balls[i].getRadius();
        double m_x = balls[i].getX();
        double m_y = balls[i].getY();
        double m_vectorX = balls[i].getVelocityVectorX();
        double m_vectorY = balls[i].getVelocityVectorY();
        
        // Handle wall boundary collisions
        if ( m_x-radius <= lt ) {
            
            std::cout << "LEFT BOUNDARY REACHED ball" << id << std::endl;
            
            calcVectorReflection(m_vectorX, m_vectorY, -1, 0);
            balls[i].setCoord(lt+radius, m_y);
            
        } else if ( m_x+radius >= rt ) {
            
            std::cout << "RIGHT BOUNDARY REACHED ball" << id << std::endl;
            
            calcVectorReflection(m_vectorX, m_vectorY, 1, 0);
            balls[i].setCoord(rt-radius, m_y);
            
        } else if ( m_y-radius <= bt ) {
            
            std::cout << "BOTTOM BOUNDARY REACHED ball" << id << std::endl;
            
            calcVectorReflection(m_vectorX, m_vectorY, 0, 1);
            balls[i].setCoord(m_x, bt + radius);
            
        } else if ( m_y+radius >= tp ) {
            
            std::cout << "TOP BOUNDARY REACHED ball" << id << std::endl;
            
            calcVectorReflection(m_vectorX, m_vectorY, 0, -1);
            balls[i].setCoord(m_x, tp - radius);
        }
        
        // Update velocity vector from wall calculations
        balls[i].setVelocityVector(m_vectorX, m_vectorY);
        
        // Handle ball-to-ball collisions
        
        for (int j = counter; j < noOfBalls; j++) {
            
            if (i != j) {
                // check if edges touch.
                // calc distance b/w center of two balls and compare if <= combined radiuses
                double distance = sqrt( pow(balls[i].getX() - balls[j].getX(), 2) + pow(balls[i].getY() - balls[j].getY(), 2) );
                
                if (distance <= balls[i].getRadius() + balls[j].getRadius()) {
                    std::cout << "### collision ###" << balls[i].getId() << " " << balls[j].getId() << std::endl;
                    calcBallCollision(balls[i], balls[j]);
                }
            }
        }
        
        // Move ball and update velocity vectors
        balls[i].move();

        counter++;
    }
    
    glutPostRedisplay();
}

// <<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    
    drawCircles();
    
    if (selected) {
        //std::cout << "left mouse clicked" << std::endl;
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
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(screenWidth, screenHeight); // set window position on screen
    glutCreateWindow("Computer Graphics - HW1"); // open the screen window
    
    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutIdleFunc(myIdle);
    
    myInit();
    
    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}
