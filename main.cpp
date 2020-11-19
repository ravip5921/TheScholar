#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/vars.h"
#include "Headers/GUICompClass.h"
#include "Headers/FileReader.h"
#include "Headers/GUIPages.h"
#include "Headers/ErrorWindow.h"
#include "Headers/GUIBlocks.h"

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);
void createErrorWindow(const char*);
void setFonts();
void showClock();
int windowWidth();
int windowHeight();

//For pages
GUIPage loginPage;
GUIPage signupPage;
GUIPage welcomePage;
GUIPage homePage;

/*** Navigate Pages ****/
int PAGE = 0;
enum
{
    WELCOME_P = 0,
    LOGIN_P = 1,
    SIGNUP_P = 2,
    HOME_P = 3
};

std::vector<GUIPage *> activePage = {&welcomePage, &loginPage, &signupPage , &homePage};
//end of page navigator

//for miniPages in Home PageGUIBlock readingBlock;
    GUIBlock readingBlock;
    GUIBlock completedBlock;
    GUIBlock favouriteBlock;
    GUIBlock sharedBlock;

/**** Navigate miniPages in HOME_PAGE *****/
    int MINI_P=0;
    enum{
        READING_MP = 0,
        COMPLETED_MP =1,
        FAVOURITE_MP =2,
        SHARED_MP = 3
    };
    std::vector<GUIBlock *>activeBlock = {&readingBlock, &completedBlock , &favouriteBlock , &sharedBlock};
//end miniPages

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
    /************** MINI Pages *****************/
    readingN::addReadingComponents(&readingBlock);
    completedN::addCompletedComponents(&completedBlock);
    favouriteN::addFavouriteComponents(&favouriteBlock);
    sharedN::addSharedComponents(&sharedBlock);
    //mini pages end

    glutDisplayFunc(callBackFun);
    glutReshapeFunc(ReshapeCallBack);
    glutMouseFunc(mousePressed);
    glutKeyboardFunc(keyPressed);
    initColor();

    glutCreateSubWindow(mainWindowIndex, 1, 1, 200, 100);
    glutDisplayFunc(showClock);
    glutReshapeFunc(ReshapeCallBack);

    glutMainLoop();
}
void callBackFun()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0, 1, 0);
    WID = windowWidth();
    HEI = windowHeight();
    setFonts();

    activePage[PAGE]->render();
    if(PAGE == HOME_P){
        activeBlock[MINI_P]->render();
    }

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

void setFonts()
{
    LogIn::userNameB.setFont(GLUT_BITMAP_HELVETICA_18);
    SignUp::userNameB.setFont(GLUT_BITMAP_HELVETICA_18);
}

