#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/vars.h"
#include "Headers/GUICompClass.h"
#include "Headers/FileReader.h"
#include "Headers/ErrorWindow.h"

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);
void setFonts();
void showClock();
void createErrorWindow(const char* err);
int windowWidth();
int windowHeight();

GUIPage loginPage;
GUIPage signupPage;
GUIPage welcomePage;

/*** Navigate Pages ****/
int PAGE = 0;
enum
{
    WELCOME_P = 0,
    LOGIN_P = 1,
    SIGNUP_P = 2
};

std::vector<GUIPage *> activePage = {&welcomePage, &loginPage, &signupPage};
//end of page navigator

/**** Welcome Page *****/
namespace welcome
{
    float devInfoX = -9.1;
    float devInfoY = -4.5;
    Color titleC(0.7, 0.67, 0.6);
    Color devInfo(0.9, 0.9, 0.91);
    Color loginButtonC(0.1, 0.3, 0.7);
    Color loginButtonTextC(1, 1, 1);

    Coord_Rect loginButtonD(2, -8, 3, 1.5);
    Coord_Rect signupButtonD(loginButtonD, 'x', 3.4);

    Text titleT(-2.5, 2.5, titleC, "THE SCHOLAR", GLUT_BITMAP_TIMES_ROMAN_24);
    Text subTitleT(-2.2, 1.8, titleC, "E-lib of some sort", GLUT_BITMAP_HELVETICA_18);
    Text devInfoA(devInfoX, devInfoY, devInfo, "DEVELOPED BY:", GLUT_BITMAP_TIMES_ROMAN_24);
    Text devInfoB(devInfoX, devInfoY - 1, devInfo, "Ravi Pandey", GLUT_BITMAP_HELVETICA_18);
    Text devInfoC(devInfoX, devInfoY - 2, devInfo, "Rohan Chhetry", GLUT_BITMAP_HELVETICA_18);
    Text devInfoD(devInfoX, devInfoY - 3, devInfo, "Nikesh D.C.", GLUT_BITMAP_HELVETICA_18);
    Button loginButton("Log In", loginButtonC, loginButtonTextC, loginButtonD);
    Button signupButton("Sign Up", loginButtonC, loginButtonTextC, signupButtonD);

    void addWelcomComponents(GUIPage *_welcomePage)
    {
        _welcomePage->addComponent(&titleT);
        _welcomePage->addComponent(&subTitleT);
        _welcomePage->addComponent(&devInfoA);
        _welcomePage->addComponent(&devInfoB);
        _welcomePage->addComponent(&devInfoC);
        _welcomePage->addComponent(&devInfoD);
        _welcomePage->addComponent(&loginButton);
        _welcomePage->addComponent(&signupButton);
    }
} // namespace welcome
/**** Login Page *****/

namespace LogIn
{
    Color userNameC(0.978, 0.849, 0.9055);
    Color passwordC = userNameC;
    Color boxTextC(0.23, 0.17, 0.91);
    Color logInTextC(1, 1, 0);
    Color logInButtonTextC(1, 0, 1);
    Color logInButtonC(0.1, 0.9, 0.43);
    Color toSignupC(0.3, 0.9, 0.6);
    Color pageTextC(1, 0, 0);
    Color rectBoxC(1, 1, 1);
    Color TitleC(0.5, 0, 0.5);

    Coord_Rect logInButtonD(-2, -6, 3, 1.2);
    Coord_Rect userNameD(-5, 0, 9, 1.9);
    Coord_Rect passwordD(userNameD, 'y', -3);
    Coord_Rect toSignupD(-5, -8, 5.5, 1.5);
    Coord_Rect rectBoxA(-6.5, -3.5, 12.5, 7);
    Coord_Rect rectBoxB(-6.3, -3.3, 12.1, 6.6);

    Text logInScreen(-2, 5, pageTextC, "LOGIN SCREEN", GLUT_BITMAP_TIMES_ROMAN_24);
    Text userNameT(-4.8, 2.2, TitleC, "Enter User-name:", GLUT_BITMAP_HELVETICA_18);
    Text passwordT(-4.8, -0.8, TitleC, "Enter Password:", GLUT_BITMAP_HELVETICA_18);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 4.5, -2.8, logInButtonC);
    Button logInButton("Log In", logInButtonC, logInButtonTextC, logInButtonD);
    Button toSignup("New to The SCHOLAR?", toSignupC, logInButtonTextC, toSignupD);
    rectOutline rectBoxa(rectBoxA, rectBoxC);
    rectOutline rectBoxb(rectBoxB, rectBoxC);

    void addlogInComponents(GUIPage *logInPage)
    {
        logInPage->addComponent(&logInScreen);
        logInPage->addComponent(&userNameB);
        logInPage->addComponent(&passwordB);
        logInPage->addComponent(&userNameT);
        logInPage->addComponent(&passwordT);
        logInPage->addComponent(&showPassword);
        logInPage->addComponent(&logInButton);
        logInPage->addComponent(&toSignup);
        logInPage->addComponent(&rectBoxa);
        logInPage->addComponent(&rectBoxb);
    }
} // namespace LogIn

