#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/GlutEventHandlers.h"

int main(int argc, char **argv) //default arguments of main
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(INI_X, INI_Y);
    glutInitWindowSize(WID_INI, HEI_INI);
    mainWindowIndex = glutCreateWindow("The Scholar");
    /**** Welcome Page ****/
    welcome::addWelcomComponents(&welcomePage);
    /*** Login Page ****/
    LogIn::addlogInComponents(&loginPage);
    /**** SignUp Page ***/
    SignUp::addsignUpComponents(&signupPage);
    /***** Home Page *****/
    Home::addHomeComponents(&homePage);
    /******* Book Detail Page *******/
    BookDetail::addBookDetailComponents(&bookDetailPage);

    glutDisplayFunc(callBackFun);
    glutReshapeFunc(ReshapeCallBack);
    glutMouseFunc(mousePressed);
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(mouseMotion);
    initColor();

    glutCreateSubWindow(mainWindowIndex, 1, 1, 200, 100);
    glutDisplayFunc(showClock);
    glutReshapeFunc(ReshapeCallBack);

    glutMainLoop();
}
