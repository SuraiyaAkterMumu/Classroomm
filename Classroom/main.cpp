#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "gl\glut.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<ctime>
#include<time.h>
#include<bits/stdc++.h>
#include "include/BmpLoader.h"
using namespace std;

double Txval=0,Tyval=0,Tzval=0, Bxval=0,Cxval=0,Lzval=0, Rzval=0;
double windowHeight=1400, windowWidth=1400;
//double eyeX=0, eyeY=2, eyeZ=261, refX = 0, refY=2,refZ=240, upX = 0, upY = 1,upZ = 0;
double eyeX=0, eyeY=4, eyeZ=22, refX = 0, refY=4,refZ=8, upX = 0, upY = 1,upZ = 0;
//double eyeX=0, eyeY=185, eyeZ=136, refX = 0, refY=185,refZ=122, upX = 0, upY = 1,upZ = 0;//0 185 136 0 185 122
//GLfloat alpha1 = 0.0, theta1 = 0.0, axis_x1=0.0, axis_y1=0.0, angle_y1=0.0,angle_x1=0.0,angle_z1=0.0;
//GLfloat alpha2 = 0.0, theta2 = 0.0, axis_x2=0.0, axis_y2=0.0, angle_y2=0.0,angle_x2=0.0,angle_z2=0.0;
//GLfloat alpha3 = 0.0, theta3 = 0.0, axis_x3=0.0, axis_y3=0.0, angle_y3=0.0,angle_x3=0.0,angle_z3=0.0;
//GLfloat alpha4 = 0.0, theta4 = 0.0, axis_x4=0.0, axis_y4=0.0, angle_y4=0.0,angle_x4=0.0,angle_z4=0.0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, angle_y=0.0,angle_x=0.0,angle_z=0.0;
GLboolean bRotate = false, uRotate = false;
GLfloat nearPLane = 3, farPlane = 300;
GLfloat dx, dy, dz, dxyz;
double limit = 360;
double roll_value = 1;
double xx=20,d=0;


GLfloat angleYaw = 90.0, anglePitch = 270.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 360.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 180.0;
GLfloat dangle = 0.0;

double scale_x = 1;
double scale_y = 1;
double scale_z = .8;
double scale_projector_curtain=0;
double translate_projector_curtain=10;

int s=1,p=1;
float k=0.0, k1 = 0.0,k2=0.0, l=0.0;
double kdeg1, kdeg2, kdeg3, kdeg4, hour=0, minute=0, second=0;
int spotlght,fon1, fon2, fon3,fon4,pd;



static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0},  //point index 0
    {2.0, 0.0, 0.0},  //point index 1
    {2.0, 0.0, 2.0},  //point index 2
    {0.0, 0.0, 2.0},  //point index 3
    {0.0, 2.0, 0.0},  //point index 4
    {2.0, 2.0, 0.0},  //point index 5
    {2.0, 2.0, 2.0},  //point index 6
    {0.0, 2.0, 2.0}   //point index 7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 5, 4}, // indices for drawing the triangle plane 1
    {1, 2, 6, 5}, // indices for drawing the triangle plane 2
    {2, 3, 7, 6}, // indices for drawing the triangle plane 3
    {3, 0, 4, 7},  // indices for drawing the triangle plane 4
    {0, 1, 2, 3}, // indices for drawing the triangle plane 5
    {4, 5, 6, 7}  // indices for drawing the triangle plane 6
};


static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void solid(float col_a,float col_b,float col_c)
{

    GLfloat mat_ambient[] = { col_a*0.5, col_b*0.5, col_c*0.5, 1.0 };
    GLfloat mat_diffuse[] = {  col_a, col_b, col_c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glutSolidSphere (3.0, 20, 16);

}


void drawCube(float a,float b,float c,float shine = 60)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a,b,c,0.3};
    GLfloat mat_diffuse[] = {  a,b,c,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
//        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
//                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
//                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}

void drawwireCube1(float a,float b,float c)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a,b,c,0.3};
    GLfloat mat_diffuse[] = {  a,b,c,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glBegin(GL_LINES);
    for (GLfloat i = -2; i <= 2; i += .50)
    {
        glVertex3f(i, 2, 0);
        glVertex3f(i, -2, 0);
        glVertex3f(2, i, 0);
        glVertex3f(-2, i, 0);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}

void triangularPrism(float a,float b,float c, float shine=60)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a,b,c,0.3};
    GLfloat mat_diffuse[] = {  a,b,c,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
        glVertex3f(0.5, 0, 0.5);glTexCoord2f(1,1);
        glVertex3f(0.5, 0, -0.5);glTexCoord2f(1,0);
        glVertex3f(-0.5, 0, -0.5);glTexCoord2f(0,0);
        glVertex3f(-0.5, 0, 0.5);glTexCoord2f(0,1);

        glVertex3f(0.5,0,-0.5);glTexCoord2f(1,1);
        glVertex3f(0.5,1,-0.5);glTexCoord2f(1,0);
        glVertex3f(-0.5,1,-0.5);glTexCoord2f(0,0);
        glVertex3f(-0.5,0,-0.5);glTexCoord2f(0,1);

        glVertex3f(0.5,1,-0.5);glTexCoord2f(1,1);
        glVertex3f(-0.5,1,-0.5);glTexCoord2f(1,0);
        glVertex3f(-0.5,0,0.5);glTexCoord2f(0,0);
        glVertex3f(0.5,0,0.5);glTexCoord2f(0,1);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(0.5,0,0.5);glTexCoord2f(0,0);
        glVertex3f(0.5,1,-0.5);glTexCoord2f(1,0);
        glVertex3f(0.5,0,-0.5);glTexCoord2f(0,1);

        glVertex3f(-0.5,0,0.5);glTexCoord2f(1,0);
        glVertex3f(-0.5,1,-0.5);glTexCoord2f(0,1);
        glVertex3f(-0.5,0,-0.5);glTexCoord2f(1,1);
    glEnd();
}

void light0(int on)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = { .296, 0.2764, .2882,0.3};
    GLfloat light_diffuse[]  = { .292, 0.2529, .2765, .3 };
    GLfloat light_specular[] = { 1, 1, 1, 1.0 };
    GLfloat light_position[] = { -2,13,10.4,1};

    if(on==1)
    {
        glEnable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    }
    else if(on==0)
    {
        glDisable( GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    }

}
void light1(int on)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = { .296, 0.2764, .2882,0.3};
    GLfloat light_diffuse[]  = { .292, 0.2529, .2765, .3 };
    GLfloat light_specular[] = { 1, 01, 01, 1.0 };
    GLfloat light_position[] = { -2,12.8,8.4,1};

    if(on==1)
    {
//        cout<<"light1--"<<GL_LIGHT1<<endl;
        glEnable( GL_LIGHT2);
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
        glLightfv( GL_LIGHT2, GL_POSITION, light_position);

    }
    else if(on==0)
    {
        glDisable( GL_LIGHT2);
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
        glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    }

}

