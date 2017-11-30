//Lab: Camera Control

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
#include <iostream>

#include "Lab-Camera.h"

// Current mouse location and clicked point location.
Point currentPoint;
bool moveCam = false;
bool shiftKey = false;
float camRadius = 5;
float oAngleDegree = 45;
float eAngleDegree = 45;
float camX = 4.0;
float camY = 4.0;
float camZ = 4.0;
/*
 * eye parameters: d, distance to origin
 *                 angle1, angle around y-axis, as measured from positive x-axis
 *                 angle2, angle up from x-z plane, clamped to [0:Pi/2]
 */
float d, angle1, angle2;
bool materialToggle = false;
bool objectControl = false;

//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);  // background is black
	glColor3f(1.0f, 1.0f, 1.0f);    // drawing color is white

	// set the view volume shape ----
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
    
    gluPerspective(50.0f, 64.0f/48.0f, 0.5f, 200.0f);
    glOrtho(-worldWidth/2, worldWidth/2, -worldHeight/2, worldHeight/2, 0.1, 120);
	//---------------------------

    // ### Lighting Settings
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv (GL_LIGHT0, GL_POSITION, litePos);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    // attach them to GL_LIGHT0
//    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
//
//    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
	
    float oAngle = 3.14159265/180 * oAngleDegree;
    float eAngle = 3.14159265/180 * eAngleDegree;
    camX = camRadius * cos(oAngle) * cos(eAngle);
    camY = camRadius * sin(oAngle) * cos(eAngle);
    camZ = camRadius * sin(eAngle);
    
    //make the initial camera
	cam.set(Point3(camX, camY, camZ), Point3(0, 0, 0), Vector3(0, 1, 0));
}

