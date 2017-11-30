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
#include "mesh.h"

// For extrusion. To rotate the polyline to K equi-spaced angles about the y-axis
int K = 36;

// constructor
Mesh:: Mesh()
{
    numVerts=0;
    ready2draw=0;
    numFaces=0;
    norm=NULL;
    face=NULL;
    material=0;
}

// destructor
Mesh::     ~Mesh()
{
    if(numVerts !=0) {
        delete[] pt;
        delete[] norm;
        delete[] face;
    }
}

// use OpenGL to draw this mesh in solid object mode
void Mesh:: drawSolid() // use OpenGL to draw this mesh
{
    // GOLD
    GLfloat ambG[] = {0.24725, 0.1995, 0.0745, 1.0};
    GLfloat diffG[] = {0.75164, 0.60648, 0.22648, 1.0};
    GLfloat specG[] = {0.628281, 0.555802, 0.366065, 1.0};
    GLfloat shininessG[] = {0.4f};
    
    // red PLASTIC
    GLfloat ambP[] = {0, 0, 0, 1.0};
    GLfloat diffP[] = {0.5, 0, 0, 1.0};
    GLfloat specP[] = {0.7, 0.6, 0.6, 1.0};
    GLfloat shininessP[] = {0.25f};
    
    if(ready2draw) {
        
        glPushMatrix();
        
        if (material == 0) {
            // GOLD
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambG);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffG);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specG);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininessG);
            glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.8f,0.8f,0.1f);
        } else if (material == 1) {
            // red PLASTIC
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambP);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffP);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specP);
            glMaterialfv(GL_FRONT, GL_SHININESS, shininessP);
            glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
            glEnable(GL_COLOR_MATERIAL);
            glColor3f(0.8f,0.1f,0.1f);
        }
        
        for(int f = 0; f < numFaces; f++) // draw each face
        {
            glBegin(GL_POLYGON);
            for(int v = 0; v < face[f].nVerts; v++) // for each one..
            {
                int in = face[f].vert[v].normIndex ; // index of this normal
                int iv =  face[f].vert[v].vertIndex ; // index of this vertex
                //glNormal3f(norm[in].x, norm[in].y, norm[in].z);
                glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
            }
            glEnd();
        }
        glPopMatrix();
    }
}

// use OpenGL to draw this mesh in wireframe mode
void Mesh:: drawWireframe()
{
    if(ready2draw) {
        for(int f = 0; f < numFaces; f++) // draw each face
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINE_LOOP);
            for(int v = 0; v < face[f].nVerts; v++) // for each one..
            {
                int iv =  face[f].vert[v].vertIndex ; // index of this vertex
                glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
            }
            glEnd();
        }
    }
}

void Mesh:: initPrism(int N)
{
    numVerts = N;
    numNormals = N; //no +2 b/c will be no base and cap b/c of extrusion
    numFaces = N;   //no +2 b/c will be no base and cap b/c of extrusion
    
    pt = new Point3[numVerts];
    norm = new Vector3[numNormals];
    face = new Face[numFaces];
}

void Mesh:: calcNormals()
{
    // Newell's Method for Normals
    // Assume polygon is given vertices v1, v2, ... vn and each vi = (xi, yi, zi)
    // Plane equation Ax+By+Cz+D=0, is given by (X-P) dot N = 0
    // where X=(x,y,z), N=(A,B,C)=(nx,ny,nz) is the normal to the plane, P is point on the plane
    
    // For each face..
    for (int f = 0; f < numFaces; f++) {
        
        float nx=0, ny=0, nz=0; // the normal n = (nx,ny,nz)
        
        // traverse vertices counter-clockwise from outside..
        for (int i = 0; i < face[f].nVerts; i++) { // Solve plane equation using n vertices
            int vertIndex = face[f].vert[i].vertIndex;
            int nextIndex = (i+1) % face[f].nVerts; // define ni = (i+1) mod N
            
            nx += (pt[vertIndex].y - pt[nextIndex].y) * (pt[vertIndex].z + pt[nextIndex].z);
            ny += (pt[vertIndex].z - pt[nextIndex].z) * (pt[vertIndex].x + pt[nextIndex].x);
            nz += (pt[vertIndex].x - pt[nextIndex].x) * (pt[vertIndex].y + pt[nextIndex].y);

            face[f].vert[i].normIndex = f;
        }
        
        norm[f] = Vector3 (nx,ny,nz); // the normal points to outside(front) of the face
    }
}

// perform extrusion of base triangle along positive z-axis. generate lists of vertices and faces
void Mesh:: createPrism(int N, Point3 *p, float length)
{
    std::cout << "createPrism called, K=" << K << std::endl;
    
    initPrism(N*K); // initialize the prism, N*K vertices
    
    for (int i = 0; i < N; i++) {
        // EXTRUDED vertex list. Polyline extrusion along y-axis rotation
        // K equidistant angles about the y-axis: ANGLEi = 2*PI*(i/K), i=0..K
        for (int k = 0; k < K; k++) {
            float angle = 2*3.14159265*(float(k)/K);
            
            // p * M'
            int revX = p[i].x*cos(angle) + p[i].y*0 + p[i].z*-sin(angle) + 1*0;
            int revY = p[i].x*0 + p[i].y*1 + p[i].z*0 + 1*0;
            int revZ = p[i].x*sin(angle) + p[i].y*0 + p[i].z*cos(angle) + 1*0;
            //int hom = p[i].x*0 + p[i].y*0 + p[i].z*0 + 1*1;
            
            int currPt = i*K + k;
            pt[currPt] = Point3 (revX, revY, revZ);
            
            std::cout << "i=" << i << " k=" << k << " pt[" << currPt << "], extruded verts: " << pt[currPt].x << ", " << pt[currPt].y << ", " << pt[currPt].z << std::endl;
        }
    }
    
    // create N*K side faces
    // for the jth side face, (j=0..N-1), four vertices are at j, j+N, (j+1)%N + N, (j+1)%N
    for (int n = 0; n < N; n++) {
        for (int k = 0; k < K; k++) { //36 extruded points
            
            int f = n*K + k;
            face[f].nVerts = 4;
            face[f].vert = new VertexID[4];
            
            if (f%K == K-1) { // TODO: if last vertex, connect to base vertices
                face[f].vert[0].vertIndex = (n*K) +k;
                face[f].vert[1].vertIndex = 35;
                face[f].vert[2].vertIndex = 2;
                face[f].vert[3].vertIndex = 0;
            } else {
                face[f].vert[0].vertIndex = (n*K) +k;
                face[f].vert[1].vertIndex = (n*K) +k+1;
                
                if ( n+1 < N ) {
                    face[f].vert[2].vertIndex = (n+1)*K +k+1;
                    face[f].vert[3].vertIndex = (n+1)*K +k;
                } else {
                    face[f].vert[2].vertIndex = k+1;
                    face[f].vert[3].vertIndex = k;
                }
            }
            
            std::cout << "face[" << f << "]: " << face[f].vert[0].vertIndex << "," << face[f].vert[1].vertIndex << "," << face[f].vert[2].vertIndex << "," << face[f].vert[3].vertIndex << std::endl;
        }
    }
    
    calcNormals(); // generate each face normal
    
    // when all is done, ready2draw=1;
    ready2draw = 1;
}

//void Mesh::createPrism(int noVerts, std::vector<Point3> p, float length) {
//    
//}

void Mesh::setMaterial(int m) {
    material = m;
}