void spotlight(int sptlght)
{
    GLfloat no_lights[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambients[]  = {.992, 0.9529, .7765, 1.0};
    GLfloat light_diffuses[]  = { .992, 0.9529, .7765, 1.0 };
    GLfloat light_speculars[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_positions[] =  { .8,8,5.5 };
    if(sptlght==0)
    {
        glEnable(GL_LIGHT1);
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_lights);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_lights);
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_lights);
        glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==1)
    {
        glEnable(GL_LIGHT1);
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
        glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==2)
    {
        glEnable(GL_LIGHT1);
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_lights);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
        glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==3)
    {
        glEnable(GL_LIGHT1);
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_lights);
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_speculars);
        glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }
    else if(sptlght==4)
    {
        glEnable(GL_LIGHT1);
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambients);
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuses);
        glLightfv( GL_LIGHT1, GL_SPECULAR,no_lights);
        glLightfv( GL_LIGHT1, GL_POSITION, light_positions);
    }

    GLfloat spt_dir[] = {0,0,-1};
    GLfloat spt_ct[] = {43};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spt_dir);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);


}


void sky()
{
    /// piser akash
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-208,-4,-30);
    glScalef(208,200,.2);

    drawCube(1.0, 1.0, 1.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    /// left side er akash
    glPushMatrix();
    glTranslatef(-208,-4,-30);
    glScalef(.2,200,100);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();

    /// right side er akash
    glPushMatrix();
    glTranslatef(208,-4,-30);
    glScalef(.2,200,100);
    drawCube(1.0, 1.0, 1.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

///    top side er akash
    glPushMatrix();
    glTranslatef(-208,396,-30);
    glScalef(208,.1,100);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawCube(1.0, 1.0, 1.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPopMatrix();

}

void grass()
{
    ///tola
    glPushMatrix();
    glTranslatef(-208,-4,-30);
    glScalef(208,.1,50);
    glBindTexture(GL_TEXTURE_2D, 16);
    glEnable(GL_TEXTURE_2D);
    drawCube(1.0, 1.0, 1.0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void color(float a, float b, float c, float shine = 60){
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a,b,c,1.0};
    GLfloat mat_diffuse[] = {  a,b,c,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}


void light()
{
    glPushMatrix();
    glTranslated(-6,12.9,-5);
    glScaled(3.5,.05,.3);
    drawCube(0.546875,0.546875,0.546875);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,12.9,8);
    glScaled(3.5,.05,.3);
    drawCube(0.546875,0.546875,0.546875);
    glPopMatrix();


    GLUquadricObj *quad;
    quad = gluNewQuadric();

    ///rod light
    glPushMatrix();
    if(s==1)
        color(1,1,1,100);
    else
        color(0.3,0.3,0.3,0);
    glTranslated(-6,12.8,8.4);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.1, 0.1, 7, 32, 32);
    glPopMatrix();

    glPushMatrix();
    if(s==0 && p==1)
    color(1,1,1,100);
    else if(s==1 && p==0)color(0.1,0.1,0.1,0);
    glTranslated(-6,12.8,-4.6);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.1, 0.1, 7, 32, 32);
    glPopMatrix();

    /// rod light er dui paser disk
    glPushMatrix();
    color(0.546875,0.546875,0.546875);
    glTranslated(-6,12.8,8.35);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, 0.1, 0.2,32, 32);
    glPopMatrix();

    glPushMatrix();
    color(0.546875,0.546875,0.546875);
    glTranslated(1,12.9,8.4);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, 0.1, 0.2,32, 32);
    glPopMatrix();

    glPushMatrix();
    color(0.546875,0.546875,0.546875);
    glTranslated(-6,12.8,-4.6);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, 0.1, 0.2,32, 32);
    glPopMatrix();

    glPushMatrix();
    color(0.546875,0.546875,0.546875);
    glTranslated(1,12.9,-4.6);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, 0.1, 0.2,32, 32);
    glPopMatrix();




}
void wall_sets()
{

    glTranslatef(-10,0,0);
    glPushMatrix(); //....................................begin of walls.................................

//    standing floor
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(12.5,0.3,2);
    drawCube(0.0f, 0.0, 0.69921875);
    glPopMatrix();

    /// floor

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 11);
    glPushMatrix();

    glTranslatef(-8,-3.1,-10);
    glScalef(15.2,0.05,12.5);

    drawCube(1.0, 1.0, 1.0);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///   ceil
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,13,-10);
    glScalef(15.2,0.05,12.5);
    drawCube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    /// left wall
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(0.25,8,3.5);
    drawCube(0.69921875,0.69921875,0.69921875);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,7,-3);
    glScalef(0.25,3,2.5);
    drawCube(0.69921875,0.69921875,0.69921875);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //last wall
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8.05,-3,2);
    glScalef(0.25,8,6.51);
    drawCube(0.69921875,0.69921875,0.69921875);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//    last wall upper layer
    glBindTexture(GL_TEXTURE_2D,12);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,-3,2);
    glScalef(0.25,8,6.5);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // janar nicher part
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.25,2.5,2.5);
    glTranslatef(-32.15,-1.2,-1.2);
    drawCube(0.69921875,0.69921875,0.69921875);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    /// left wall end


    ///right wall start
    glPushMatrix();
    glTranslated(30,0,0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(0.25,8,3.5);
    drawCube(0.69921875,0.69921875,0.69921875);
//    drawCube(1,1,1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,7,-3);
    glScalef(0.25,3,2.5);
    drawCube(0.69921875,0.69921875,0.69921875);
//    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,-3,2);
    glScalef(0.25,8,6.51);
    drawCube(0.69921875,0.69921875,0.69921875);
//    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    glBindTexture(GL_TEXTURE_2D,12);
//    glEnable(GL_TEXTURE_2D);
//    glPushMatrix();
//    glTranslatef(-8.05,-3,2);
//    glScalef(0.25,8,6.5);
//    drawCube(1.0, 1.0, 1.0);
//    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(0.25,2.5,2.5);
    glTranslatef(-32.15,-1.2,-1.2);
    drawCube(0.69921875,0.69921875,0.69921875);
//    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();
    ///right wall end

    ///back wall
    glBindTexture(GL_TEXTURE_2D, 21);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,-3,-10);
    glScalef(15.1,8,0.25);
    drawCube(0.69921875,0.69921875,0.69921875);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///front wall
    glBindTexture(GL_TEXTURE_2D, 20);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,-3,14.55);
    glScalef(4.1,8,0.25);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 20);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(.2,9,14.55);
    glScalef(11.1,2,0.25);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 20);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(8.4,-3,14.55);
    glScalef(7.0,6,0.25);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    ///white board1
    glPushMatrix();
    glPushMatrix();
    glTranslatef(-6,3,-9.5);
    glScalef(12,.10,0.25);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6,3,-9);
    glScalef(12,.10,0.25);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6,9,-9.5);
    glScalef(12,.10,0.25);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6,9,-9);
    glScalef(12,.10,0.25);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(Bxval,0,0);
    glTranslatef(-6,3,-9.5);
    glScalef(6,3,0.25);
    drawCube(1.000, 1.000, 1.000);
    glPopMatrix();
    glPopMatrix();
    ///white board2
    glPushMatrix();
    glPushMatrix();
    glTranslatef(Cxval,0,0);
    glTranslatef(6,3,-9.3);
    glScalef(6,3,0.25);
    drawCube(1.000, 1.000, 0.8);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix(); //..............end of walls................

}