/***** Sign Up Page *******/
namespace SignUp
{
    Color userNameC(0.978, 0.849, 0.9055);
    Color passwordC = userNameC;
    Color boxTextC(0.23, 0.17, 0.91);
    Color signUpTextC(1, 1, 0);
    Color signUpButtonTextC(1, 0, 1);
    Color signUpButtonC(0.1, 0.9, 0.43);
    Color pageTextC(1, 0, 0);
    Color toLoginC(0.3, 0.9, 0.6);
    Color rectBoxC(1, 1, 1);
    Color TitleC(0.5, 0, 0.5);

    Coord_Rect signUpButtonD(-2, -6, 3, 1.2);
    Coord_Rect userNameD(-5, 0, 9, 1.9);
    Coord_Rect passwordD(userNameD, 'y', -3);
    Coord_Rect toLoginD(-3, -8, 4.8, 1.3);
    Coord_Rect rectBoxA(-6.5, -3.5, 12.5, 7);
    Coord_Rect rectBoxB(-6.3, -3.3, 12.1, 6.6);

    Text signUpScreen(-2, 5, pageTextC, "SIGNUP SCREEN", GLUT_BITMAP_TIMES_ROMAN_24);
    Text userNameT(-4.8, 2.2, TitleC, "Enter User-name:", GLUT_BITMAP_HELVETICA_18);
    Text passwordT(-4.8, -0.8, TitleC, "Enter Password:", GLUT_BITMAP_HELVETICA_18);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 4.5, -2.8, signUpButtonC);
    Button signUpButton("Sign Up", signUpButtonC, signUpButtonTextC, signUpButtonD);
    Button toLogin("Already a member?", toLoginC, signUpButtonTextC, toLoginD);
    rectOutline rectBoxa(rectBoxA, rectBoxC);
    rectOutline rectBoxb(rectBoxB, rectBoxC);

    void addsignUpComponents(GUIPage *signUpPage)
    {
        signUpPage->addComponent(&signUpScreen);
        signUpPage->addComponent(&userNameB);
        signUpPage->addComponent(&passwordB);
        signUpPage->addComponent(&userNameT);
        signUpPage->addComponent(&passwordT);
        signUpPage->addComponent(&showPassword);
        signUpPage->addComponent(&signUpButton);
        signUpPage->addComponent(&toLogin);
        signUpPage->addComponent(&rectBoxa);
        signUpPage->addComponent(&rectBoxb);
    }
} // namespace SignUp

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

    glutDisplayFunc(callBackFun);
    glutReshapeFunc(ReshapeCallBack);
    glutMouseFunc(mousePressed);
    glutKeyboardFunc(keyPressed);
    initColor();

    glutCreateSubWindow(mainWindowIndex, 1, 1, 200, 100);
    glutDisplayFunc(showClock);
    glutReshapeFunc(ReshapeCallBack);
    initColor();

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
        }
        else if (activePage[PAGE]->buttonPressed(&welcome::loginButton))
        {
            PAGE = LOGIN_P;
        }
    }
    else if (PAGE == LOGIN_P)
    {
        if (activePage[PAGE]->buttonPressed(&LogIn::logInButton))
        {
            userName = activePage[PAGE]->getText(&LogIn::userNameB);
            password = activePage[PAGE]->getText(&LogIn::passwordB);
            std::cout << "User = " << userName << "\nPass = " << password << "\n";
            logIn LogInObject(userName, password);
            std::cout << "Logged In";
        }
        else if (activePage[PAGE]->buttonPressed(&LogIn::toSignup))
        {
            PAGE = SIGNUP_P;
        }
    }
    else if (PAGE == SIGNUP_P)
    {
        if (activePage[PAGE]->buttonPressed(&SignUp::signUpButton))
        {
            userNameN = activePage[PAGE]->getText(&SignUp::userNameB);
            passwordN = activePage[PAGE]->getText(&SignUp::passwordB);
            std::cout << "User = " << userNameN << "\nPass = " << passwordN << "\n";
            signUp SignUpObject(userNameN, passwordN);
            SignUpObject.signup();
            std::cout << "Signed Up";
        }
        else if (activePage[PAGE]->buttonPressed(&SignUp::toLogin))
        {
            PAGE = LOGIN_P;
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
                std::cout << "User = " << userName << "\nPass = " << password << "\n";
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
                std::cout << "User = " << userName << "\nPass = " << password << "\n";
                if(userNameN=="")
                {
                    createErrorWindow("Please Enter User-Name");
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
