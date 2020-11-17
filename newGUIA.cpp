#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/vars.h"
#include "Headers/GUICompClassA.h"
Color BoxCol(0, 1, 0);
Color passCol(1, 1, 1);
Color TextCol(0, 0, 0);
Coord_Rect norm(-3, 0, 6.5, 2);
Coord_Rect pass(-3, -4, 6.5, 1.5);
Coord_Rect butD(5,-5,3,1);
Color LogIn(1,0.17,0.3);
TextBox normBox(norm, BoxCol, TextCol, false);
PasswordBox passB(pass, passCol, TextCol, false);
CheckBox r(&passB,4, -4, BoxCol, false);
Text Login(-2,3,LogIn,"LOGIN SCREEN",GLUT_BITMAP_TIMES_ROMAN_24);
Button loginButton(" Log In",BoxCol,LogIn,butD);
GUIPage lp;

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
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
    lp.addComponent(&normBox);
    lp.addComponent(&passB);
    lp.addComponent(&r);
    lp.addComponent(&Login);
    lp.addComponent(&loginButton);
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
    glColor3f(0, 1, 0);
    //printText(0,0,"Ravi Pandey",GLUT_BITMAP_HELVETICA_18,1,1,1);
    /* glBegin(GL_LINES);
  glColor3f(1,1,1);
  glVertex2f(0, 0);
  glVertex2f(0, .5);
  glEnd()*/
   /* normBox.render();

    //if (passB.isActive())
    //normBox.showText(true);
    passB.render();
    r.setActive(passB.isShowing());
    r.render();*/
    lp.render();
    glutPostRedisplay();
    glutSwapBuffers();
}
void ReshapeCallBack(int wid, int heig)
{
    glViewport(0, 0, wid, heig);                      //full screen has been taken as view port //all drawings are displayed in the view port
    glMatrixMode(GL_PROJECTION);                      //Switches to projection mode to draw stuff on the window //from GL model view matrix(default)
    glLoadIdentity();                                 //resets the parameters of projection matrix
    gluOrtho2D(-COORD_X, COORD_X, -COORD_Y, COORD_Y); //takes 4 arguments left,right,bottom,top (2D graph)
    glMatrixMode(GL_MODELVIEW);                       //switches back to model-view mode,the default mode
                                                      //always should be in model view matrix , only go to projection matrix to set coordinates
}
void initColor()
{
    glClearColor(WC_R, WC_G, WC_B, WC_A);
}

void mousePressed(int button, int state, int x, int y)
{
  /*  normBox.mouseHandler(button, state, x, y);
    passB.mouseHandler(button, state, x, y);
    r.mouseHandler(button, state, x, y);*/
    lp.mouseHandler(button,state,x,y);
    if (state == GLUT_DOWN)
    {
        std::cout << "x= " << x << " y= " << y << '\n';
    }
}
void keyPressed(unsigned char key, int x, int y)
{
  /*  normBox.keyboardHandler(key, x, y);
    passB.keyboardHandler(key, x, y);
    r.keyboardHandler(key, x, y);*/
    lp.keyboardHandler(key,x,y);
    if (key == ENTER_KEY)
    {
        userName = normBox.getText();
        passWord = passB.getText();
        std::cout << "USER=" << userName << std::endl;
        std::cout << "PASS=" << passB.getText() << '\n';
    }

  /*  else if (key == '/')
    {
        passB.showPass(true);
    }
    else if (key == '.')

        passB.showPass(false);*/
}