static void torus(int numc, int numt)
{
    int i, j, k;
    double s, t, x, y, z, twopi;
    double PI_ = 3.1416;
    twopi = 2 * PI_;
    for (i = 0; i < numc; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= numt/2; j++)
        {
            for (k = 4; k >= 0; k--)
            {
                s = (i + k) % numc + 0.5;
                t = j % numt;

                x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
                y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
                z = .1 * sin(s * twopi / numc);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
}

void door()
{
    /// door

    glTranslated(d, 0,0);
    glBindTexture(GL_TEXTURE_2D, 15);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-9.8,-3,14.55);
    glScalef(4.4,6,0.25);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();



}

void box()
{


    glPushMatrix();
    /// back side
    glPushMatrix();
    glTranslatef(7,-1.5,-7.5);
    glScalef(1,2,.05);
    drawCube(0.5, 0.0, 1.0);
    glPopMatrix();

    /// left side
    glPushMatrix();
    glTranslatef(9,-1.5,-7.5);
    glScalef(.05,2,.5);
    drawCube(0.5, 0.0, 1.0);
    glPopMatrix();
//
    /// right side
    glTranslatef(6.9,-1.5,-7.5);
    glScalef(.05,2,.5);
    drawCube(0.5, 0.0, 1.0);
//
    glPopMatrix();
//
///    top side
    glPushMatrix();
    glTranslatef(7,2,-7.5);
    glScalef(1,.05,.49);
    drawCube(0.0, 0.0, 0.0);
    glPopMatrix();
    ///    down side
    glPushMatrix();
    glTranslatef(7,-1.5,-7.5);
    glScalef(1,.05,.49);
    drawCube(1.0, 1.0, 1.0);
    glPopMatrix();

    glPopMatrix();
}

void box_door()
{

    /// front door1

    glPushMatrix();
    glScaled(0.5,.85,1);
//    glTranslated(0,0,k);
    drawwireCube1(0.0,0.0,0.0);
    glPopMatrix();


}

void window_frame()
{
//    glTranslatef(-10,0,0);
    glPushMatrix();
    glPushMatrix();
    glScalef(0.05,.10,1.25);
    glTranslatef(-148,68.0,-0.4);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.05,2.50,.10);
    glTranslatef(-148,.80,-5.4);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.05,.10,1.25);
    glTranslatef(-148,20.00,-0.4);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.05,2.50,.10);
    glTranslatef(-148,.80,20);
    drawCube( 0.000, 0.000, 0.0);
    glPopMatrix();
    glPopMatrix();

}

void windows()
{
    glTranslatef(-10,0,0);
    glPushMatrix(); //....................................begin of window.................................
//left window
    glPushMatrix();

    glTranslatef(0,0,Lzval);

    glPushMatrix();

    window_frame();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(0.05,2.50,1.25);
    glTranslatef(-149,.80,-0.4);
    drawCube( 1.000, 1.000, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//    glPushMatrix();
//    glScalef(0.05,2.50,.10);
//    glTranslatef(-150,.80,-5.4);
//    drawCube( 0.000, 0.000, 0.0);
//    glPopMatrix();

    // 2nd part
    glPushMatrix();
    glTranslated(-0.08,0,-2.5);
    window_frame();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glScalef(0.05,2.50,1.25);
    glTranslatef(-150,.80,-2.4);
    drawCube( 1.000, 1.000, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    // 1st right window
    glPushMatrix();
    glTranslatef(0,0,Rzval);
    glPushMatrix();
    glPushMatrix();
    glTranslated(29.3,0,0);
    window_frame();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(0.05,2.50,1.25);
    glTranslatef(439.5,.80,-0.4);
    drawCube(1.000, 1.000, 1.0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslated(29.4,0,-2.5);
    window_frame();
    glPopMatrix();

    glScalef(0.05,2.50,1.25);
    glTranslatef(440.5,.80,-2.4);
    drawCube(1.000, 1.000, 1.0);
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);




    //2nd right window
//    glPushMatrix();
//
//    glScalef(0.05,2,2);
//    glTranslatef(440.5,0,2);
//    drawCube( 1.000, 1.000, 0.941);
//    glPopMatrix();



    glPopMatrix();
}

void door1()
{
    glPushMatrix(); //....................................begin of door.................................
    // door
    glPushMatrix();
    glTranslatef(-7.5,-2.8,-6);
    glScalef(0.08,4,2);
    drawCube(1.000, 1.000, 0.5);
    glPopMatrix();

    //door row1
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-6);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door row2
    glPushMatrix();
    glTranslatef(-7.4,5.2,-6);
    glScalef(0.05,0.05,2);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door col1
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-6);
    glScalef(0.05,4,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    //door col2
//    glPushMatrix();
//    glTranslatef(-7.4,-2.8,-4);
//    glScalef(0.05,4,0.05);
//    drawCube( 0.2, 0.0, 0.0);
//    glPopMatrix();
    //door col3
    glPushMatrix();
    glTranslatef(-7.4,-2.8,-2);
    glScalef(0.05,4,0.05);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();

    //door handle1
    glPushMatrix();
    glTranslatef(-7.2,1.5,-2.4);
    glScalef(0.05,0.5,0.1);
    drawCube( 0.2, 0.0, 0.0);
    glPopMatrix();
    glPopMatrix();
}

void celling_fan()
{




    //body
    glPushMatrix();
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.0,0.0,0.0,0.3};
    GLfloat mat_diffuse[] = {  0.0,0.0,0.0,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslated(0,3,0);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.1, 0.1, 3, 32, 32);
    glPopMatrix();
    glPushMatrix();


    /// 1st

    glPushMatrix();
    glScalef(0.3,0,1.2);
    drawCube(0,0,0);
    glPopMatrix();

    ///2nd
    glPushMatrix();
    glRotatef(60,0,1,0);
    glScalef(0.3,0,1.2);
//    drawcube(0.208,0.231,0.059);
    drawCube(0,0,0);
    glPopMatrix();

    ///3rd

    glPushMatrix();
    //glTranslatef(0,0,2);
    glRotatef(120,0,1,0);
    glScalef(0.3,0,1.2);
//    drawcube(0.208,0.231,0.059);
    drawCube(0,0,0);
    glPopMatrix();

    ///4th
    glPushMatrix();
    //glTranslated(2,0,0);
    glRotatef(180,0,1,0);
    glScalef(0.3,0,1.2);
//    drawcube(0.208,0.231,0.059);
    drawCube(0,0,0);
    glPopMatrix();
///5th
    glPushMatrix();
    //glTranslated(2,0,0);
    glRotatef(240,0,1,0);
    glScalef(0.3,0,1.2);
//    drawcube(0.208,0.231,0.059);
    drawCube(0,0,0);
    glPopMatrix();
///6th
    glPushMatrix();
    //glTranslated(2,0,0);
    glRotatef(300,0,1,0);
    glScalef(0.3,0,1.2);
//    drawcube(0.208,0.231,0.059);
    drawCube(0,0,0);
    glPopMatrix();

    glPopMatrix();
}