void animateCamera() {
    
    if (cameraAnimFrame < 1000) {
        camX = 10 * cos(cameraAngle);
        camZ = 10 * sin(cameraAngle);
        cameraAngle += 2 * 3.14159265 / 1000;
        cameraAnimFrame++;
    } else {
        cameraAnimFrame = 0;
        cameraAngle = 0;
    }
    
    cam.set(Point3(camX, camY, camZ), Point3(0, 0, 0), Vector3(0, 1, 0));
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{	
	case GLUT_KEY_LEFT:   
		std::cout << "Camera move left" << std::endl;
		cam.slide(-0.2,0,0); 
		break; 
	case GLUT_KEY_RIGHT: 
		std::cout << "Camera move right" << std::endl;
		cam.slide(0.2,0,0); 
		break;
	case GLUT_KEY_UP:  
		std::cout << "Camera move up" << std::endl;
		cam.slide(0,0.2,0); 
		break; 		
	case GLUT_KEY_DOWN: 
		std::cout << "Camera move down" << std::endl;
		cam.slide(0,-0.2,0); 
		break; 		
	case GLUT_KEY_PAGE_UP:
		// slide camera forward
		std::cout << "Camera zoom-in" << std::endl;
        cam.slide(0,0,-0.2);
		break;
	case GLUT_KEY_PAGE_DOWN:
		// slide camera backward
		std::cout << "Camera zoom-out" << std::endl;
        cam.slide(0,0,0.2);
		break;
	default:
		break;
	}	
	glutPostRedisplay(); // draw it again
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{	
	case 'r':  
		std::cout << "Camera roll counter clock-wise " << std::endl;
		cam.roll(1.0); 
		break; // roll the camera 
	case 'R': 
		std::cout << "Camera roll clock-wise" << std::endl;
		cam.roll(-1.0); 
		break; // roll the camera back	
	case 'p':    
		std::cout << "Camera pitch up" << std::endl;
		// complete pitch function in camera.cpp and invoke cam.pitch() function
        cam.pitch(-1.0);
		break; 
	case 'P':    
		std::cout << "Camera pitch down" << std::endl;
		// complete pitch function in camera.cpp and invoke cam.pitch() function
        cam.pitch(1.0);
		break; 
	case 'y':    
		std::cout << "Camera yaw left" << std::endl;
		// complete yaw function in camera.cpp and invoke cam.yaw() function
        cam.yaw(-1.0);
		break; 
	case 'Y':    
		std::cout << "Camera yaw right" << std::endl;
		// complete yaw function in camera.cpp and invoke cam.yaw() function
        cam.yaw(1.0);
		break;
    case 'l':
        std::cout << "Toggle Rotate/Translate movement of Camera." << std::endl;
        shiftKey = !shiftKey;
        break;
    case 32: // spacebar
        std::cout << "Ready camera view for drawing polygon." << std::endl;
        cam.set(Point3(0,0,15), Point3(0,0,0), Vector3(0, 1, 0));
        break;
    case 'w': //display wireframe mode
        displayMode = (displayMode + 1) % 2;
        break;
    case 'm':
        // move camera along predefined path to show object clearly
        std::cout << "Toggle predefined camera path." << std::endl;
        cameraAnimation = !cameraAnimation;
        break;
    case 'f':
        // make camera focus on the object
        cam.set(Point3(camX, camY, camZ), Point3(0, 0, 0), Vector3(0, 1, 0));
        break;
    case 'c':
        // clear the screen and ready to create new model
        triPrism = Mesh();
        base.clear();
        NoOfPts=0;
        break;
    case 'g':
        // toggle the model to render b/w gold and plastic materials
        materialToggle = !materialToggle;
        triPrism.setMaterial(materialToggle);
        break;
    case 'o':
        // toggle- allow the uwer to translate, rotate, uniform-scale the rendered object using mouse
        std::cout << "Toggle object control mode for mouse." << std::endl;
        objectControl = !objectControl;
        if (objectControl) {moveCam = false;} //turn off camera move controls when in object control mode
            if (!objectControl) {objectRotateMode=false;}
        break;
    case 'z':
        // toggle z rotation of object
            std::cout << "objectRotateModeIndex before: " << objectRotateModeIndex << std::endl;
        if (objectRotateMode) {
            if (objectRotateModeIndex < 2) {
                std::cout << "< 2" << objectRotateModeIndex << std::endl;
                objectRotateModeIndex++;
            } else {
                std::cout << "else" << objectRotateModeIndex << std::endl;
                objectRotateModeIndex = 0;
            }
        }
            std::cout << "objectRotateModeIndex after: " << objectRotateModeIndex << std::endl;
        break;
	default:
		break;
	}
    
	glutPostRedisplay(); // draw it again
}

