#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/vars.h"
#include "Headers/GUICompClassA.h"
#include "map"

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);


GUIPage loginPage;
GUIPage signupPage;
GUIPage activePage;
int PAGE=1;
enum
{
    WELCOME_P = 0,
    LOGIN_P = 1,
    SIGNUP_P = 2
};
std::map <int,GUIPage* > pageMap=
{
    {1,&loginPage},
    {2,&signupPage}
};


//pageMap.insert(std::pair<int,GUIcomponent *>(LOGIN_P,&loginPage));

/**** Login Page *****/

namespace LogIn{
    Color userNameC(0.878,0.749,0.9055);
    Color passwordC = userNameC;
    Color boxTextC(0.43,0.67,0.1);
    Color logInTextC(1, 1, 0);
    Color logInButtonTextC(1, 0, 1);
    Color logInButtonC(0.7, 0, 0.43);
    Color pageTextC(1, 0, 0);

    Coord_Rect logInButtonD(-1, -6, 3, 1.2);
    Coord_Rect userNameD(-3, 1, 8, 2.2);
    Coord_Rect passwordD(-3, -3, 8, 2.2);

    Text logInScreen(-2, 5, pageTextC, "LOGIN SCREEN", GLUT_BITMAP_TIMES_ROMAN_24);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 5.5, -3, logInButtonC);
    Button logInButton("Log In", logInButtonC, logInButtonTextC, logInButtonD);

    void addlogInComponents(GUIPage *logInPage)
    {
        logInPage->addComponent(&logInScreen);
        logInPage->addComponent(&userNameB);
        logInPage->addComponent(&passwordB);
        logInPage->addComponent(&showPassword);
        logInPage->addComponent(&logInButton);
    }
}

/**** SignUp Page *****/

namespace SignUp{
    Color userNameC(0.878,0.749,0.9055);
    Color passwordC = userNameC;
    Color boxTextC(0.43,0.67,0.1);
    Color signUpTextC(1, 1, 0);
    Color signUpButtonTextC(1, 0, 1);
    Color signUpButtonC(0.7, 0, 0.43);
    Color pageTextC(1, 0, 0);

    Coord_Rect signUpButtonD(-1, -6, 3, 1.2);
    Coord_Rect userNameD(-3, 1, 8, 2.2);
    Coord_Rect passwordD(-3, -3, 8, 2.2);

    Text signUpScreen(-2, 5, pageTextC, "SIGNUP SCREEN", GLUT_BITMAP_TIMES_ROMAN_24);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 5.5, -3, signUpButtonC);
    Button signUpButton("Sign Up", signUpButtonC, signUpButtonTextC, signUpButtonD);

    void addsignUpComponents(GUIPage *signUpPage)
    {
        signUpPage->addComponent(&signUpScreen);
        signUpPage->addComponent(&userNameB);
        signUpPage->addComponent(&passwordB);
        signUpPage->addComponent(&showPassword);
        signUpPage->addComponent(&signUpButton);
    }
}

int main(int argc, char **argv) //default arguments of main
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(INI_X, INI_Y);
    glutInitWindowSize(WID, HEI);
    glutCreateWindow("Scalling Trial");

/*** Login Page ****/
    LogIn::addlogInComponents(&loginPage);
/**** SignUp Page ***/
    SignUp::addsignUpComponents(&signupPage);

    glutDisplayFunc(callBackFun);
    glutReshapeFunc(ReshapeCallBack);
    glutMouseFunc(mousePressed);
    glutKeyboardFunc(keyPressed);
    initColor();
    glutMainLoop();
}
void callBackFun()
{
    activePage= (*pageMap[PAGE]);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0, 1, 0);
    if(PAGE==WELCOME_P)
        glDrawP(0,0,1,1);
    /*else if(PAGE==LOGIN_P)
        loginPage.render(); //Login Page render
    else if(PAGE==SIGNUP_P)
        signupPage.render();        //Sign Up page render
        */
    else
    activePage.render();
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
  //  loginPage.mouseHandler(button,state,x,y);      //login page
    //signupPage.mouseHandler(button,state,x,y);      //sign up page


    activePage.mouseHandler(button,state,x,y);

    if(PAGE==SIGNUP_P && activePage.buttonPressed(SignUp::signUpButton))
    {
        PAGE=LOGIN_P;
        std::cout<<"signed In\n";
    }
    else if(PAGE==LOGIN_P && activePage.buttonPressed(LogIn::logInButton))
    {
        PAGE=SIGNUP_P;
        std::cout<<"HEY\n";
    }
    if (state == GLUT_DOWN)
    {
        std::cout << "x= " << x << " y= " << y << '\n';
    }
}
void keyPressed(unsigned char key, int x, int y)
{
//    loginPage.keyboardHandler(key,x,y);  //login page
    //signupPage.keyboardHandler(key,x,y);    //sign up page
activePage.keyboardHandler(key,x,y);
}