void fan()
{


    ///11 fan
    glPushMatrix();
    glTranslatef(5,10,0);
    glRotatef(kdeg1,0,1,0);
    celling_fan();
    glPopMatrix();


    ///12 fan
    glPushMatrix();
    glTranslatef(-10,10,0);
    glRotatef(kdeg2,0,1,0);
    celling_fan();
    glPopMatrix();

    ///21 fan
    glPushMatrix();
    glTranslatef(5,10,8);
    glRotatef(kdeg3,0,1,0);
    celling_fan();
    glPopMatrix();


    ///22 fan
    glPushMatrix();
    glTranslatef(-10,10,8);
    glRotatef(kdeg4,0,1,0);
    celling_fan();
    glPopMatrix();


}

void table_chair()
{


    glPushMatrix();    //.......begin of table.......

    //FLAT
    glBindTexture(GL_TEXTURE_2D, 17);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glRotatef(90,1,0,0);
    glScalef(4.2,2.2,0.05);
    drawCube(0.737, 0.561, 0.561);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //back left leg
    glPushMatrix();
    glRotatef(180,1,0,0);
    glScalef(0.2,3,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //back right leg
    glPushMatrix();
    glTranslatef(8,0,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,3,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //front left leg
    glPushMatrix();
    glTranslatef(0,0,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,3,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //front right leg
    glPushMatrix();
    glTranslatef(8,0,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.8,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //left leg connector
    glPushMatrix();
    glTranslatef(0,-4,0);
    glRotatef(90,1,0,0);
    glScalef(0.2,2,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //right leg connector
    glPushMatrix();
    glTranslatef(8,-4,0);
    glRotatef(90,1,0,0);
    glScalef(0.2,2,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //connect connector
    glPushMatrix();
    glTranslatef(0,-4,2);
    glScalef(4,0.2,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    glPopMatrix();      //......end of table

    glPushMatrix(); //........begin of chair .......
    glTranslated(2,0,1);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    //glRotatef( alpha, axis_x, axis_y, 0.0 );

    //bottom FLAT
    glBindTexture(GL_TEXTURE_2D, 17);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-1,-0.5);
    glRotatef(90,1,0,0);
    glScalef(2.5,2.3,0.05);
    drawCube(0.8, 0.2, 0.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side FLAT
    glBindTexture(GL_TEXTURE_2D, 17);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-1,4);
    glScalef(2.5,2.2,0.05);
    drawCube(0.545, 0.271, 0.075);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //back left leg
    glPushMatrix();
    glTranslatef(0,-1,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    //back right leg
    glPushMatrix();
    glTranslatef(4.5,-1,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    //front left leg
    glPushMatrix();
    glTranslatef(0,-1,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    //front right leg
    glPushMatrix();
    glTranslatef(4.5,-1,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.5, 0.4, 0.2);
    glPopMatrix();

    glPopMatrix(); //..........end of chair........
}

void call_table_chair()
{

    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glTranslatef(0,0,10);

    glPushMatrix();
    glTranslated(-8,0,-20);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-20);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8,0,-12);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-12);
    table_chair();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-8,0,-4);
    table_chair();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-4);
    table_chair();
    glPopMatrix();

    glPopMatrix();

}

void all_table_chair()
{
    //........table chair sets........


    glPushMatrix();
    glTranslatef(4,0,4);
    call_table_chair();
    glTranslatef(-14,0,0);
    call_table_chair();
    glPopMatrix();

}

void clock_kata(double a, double b, double c)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a,b,c,0.5};
    GLfloat mat_diffuse[] = {  a,b,c,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    glPushMatrix();
    glTranslated(-3,11,-9);
    glRotated(hour, 0,0,1);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .05, .05, .5, 32, 32);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-3,11,-9);
    glRotated(minute, 0,0,1);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .04, .04, .6, 32, 32);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-3,11,-9);
    glRotated(second, 0,0,1);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .03, .03, .7, 32, 32);
    glPopMatrix();



}

void wall_clock(double a, double b, double c)
{
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { a,b,c,0.5};
    GLfloat mat_diffuse[] = {  a,b,c,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadricObj *quad;
    quad = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);

    glPushMatrix();
    glTranslated(-3, 11, -9);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, .05,1,30,15);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glPushMatrix();
    glTranslated(-3,11,-9);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .05, .05, .1, 32, 32);
    glPopMatrix();

//    glPushMatrix();
//    glTranslated(-3,11,-9);
//    glScaled(.3, .03,.03);
//    drawCube(0,0,0);
//    glPopMatrix();

    glPushMatrix();
    clock_kata(0,0,0);
    glPopMatrix();

    glPopMatrix();

}

void laptop()
{
    //lower_black
    glPushMatrix();
    glPushMatrix();
    glTranslatef(8.65,-.5,-6.8);
    glScaled(.85,.5,.01);
//    glRotated(-30,1,0,0);
    drawCube(.1,.1,.1);
    glPopMatrix();

    //upper_screen
    glPushMatrix();
    glTranslatef(8.745,-.3,-6.75);
    glScaled(.75,.4,.01);
//    glRotated(-30,1,0,0);
    drawCube(0,0,0);
    glPopMatrix();
    glPopMatrix();


    //keyboard
    glBindTexture(GL_TEXTURE_2D, 9);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(8.65,-.5,-6.8);
    glScaled(.85,.01,0.5);
    drawCube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);





    glPopMatrix();

}