// Allow the user to translate and rotate the camera via mouse controls (like Blender)
void mouseControl(int button, int state, int x, int y)
{
    // middle button is pressed. rotate camera
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN && !objectControl) {
        std::cout << "middle mouse button pressed" << std::endl;
        // Update the location of the current point as the mouse moves with button pressed.
        currentPoint.setCoords(x, screenHeight - y);
        moveCam = true;

        // 𝑑(𝑃1,𝑃2)=√(𝑥2 −𝑥1)2 +(𝑦2 −𝑦1)2 +(𝑧2 −𝑧1)2
        d = sqrt(pow(camX - 0.0, 2) + pow(camY - 0.0,2) + pow(camZ - 0.0,2));
        Vector3 *v1 = new Vector3(camX, camY, camZ);
        v1->normalize();
        
        angle1 = acos(v1->dot(Vector3(1.0, 0.0, 0.0)));
        
        float clamp = v1->dot(Vector3(0.0, 0.0, 1.0));
        if (clamp < 0) {
            clamp = 0.0;
        } else if (clamp > 3.14159265/2) {
            clamp = 3.14159265/2;
        }
        angle2 = acos(clamp);
        
        float t = d*cos(angle2);   // distance to y-axis after being rotated up
        camY = d*sin(angle2);
        camX = t*cos(angle1);
        camZ = t*sin(angle1);
        cam.set(Point3(camX, camY, camZ), Point3(0, 0, 0), Vector3(0, 1, 0));
        
        std::cout << "angle1 " << angle1 << "angle2 " << angle2 << std::endl;
    }
    // middle button is released.
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP && !objectControl) {
        std::cout << "middle mouse button released" << std::endl;
        moveCam = false;
    }

    // left mouse click to draw polygon
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !objectControl)
    {
        int ry = screenHeight-y;
        base[NoOfPts] = Point3(x*worldWidth/(float)screenWidth-worldWidth/2,
                          ry*worldHeight/(float)screenHeight-worldHeight/2,
                          0);
        NoOfPts++;
    }
    
    // right mouse click to get last vertex
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !objectControl)
    {
        int ry = screenHeight-y;
        base[NoOfPts] = Point3(x*worldWidth/(float)screenWidth-worldWidth/2,
                               ry*worldHeight/(float)screenHeight-worldHeight/2,
                               0);
        NoOfPts++;
        
        if(!triPrism.ready2draw) {
            int length=10; //TODO: remove this?
            // https://stackoverflow.com/questions/2923272/how-to-convert-vector-to-array-in-c
            Point3* baseArray = &base[0];
            triPrism.createPrism(3, baseArray, length);
        }
    }
    
    // ### OBJECT CONTROLS WITH MOUSE
    if(button == GLUT_LEFT_BUTTON && objectControl)
    {
        if (state == GLUT_DOWN) {
            objectScaleMode = true;
            currentPoint.setCoords(x, screenHeight - y);
        } else if (state == GLUT_UP) {
            objectScaleMode = false;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && objectControl)
    {
        if (state == GLUT_DOWN) {
            objectRotateMode = true;
            currentPoint.setCoords(x, screenHeight - y);
        } else if (state == GLUT_UP) {
//            objectRotateMode = false;
        }
    }
    
    glutPostRedisplay();
}

// Mouse motion callback routine.
void mouseMotion(int x, int y)
{
    if (moveCam) {
        
        if (shiftKey) { //check movement mode if 'c' has been toggled (to simulate Blender's shift key)
            std::cout << "move camera shift mode" << std::endl;
            float xMove = 0, yMove = 0;
            
            if (x - currentPoint.xVal > 0) { // mouse right, camera moves left
                xMove = -0.2;
            } else if (x - currentPoint.xVal < 0) { // mouse left, camera moves right
                xMove = 0.2;
            }
            
            if (y - currentPoint.yVal > 0) {    // mouse up, camera moves down
                yMove = -0.2;
            } else if (y - currentPoint.yVal < 0) { // mouse down, camera moves up
                yMove = 0.2;
            }
            
            cam.slide(xMove,yMove,0);
            
        } else {
            /* PARAMETRIC SPHERE EQUATION - DOESN'T WORK SO WELL
            // parametric eq of sphere. orientation angle α.  elevation angle β
            // x = r cosα cosβ
            // y = r sinα cosβ
            // z = r sinβ
            
            if (x - currentPoint.xVal > 0) {
                oAngleDegree += 1;
            } else if (x - currentPoint.xVal < 0) {
                oAngleDegree -= 1;
            }
            
            if (y - currentPoint.yVal > 0) {
                eAngleDegree += 1;
            } else if (y - currentPoint.yVal < 0) {
                eAngleDegree -= 1;
            }
            
            // update currentPoint
            currentPoint.setCoords(x, screenHeight - y);
            
            float oAngle = 3.14159265/180 * oAngleDegree;
            float eAngle = 3.14159265/180 * eAngleDegree;
            
            // If mouse moves up, camera moves down on y axis along the sphere surface
            // If mouse moves down, camera moves up
            camX = camRadius * cos(oAngle) * cos(eAngle);
            camY = camRadius * sin(oAngle) * cos(eAngle);
            camZ = camRadius * sin(eAngle);
            
            // Move camera
            cam.set(Point3(camX, camY, camZ), Point3(0, 0, 0), Vector3(0, 1, 0));
            */
            
            float gain=2.5; //arbitrary value
            float dx = gain*(x-currentPoint.xVal)/screenWidth;
            float dy = gain*(y-currentPoint.yVal)/screenHeight;
            
            float newAngle1 = angle1 + dx;
            float newAngle2 = angle2 + dy;
            std::cout << "newAngle1 " << newAngle1 << "newAngle2 " << newAngle2 << std::endl;
            
            // Recompute eye's x,y,z coordinates
            float t = d*cos(newAngle2);   // distance to y-axis after being rotated up
            camY = d*sin(newAngle2);
            camX = t*cos(newAngle1);
            camZ = t*sin(newAngle1);
            cam.set(Point3(camX, camY, camZ), Point3(0, 0, 0), Vector3(0, 1, 0));
        }
    } else if (objectScaleMode) {
        if (currentPoint.xVal < x) {
            if (objectScale < 5) {
                objectScale += 0.01; // scale object up
            }
        } else if (currentPoint.xVal > x) {
            if (objectScale > 0) {
                objectScale -= 0.01; // scale object down
            }
        }
    } else if (objectRotateMode) {
        if (objectRotateModeIndex == 0) {
            std::cout << "objectRotateModeIndex == 0" << std::endl;
            if (currentPoint.xVal < x) {
                if (objectRotateX < 360) {
                    objectRotateX += 2;
                }
            } else if (currentPoint.xVal > x) {
                if (objectRotateX > 0) {
                    objectRotateX -= 2;
                }
            }
        } else if (objectRotateModeIndex == 1) {
            std::cout << "objectRotateModeIndex == 1" << std::endl;
            if (currentPoint.yVal < y) {
                objectRotateY += 2;
            } else if (currentPoint.yVal > y) {
                objectRotateY -= 2;
            }
        } else if (objectRotateModeIndex == 2) {
            std::cout << "objectRotateModeIndex == 2" << std::endl;
            if (currentPoint.yVal < y) {
                objectRotateZ += 2;
            } else if (currentPoint.yVal > y) {
                objectRotateZ -= 2;
            }
        }
    }
    glutPostRedisplay();
}

