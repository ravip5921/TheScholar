#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/vars.h"
#include "Headers/GUICompClassA.h"
Color c2(0,0,1);

Coord_Rect p(0,1,3,0);
//TextBox t1(0,1,0,3,false,0,0,1);
TextBox t1(p,false,c2);

void mousePressed(int button, int state,int x, int y);
void keyPressed(unsigned char key,int x,int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);
int main(int argc, char **argv) //default arguments of main
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowPosition(INI_X, INI_Y);
  glutInitWindowSize(WID, HEI);
  glutCreateWindow("Scalling Trial");

  glutDisplayFunc(callBackFun);
  glutReshapeFunc(ReshapeCallBack);
  glutMouseFunc(mousePressed);
  glutKeyboardFunc(keyPressed);
  initColor();
  glutMainLoop();
}
void callBackFun()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();


  //printText(-2.1,3,"C++ Genie",GLUT_BITMAP_TIMES_ROMAN_24,1,1,0);
glColor3f(0, 1,0);
//printText(0,0,"Ravi Pandey",GLUT_BITMAP_HELVETICA_18,1,1,1);
 /* glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(0, 0);
  glVertex2f(0, .5);
  glEnd()*/

  t1.render();

  glutPostRedisplay();
  glutSwapBuffers();
}
void ReshapeCallBack(int wid, int heig)
{
    glViewport(0,0,wid,heig); //full screen has been taken as view port //all drawings are displayed in the view port
    glMatrixMode(GL_PROJECTION); //Switches to projection mode to draw stuff on the window //from GL model view matrix(default)
    glLoadIdentity(); //resets the parameters of projection matrix
    gluOrtho2D(-COORD_X,COORD_X,-COORD_Y,COORD_Y); //takes 4 arguments left,right,bottom,top (2D graph)
    glMatrixMode(GL_MODELVIEW); //switches back to model-view mode,the default mode
    //always should be in model view matrix , only go to projection matrix to set coordinates


}
void initColor()
{
  glClearColor(WC_R, WC_G, WC_B, WC_A);
}

void mousePressed(int button, int state,int x, int y)
{
    t1.mouseHandler(button,state,x,y);
    if(state==GLUT_DOWN)
    {
        std::cout<<"x= "<<x<<" y= "<<y<<'\n';
    }
}
void keyPressed(unsigned char key,int x,int y)
{
    t1.keyboardHandler(key,x,y);
}