void tul()
{
    glPushMatrix();    //.......begin of table.......

    //FLAT
    glPushMatrix();
    glTranslatef(0,0,-0.5);
    glRotatef(90,1,0,0);
    glScalef(4.2,2.2,0.05);
    drawCube(0.737, 0.561, 0.561);
    glPopMatrix();

    //back left leg
    glPushMatrix();
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //back right leg
    glPushMatrix();
    glTranslatef(8,0,0);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //front left leg
    glPushMatrix();
    glTranslatef(0,0,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();

    //front right leg
    glPushMatrix();
    glTranslatef(8,0,4);
    glRotatef(180,1,0,0);
    glScalef(0.2,2.5,0.2);
    drawCube(0.2, 0.5, 1.0);
    glPopMatrix();
    glPopMatrix();

}


void glass()
{
    glBindTexture(GL_TEXTURE_2D,21);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(0,0,0);
    //glScalef(0.8, 7, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattteoc[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteoc[] = { 1.0,1.0,1.0, 1.0 };
    GLfloat mat_diffusettteoc[] = { 1.0, 1.000, 1.000, 1.0 };
    GLfloat mat_specularttteoc[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteoc[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteoc);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteoc);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteoc);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteoc);

    //drawCube();
    GLUquadric *qd;
    qd = gluNewQuadric();
    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,1.5,1.5,3,20,20);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    ///inner
    glPushMatrix();
    glRotatef(90,1,0,0);

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteoc);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteoc);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteoc);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteoc);

    //drawCube();

    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,1.48,1.48,3,20,20);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



    ///glass base
    glPushMatrix();
    glTranslated(0,-3,0);
    glRotated(90, 1,0,0);
    GLfloat no_mattte[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttte[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettte[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttte[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttte[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttte);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettte);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttte);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttte);

    //drawCube();
    GLUquadric *qdgb;
    qdgb = gluNewQuadric();
    gluQuadricTexture(qdgb, TRUE);
    gluDisk(qdgb,0,1.5,200,200);
    glPopMatrix();

    glPushMatrix();

    ///glass handle
    GLfloat no_mattte1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttte1[] = { 1.,0.,0., 1.0 };
    GLfloat mat_diffusettte1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_specularttte1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_shininessttte1[] = {60};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttte);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettte);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttte);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttte);
    glTranslated(1.5, -1.5, 0);
    glScaled(1,1,2);
    glRotated(-90,0,0,1);
    torus(200,100);
    glPopMatrix();
}

void water_jar()
{
    ///body
//    glBindTexture(GL_TEXTURE_2D,18);
//    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0,0,0,0.3};
    GLfloat mat_diffuse[] = {  1,1,1,1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    GLUquadricObj *quad;
    quad = gluNewQuadric();

    glPushMatrix();
    glTranslatef(10.9,.5,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .5, .5, 1.5, 32, 32);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);


    ///nicher base


    glPushMatrix();
    glTranslatef(10.9,-.8,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);

    gluCylinder(quad, .5, .6, .2, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.9,.6,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .3, .5, .1, 32, 32);

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,18);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    GLfloat no_matt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientt[] = { 1,1,1,0.3};
    GLfloat mat_diffusee[] = {  1,1,1,1.0 };
    GLfloat mat_specularr[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesss[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusee);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularr);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesss);
    glPushMatrix();
    glTranslatef(10.9,.8,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .5, .2, .4, 32, 32);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(10.9,1.8,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .5, .5, 1, 32, 32);
    glPopMatrix();


    glPushMatrix();
    GLfloat no_mattt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttt[] = { 1,1,1,0.3};
    GLfloat mat_diffuseet[] = {  1,1,1,1.0 };
    GLfloat mat_specularrt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessst[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuseet);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularrt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessst);
    glTranslatef(10.9,1.8,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, 0, .5, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    GLfloat no_mattt2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttt2[] = { 0,0,1,0.3};
    GLfloat mat_diffuseet2[] = {  1,1,1,1.0 };
    GLfloat mat_specularrt2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessst2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuseet2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularrt2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessst2);

    glTranslatef(10.1,0,13);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .05, .05, .3, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.14,0,13);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .05, .03, .2, 32, 32);
    glPopMatrix();


    glPopMatrix();

}

void projector()
{


    glPushMatrix();
    GLfloat no_mattt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttt[] = { 0,0,0,1.0};
    GLfloat mat_diffuseet[] = {  1,1,1,1.0 };
    GLfloat mat_specularrt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessst[] = {60};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuseet);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularrt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessst);


    GLUquadricObj *quad;
    quad = gluNewQuadric();

    glTranslated(.8,13,5.5);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.1, 0.1, 4.5, 32, 32);
    glPopMatrix();


    glTranslated(0,8,5);
//    glRotated(-15,1,0,0);
    glPushMatrix();

    glPushMatrix();
//        glTranslated(0,0,10);
    glScaled(.8,.3,.5);
    drawCube(.4,.4,.4,50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 10);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslated(0,-.01,0);
    glScaled(.8,.01,.5);

    drawCube(.9,.9,.9,50);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();




    quad = gluNewQuadric();


    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuseet);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularrt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessst);
    glTranslatef(.5,.4,-.02);
//        glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluDisk(quad, 0, .2, 32, 32);
    glPopMatrix();
    glPushMatrix();
//        GLfloat no_mattt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttt1[] = { 0,0,0,1.0};
    GLfloat mat_diffuseet1[] = {  1,1,1,1.0 };
    GLfloat mat_specularrt1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessst1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuseet1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularrt1);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessst1);
    glTranslatef(.5,.4,-.02);
//        glRotatef(90,1,0,0);
    glutSolidTorus( .05, .14, 32, 32);
    glPopMatrix();
    glPopMatrix();


}