void drawAxes()
{
    glBegin(GL_LINES);
    
    glColor3f(0.3f, 0.3f, 0.3f);
    
    int gridsize = 10;
    int linesize = 5;
    for (int i = -gridsize; i <= gridsize; i+=2) {
        glVertex3f(i*linesize,0,-gridsize*linesize);
        glVertex3f(i*linesize,0,gridsize*linesize);
        glVertex3f(-gridsize*linesize,0,i*linesize);
        glVertex3f(gridsize*linesize,0,i*linesize);
    }
    
    //x, red
    glColor3f(100.0f, 0.0f, 0.0f);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    //y, green
    glColor3f(0.0f, 100.0f, 0.0f);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
    //z, blue
    glColor3f(0.0f, 0.0f, 100.0f);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    
    glEnd();
}
//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    drawAxes();
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidCube(1);
    
    if(!triPrism.ready2draw) {
        // draws a polygon based on the input
        if(NoOfPts>2) {
            glColor3f(0.5f, 0.5f, 0.5f);
            glBegin(GL_POLYGON);
            for(int i=0; i<NoOfPts; i++)
                glVertex3f(base[i].x, base[i].y, base[i].z);
            glEnd();
        }
    } else {
        glPushMatrix();
        glScaled(objectScale, objectScale, objectScale);
        glRotated(objectRotateX, 0, 1, 0);
        glRotated(objectRotateY, 1, 0, 0);
        glRotated(objectRotateZ, 0, 0, 1);
        if(displayMode)
            triPrism.drawWireframe();
        else
            triPrism.drawSolid();
        glPopMatrix();
    }
    
	glutSwapBuffers();	
}

void myIdle()
{
    if (cameraAnimation) { animateCamera(); }
    glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("HW3"); // open the screen window

	// register callback functions
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
    
    // Register the mouse callback function.
    glutMouseFunc(mouseControl);
    // Register the mouse motion callback function.
    glutMotionFunc(mouseMotion);
    
    glutDisplayFunc(myDisplay);

	myInit();

    glutIdleFunc(myIdle);
	glutMainLoop();

	return( 0 );
}