void mousePressed(int button, int state, int x, int y)
{
    activePage[PAGE]->mouseHandler(button, state, x, y);
    if (PAGE == WELCOME_P)
    {
        if (activePage[PAGE]->buttonPressed(&welcome::signupButton))
        {
            PAGE = SIGNUP_P;
            activePage[LOGIN_P]->setActiveBox(&SignUp::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&welcome::loginButton))
        {
            PAGE = LOGIN_P;
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
        }
    }
    else if (PAGE == LOGIN_P)
    {
        if (activePage[PAGE]->buttonPressed(&LogIn::logInButton))
        {
            userName = activePage[PAGE]->getText(&LogIn::userNameB);
            password = activePage[PAGE]->getText(&LogIn::passwordB);
            std::cout << "\nUser = " << userName << "\nPass = " << password << "\n";
            logIn LogInObject(userName, password);

            if(LogInObject.IsLogedIn() || userName=="a")
            {
                PAGE = HOME_P;
                activePage[HOME_P]->setText(&Home::User,&userName);
            }
            else
            {
                createErrorWindow("User name or password incorrect!");
            }
        }
        else if (activePage[PAGE]->buttonPressed(&LogIn::toSignup))
        {
            PAGE = SIGNUP_P;
            activePage[LOGIN_P]->setActiveBox(&SignUp::userNameB);
        }
    }
    else if (PAGE == SIGNUP_P)
    {
        if (activePage[PAGE]->buttonPressed(&SignUp::signUpButton))
        {
            userNameN = activePage[PAGE]->getText(&SignUp::userNameB);
            passwordN = activePage[PAGE]->getText(&SignUp::passwordB);
            std::cout << "\nUser = " << userNameN << "\nPass = " << passwordN << "\n";
            signUp SignUpObject(userNameN, passwordN);
            if(!SignUpObject.userExists())
            {
                SignUpObject.signup();
                activePage[HOME_P]->setText(&Home::User,&userNameN);
                PAGE = HOME_P;
            }
            else
            {
                createErrorWindow("User already exists. Try Logging In.");
            }
        }
        else if (activePage[PAGE]->buttonPressed(&SignUp::toLogin))
        {
            PAGE = LOGIN_P;
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
        }
    }
    else if (PAGE == HOME_P)
    {
        if (activePage[PAGE]->buttonPressed(&Home::logoutButton))
        {
            PAGE = LOGIN_P;
            userName="";
            password="";
            activePage[LOGIN_P]->setText(&LogIn::userNameB,&userName);
            activePage[LOGIN_P]->setText(&LogIn::passwordB,&userName);
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
            activePage[LOGIN_P]->setActiveBox(&LogIn::passwordB,false);
        }
        else if (activePage[PAGE]->buttonPressed(&Home::readingButton)){
            MINI_P = READING_MP;
        }
        else if (activePage[PAGE]->buttonPressed(&Home::completedButton)){
            MINI_P = COMPLETED_MP;
        }
        else if (activePage[PAGE]->buttonPressed(&Home::favouriteButton)){
            MINI_P = FAVOURITE_MP;
        }
        else if (activePage[PAGE]->buttonPressed(&Home::sharedButton)){
            MINI_P = SHARED_MP;
        }
    }
    if (state == GLUT_DOWN)
    {
        std::cout << "x= " << x << " y= " << y << '\n';
    }
}
void keyPressed(unsigned char key, int x, int y)
{
    activePage[PAGE]->keyboardHandler(key, x, y);
    if (PAGE == LOGIN_P)
    {
        if (activePage[PAGE]->isActiveBox(&LogIn::userNameB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            activePage[PAGE]->setActiveBox(&LogIn::userNameB, false);
            activePage[PAGE]->setActiveBox(&LogIn::passwordB);
        }
        else if (activePage[PAGE]->isActiveBox(&LogIn::passwordB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            if (key == TAB_KEY)
            {
                activePage[PAGE]->setActiveBox(&LogIn::passwordB, false);
                activePage[PAGE]->setActiveBox(&LogIn::userNameB);
            }
            else if (key == ENTER_KEY)
            {
                userName = activePage[PAGE]->getText(&LogIn::userNameB);
                password = activePage[PAGE]->getText(&LogIn::passwordB);
                std::cout << "\nUser = " << userName << "\nPass = " << password << "\n";
                logIn LogInObject(userName, password);

                if(LogInObject.IsLogedIn() || userName=="a")
                {
                    PAGE = HOME_P;
                    activePage[HOME_P]->setText(&Home::User,&userName);
                }
                else
                {
                    createErrorWindow("User name or password incorrect!");
                }
            }
        }
    }
    if (PAGE == SIGNUP_P)
    {
        if (activePage[PAGE]->isActiveBox(&SignUp::userNameB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            activePage[PAGE]->setActiveBox(&SignUp::userNameB, false);
            activePage[PAGE]->setActiveBox(&SignUp::passwordB);
        }
        else if (activePage[PAGE]->isActiveBox(&SignUp::passwordB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            if (key == TAB_KEY)
            {
                activePage[PAGE]->setActiveBox(&SignUp::passwordB, false);
                activePage[PAGE]->setActiveBox(&SignUp::userNameB);
            }
            else if (key == ENTER_KEY)
            {
                userNameN = activePage[PAGE]->getText(&SignUp::userNameB);
                passwordN = activePage[PAGE]->getText(&SignUp::passwordB);
                std::cout << "\nUser = " << userNameN << "\nPass = " << passwordN << "\n";
                signUp SignUpObject(userNameN, passwordN);
                if(!SignUpObject.userExists())
                {
                    SignUpObject.signup();
                    activePage[HOME_P]->setText(&Home::User,&userNameN);
                    PAGE = HOME_P;
                }
                else
                {
                    createErrorWindow("User already exists. Try Logging In.");
                }
            }
        }
    }
}
void createErrorWindow(const char* err)
{
     if(ErrorWindow::canMake)
            ErrorWindow::create(err,glutGet(GLUT_WINDOW_X)+150,glutGet(GLUT_WINDOW_Y)+200);
}
int windowWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}
int windowHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}
void showClock()
{
    glClear(GL_COLOR_BUFFER_BIT); //Clears the frame buffer of window,good habit

    glLoadIdentity(); //resets the matrix transformation done is previous options(i.e.,make default coordinate points)
    glClearColor(WC_R, WC_G, WC_B, WC_A);
    Showtime s1(-9, 1.5, 1, 1, 1);
    s1.displayClock(GLUT_BITMAP_TIMES_ROMAN_24);
    s1.displayCalendar(-5, -2.5, GLUT_BITMAP_HELVETICA_18);
    glutPostRedisplay();
    glutSwapBuffers();
}