void projector_screen()
{

    ///porda

    glPushMatrix();
    glPushMatrix();
    glTranslated(0,translate_projector_curtain,-8.5);
    glScaled(4,scale_projector_curtain,.01);
    drawCube(1,1,1);
    glPopMatrix();

    ///pordar nicher lathi

    glPushMatrix();


    color(0,0,0);
    GLUquadricObj *quad;
    quad = gluNewQuadric();
    glTranslated(0,translate_projector_curtain,-8.5);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.1, 0.1, 8, 32, 32);
    glPopMatrix();

    ///curtain namamor handle
    glPushMatrix();


    color(0,0,0);
    glTranslated(4,translate_projector_curtain,-8.5);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.02, 0.02, .5, 32, 32);
    glPopMatrix();
    glPushMatrix();


    color(0,0,0);
    glTranslated(4,translate_projector_curtain-.5,-8.5);
    glutSolidTorus(.02,.06,30,30);
    glPopMatrix();
    glPopMatrix();
    ///pordar uporer lathi
    glPushMatrix();


    color(0,0,0);
    glTranslated(0,10,-8.5);
    glRotatef(90,0,1,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, 0.1, 0.1, 8, 32, 32);
    glPopMatrix();



}

void desk()
{
    glPushMatrix();

//    drawCube(1,1,1);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,14);
    glEnable(GL_TEXTURE_2D);
    // desk er body
    glPushMatrix();
    glTranslated(-13,-2.4,-8);
    glScaled(1,2,1);
    drawCube(1,1,1);
    glPopMatrix();
    // desk er uporer dui pash
    glPushMatrix();
    glTranslated(-12,1.6,-7.9);
    glScaled(2.04,1.2,.2);
    glRotated(90,0,1,0);
    triangularPrism(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-12,1.6,-6.1);
    glScaled(2.04,1.2,.2);
    glRotated(90,0,1,0);
    triangularPrism(1,1,1);
    glPopMatrix();
    // desk er uporer pisoner part
    glPushMatrix();
    glTranslated(-13.05,1.6,-7.9);
    glScaled(.1,.62,.9);
    drawCube(1,1,1);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

void classroom()
{


    ///clock
    glPushMatrix();
    wall_clock(1.0, 1.0, 1.0);
    glPopMatrix();


    ///windows
    glPushMatrix();
    windows();
    glPopMatrix();

    ///draw desk
    glPushMatrix();
    desk();
    glPopMatrix();


    ///wall sets
    glPushMatrix();
    wall_sets();
    glPopMatrix();

    ///light
    glPushMatrix();
    light();
    glPopMatrix();

    ///doors
    glPushMatrix();

    door();
    glPopMatrix();

    ///table chair
    glPushMatrix();
    all_table_chair();
    glPopMatrix();

    ///fan
    glPushMatrix();
    fan();
    glPopMatrix();

    ///box
    glPushMatrix();
    glScaled(1, .7,1);
    glTranslatef(1.5,-2.8,0.5);

    box();
    glPopMatrix();
    /// box door
    glPushMatrix();
    glTranslatef(9.5+k1,-1.7,-6+k2);
    glScaled(1,0.7,1);

    glRotated(l,0,1,0);
    box_door();
    glPopMatrix();

    /// laptop
    glPushMatrix();
    laptop();
    glPopMatrix();

    /// projector
    glPushMatrix();
    projector();
    glPopMatrix();

    /// projector screen
    glPushMatrix();
    projector_screen();
    glPopMatrix();

    /// tul
    glPushMatrix();
    glTranslated(9,-1,12.5);
    glScaled(.3,.4,.4);
    tul();
    glPopMatrix();

    /// glass
    glPushMatrix();
    glTranslated(10.1,-.55,13);
    glScaled(.15,.15,.15);
    glRotated(270,0,1,0);
    glass();
    glPopMatrix();

    /// water_jar
    glPushMatrix();
    water_jar();
    glPopMatrix();







}

void tree()
{
    GLUquadricObj *quad;
    quad = gluNewQuadric();

    //body
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(-30,27,0);
    glRotatef(90,1,0,0);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    gluCylinder(quad, .5, .5, 30, 32, 32);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //leaf
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    gluQuadricOrientation(quad, GLU_OUTSIDE);
    gluQuadricNormals(quad, true);
    gluQuadricTexture(quad, true);
    float tx = -30, ty = 10, tz = 0, sx = .3, sy = .3, sz = .3;
    for(int i=0; i<15; i++)
    {
        glPushMatrix();
        glTranslatef(tx,ty,tz);
        glRotatef(-90,1,0,0);
        glScalef(sx, sy, sz);
        gluCylinder(quad, 16-i, 0, 10, 32, 32);
        glPopMatrix();
        ty += 1.5;// sx -= 0.08;
    }
    glDisable(GL_TEXTURE_2D);
}

void LoadTexture(const char*filename, unsigned int ID)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void display(void)
{
    glViewport(0, -200, windowHeight, windowWidth);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();
    glFrustum(-10, 10, -10, 10, nearPLane, farPlane);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  upX,upY,upZ);

    light0(s);
    light1(p);
    spotlight(spotlght);

    glScalef(scale_x,scale_y,scale_z);
//    glTranslatef(Txval,Tyval,Tzval);
    glRotated(angle_x,1,0,0);
    glRotated(angle_y,0,1,0);
    glRotated(angle_z,0,0,1);

    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );




//    visualizing lighting effect


    glPushMatrix();
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glEnable(GL_TEXTURE_2D);
    glTranslatef(10, 200, 0);
    glutSolidSphere(3,100,100);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
//





//----------------------------------------------

    ///Sky
    glPushMatrix();
    sky();
    glPopMatrix();

    ///grass
    glPushMatrix();
    grass();
    glPopMatrix();
    ///grass
    glPushMatrix();
    tree();
    glTranslated(-5,0,0);
    tree();
    glTranslated(-10,0,0);
    tree();
    glTranslated(-10,0,-10);
    tree();
    glTranslated(-5,0,10);
    tree();
    glTranslated(80,0,10);
    tree();
    glTranslated(0,0,-10);
    tree();
    glTranslated(10,0,0);
    tree();
    glPopMatrix();

    glPushMatrix();
    classroom();

    glPopMatrix();

    glPushMatrix();

    glPopMatrix();



//    glPushMatrix();
//    glTranslatef(-9.8,3,25.55);
//    glRotatef(-90,0,1,0);
//    door1();
//    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void setCameraEye_Yaw() // y axis , y u
{

    refY = 100.0*(cos(angleYaw*3.1416/180.0));

}

void setCameraEye_Roll() // z axis ,i o
{

    upX = 100.0*(cos(angleRoll*3.1416/180.0));
    upY = 100.0*(sin(angleRoll*3.1416/180.0));

}

void setCameraEye_Pitch() // x axis , r t
{


    refX = 100.0*(cos(anglePitch*3.1416/180.0));
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'd':
        if(d<=6) d+=1;
        //cout<<d<<endl;
        break;
    case 'D':
        if(d>=1) d-=1;
        //cout<<d<<endl;
        break;
    case '5':
        if(l>=90)
            break;
        l+=15;
//        cout<<l<<endl;
        if(l==90)
        {
            k1=1;
            k2=1;
            break;
        }
        if(l==75)
        {
            k1=0.77;
            k2=0.979999;
            break;
        }
        if(l==60)
        {
            k1=.50;
            k2=.90;
            break;
        }
        if(l==45)
        {
            k1=.3;
            k2=.7;

            break;
        }
        if(l==30)
        {
            k1=.13;
            k2=.52;

            break;
        }
        if(l==15)
        {
            k1=.02;
            k2=0.23;

            break;
        }

        k+=.01;
//cout<<k<<endl;

        break;
    case '6':
        if(l<=0)
            break;
        l-=15;
//        cout<<l<<endl;
        if(l==90)
        {
            k1=1;
            k2=1;
            break;
        }
        if(l==75)
        {
            k1=0.77;
            k2=0.979999;
            break;
        }
        if(l==60)
        {
            k1=.50;
            k2=.90;
            break;
        }
        if(l==45)
        {
            k1=.3;
            k2=.7;

            break;
        }
        if(l==30)
        {
            k1=.13;
            k2=.52;

            break;
        }
        if(l==15)
        {
            k1=.02;
            k2=0.23;

            break;
        }
        if(l==0)
        {
            k1=0;
            k2=0;

            break;
        }



        break;
    case 'B':
        if(Bxval>=11.8)
            break;
        Bxval+=0.2;

        break;
    case 'b':
        if(Bxval<=1.2)
            break;
        //cout<<"Bxval "<<Bxval<<endl;
        Bxval-=.2;
        break;
    case 'c':
        if(Cxval>=-1.2)
            break;
        //cout<<"Cxval "<<Cxval<<endl;
        Cxval+=0.2;

        break;
    case 'C':
        if(Cxval<=-11.4)
            break;

        Cxval-=.2;
        break;

    case 'x':
//        bRotate=!bRotate;
//        uRotate=0;
        axis_x=0.0;
        axis_y=1.0;
        alpha += 1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
        break;
    case 'X':
//        bRotate=!bRotate;
//        uRotate=0;
        axis_x=0.0;
        axis_y=1.0;
        alpha -= 1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
        break;
    case 'y':
//        uRotate=!uRotate;
//        bRotate=0;
        axis_x=1.0;
        axis_y=0.0;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
        alpha += 1;
        break;
    case 'Y':
//        uRotate=!uRotate;
//        bRotate=0;
        axis_x=1.0;
        axis_y=0.0;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
        alpha -= 1;
        break;



    ///zooming
    case '+'://zoom using nearplane in GLfruscome
        nearPLane+=0.1;
//        cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<endl;
//        cout<<refX<<" "<<refY<<" "<<refZ<<endl;
        break;
    case '-':
        nearPLane-=.1;
        break;


    case 'z': // zoom using scaling
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();

        break;
    case 'Z':
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;

    case 'N':
        dx = eyeX-refX;
        dy = eyeY-refY;
        dz = eyeZ-refZ;
        dxyz = sqrt(dx*dx+dy*dy+dz*dz);
        eyeX+=(dx/dxyz);
        eyeY+=(dy/dxyz);
        eyeZ+=(dz/dxyz);
        refX+=(dx/dxyz);
        refY+=(dy/dxyz);
        refZ+=(dz/dxyz);
        //cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<refX<<" "<<refY<<" "<<refZ<<endl;
        break;

    case 'n':
        dx = eyeX-refX;
        dy = eyeY-refY;
        dz = eyeZ-refZ;
        dxyz = sqrt(dx*dx+dy*dy+dz*dz);
        eyeX-=(dx/dxyz);
        eyeY-=(dy/dxyz);
        eyeZ-=(dz/dxyz);
        refX-=(dx/dxyz);
        refY-=(dy/dxyz);
        refZ-=(dz/dxyz);
        break;

    /// window open close
    case 'W':

        if(Lzval>=-.1)
            break;
        Lzval+=0.2;
        //cout<<Tzval<<endl;

        break;

    case 'w':
        if(Lzval<=-2.4)
            break;
        Lzval-=0.2;
        break;
    case 'Q':

        if(Rzval>=-.1)
            break;
        Rzval+=0.2;
        //cout<<Tzval<<endl;

        break;

    case 'q':
        if(Rzval<=-2.4)
            break;
        Rzval-=0.2;
        break;

    case 'I':
        if(anglePitch>=anglePitchLimit1)
            break;
        anglePitch += roll_value;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'i':
        if(anglePitch==anglePitchLimit2)
            break;
        anglePitch -= roll_value;

        setCameraEye_Pitch();
        glutPostRedisplay();
        break;



    case 'O':
        if(angleYaw==angleYawLimit1)
            break;
        angleYaw += roll_value;

        setCameraEye_Yaw();
        glutPostRedisplay();

        // eyex = eyex;
        break;
    case 'o':
        if(angleYaw==angleYawLimit2)
            break;
        angleYaw -= roll_value;
        //if(angleYaw < 0)
        //   angleYaw += limit;
        setCameraEye_Yaw();
        //setCameraEye_Yaw();
        glutPostRedisplay();
        break;




    case 'P':

        angleRoll += roll_value;
        setCameraEye_Roll();
        glutPostRedisplay();


        break;
    case 'p':

        angleRoll -= roll_value;
        setCameraEye_Roll();
        glutPostRedisplay();
        break;

    ///*****************fan control*************
    case '1'://fan on
        if(fon1==0)
        {
            fon1=1;
            break;
        }
        else
        {
            fon1=0;
            break;
        }
    case '2'://fan on
        if(fon2==0)
        {
            fon2=1;
            break;
        }
        else
        {
            fon2=0;
            break;
        }
    case '3'://fan on
        if(fon3==0)
        {
            fon3=1;
            break;
        }
        else
        {
            fon3=0;
            break;
        }
    case '4'://fan on
        if(fon4==0)
        {
            fon4=1;
            break;
        }
        else
        {
            fon4=0;
            break;
        }
    case 'R':
        if(fon1==1)
        {
            if(xx>=30)
            {
                xx=30;
                break;
            }
            xx+=2;
            //cout<<xx<<endl;
            glutPostRedisplay();

            break;
        }

    case 'r':
        if(fon1==1)
        {
            if(xx<=0.1)
            {
                xx=0.1;
                break;
            }
            xx-=2;
            //cout<<xx<<endl;
            glutPostRedisplay();

            break;
        }

    ///*******************light control**************
    case 'l'://LIGHT ON/OFF
        if(s==0)
        {
            s=1;
            break;
        }
        else
        {
            s=0;
            break;
        }
    case 'k'://LIGHT ON/OFF
        if(p==0)
        {
            p=1;
            break;
        }
        else
        {
            p=0;
            break;
        }

    case 'V':
        spotlght=1; //spotlight on
        break;
    case 'v'://spotlight off
        spotlght=0;
        break;
    case 27:	// Escape key
        exit(1);

    case ' ':    // space key

        Txval=0,Tyval=0,Tzval=0, Bxval=0,Cxval=0,Lzval=0, Rzval=0;
        windowHeight=1400, windowWidth=1400;
        //double eyeX=0, eyeY=2, eyeZ=261, refX = 0, refY=2,refZ=240, upX = 0, upY = 1,upZ = 0;
        eyeX=0, eyeY=4, eyeZ=22, refX = 0, refY=4,refZ=8, upX = 0, upY = 1,upZ = 0;
        alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, angle_y=0.0,angle_x=0.0,angle_z=0.0;
        bRotate = false, uRotate = false;
        nearPLane = 3, farPlane = 300;

        limit = 360;
        roll_value = 1;
        xx=1;


        angleYaw = 90.0, anglePitch = 270.0, angleRoll = 90.0;
        angleYawLimit1 = 180.0, anglePitchLimit1 = 360.0;
        angleYawLimit2 = 0.0, anglePitchLimit2 = 180.0;
        dangle = 0.0;

        scale_x = 1;
        scale_y = 1;
        scale_z = .8;

        int s=1;
        break;


    }


    glutPostRedisplay();

}

void pressKey(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_PAGE_DOWN:
        pd=1;
        break;
    case GLUT_KEY_PAGE_UP:
        pd=0;
        break;

    case GLUT_KEY_F1: // move eye point upwards along Y axis
        eyeX=-1,eyeY=3,eyeZ=-9;
        refX=0,refY=3,refZ=-5;
        break;
    case GLUT_KEY_UP: // move eye point upwards along Y axis
        eyeY+=1.0;
        refY+=1.0;
        break;
    case GLUT_KEY_DOWN: // move eye point downwards along Y axis
        eyeY-=1.0;
        refY-=1.0;
        break;
    case GLUT_KEY_LEFT: // move eye point left along X axis
        eyeX-=1.0;
        refX-=1.0;
//        cout<<eyeX<<endl;

        break;
    case GLUT_KEY_RIGHT: // move eye point right along X axis
        eyeX+=1.0;
        refX+=1.0;
        break;


        glutPostRedisplay();
    }


}

void animate()
{
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    int hr=(aTime->tm_hour)%12;
    int mnt=aTime->tm_min;
    int sec =aTime->tm_sec;


    second= -(sec*6)+180;
    minute = -(mnt*6)+180;
    hour = -(hr*30)-.5*mnt+180;
//    cout<<hr<<" "<<mnt<<" "<<sec<<endl;
//    cout<<hour<<" "<<minute<<" "<<second<<endl;

    if(pd==1)
    {
        if(translate_projector_curtain<=0)
        {
            translate_projector_curtain=0;
            scale_projector_curtain=5;
        }
        else
        {
            translate_projector_curtain-=.25;
            scale_projector_curtain+=.125;
        }
        cout<<translate_projector_curtain<<endl;

    }
    if(pd==0)
    {
        if(translate_projector_curtain>=10)
        {
            translate_projector_curtain=10;
            scale_projector_curtain=0;
        }
        else
        {
            translate_projector_curtain+=.25;
            scale_projector_curtain-=.125;
        }
    }

    if(fon1==1)
    {
        kdeg1+=xx;
//        cout<<x<<endl;
//        if(kdeg1>=360)
//            kdeg1=0.0;
        glutPostRedisplay();

    }
    else if(fon1==0)
    {
        kdeg1=0;
        glutPostRedisplay();
    }
    if(fon2==1)
    {
        kdeg2+=20;
//        cout<<x<<endl;
        if(kdeg2>=360)
            kdeg2=0.0;
        glutPostRedisplay();

    }
    else if(fon2==0)
    {
        kdeg2=0;
        glutPostRedisplay();
    }
    if(fon3==1)
    {
        kdeg3+=20;
//        cout<<x<<endl;
        if(kdeg3>=360)
            kdeg3=0.0;
        glutPostRedisplay();

    }
    else if(fon3==0)
    {
        kdeg3=0;
        glutPostRedisplay();
    }
    if(fon4==1)
    {
        kdeg4+=20;
//        cout<<x<<endl;
        if(kdeg4>=360)
            kdeg4=0.0;
        glutPostRedisplay();

    }
    else if(fon4==0)
    {
        kdeg4=0;
        glutPostRedisplay();
    }
    glutPostRedisplay();
    if (bRotate == 1)
    {
        theta += 0.05;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == 1)
    {
        alpha += 0.05;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("1707100_Classroom_project");

//    /// texture adding
//////
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\sky1.bmp",1);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\sky_right.bmp",2);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\sky_top.bmp",3);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\leaves.bmp",4);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\treebody2.bmp",5);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\clock.bmp",6);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\window.bmp",7);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\mug.bmp",8);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\keyboard.bmp",9);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\projector.bmp",10);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\floorr.bmp",11);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\left_wall_part3.bmp",12);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\table.bmp",13);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\door.bmp",14);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\door1.bmp",15);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\grass2.bmp",16);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\table.bmp",17);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\bottol.bmp",18);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\bottol2.bmp",19);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\wall1.bmp",20);
    LoadTexture("F:\\42\\CSE 4208 (Computer Graphics lab)\\Project\\Classroom\\wall2.bmp",21);


//****************************************///keyboard function***************************************************
    cout<<"1. Zoom in/Zoom out using near-far plane --> +/-\n";
    cout<<"2. Zoom in/Zoom out using eye and ref plane --> n/N\n";
    cout<<"3. Zoom in/Zoom out using scalling plane --> z/Z\n";
    cout<<"4. left window open/close --> w/W\n";
    cout<<"5. Right window open/close --> q/Q\n";
    cout<<"6. white board movement --> c/C & b/B\n";
    cout<<"7. box door open/close --> 5/6\n";
    cout<<"8. fan --> 1,2,3,4\n";
    cout<<"9. fan regulator--> r/R\n";
    cout<<"10. X/Y rotation--> X/Y\n";
    cout<<"11. up/down/left/right--> keyboard button \n";
    cout<<"12. door open/close--> d/D \n";
    cout<<"13. projector sheet dn/up--> pg dn/pg up \n";
    cout<<"14. light 1, 2--> k/l \n";
    cout<<"15. projector on/off --> V/v \n";









//*********************************************************************************************



    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(pressKey);
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutMainLoop();


    return 0;
}




