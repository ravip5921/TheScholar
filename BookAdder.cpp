#include <GL/gl.h>   //lib for openGL
#include <GL/glu.h>  //lib of glut utilities
#include <GL/glut.h> //lib glut
#include <iostream>
#include <vector>
#include "Headers/vars.h"
#include "Headers/GUICompClass.h"
#include "Headers/BookAdderPage.h"
#include "Headers/DatabaseCreator.h"

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);
void getValues();
int windowWidth();
int windowHeight();

GUIPage BookAdderPage;

BookDescriptor bd;

int main(int argc, char **argv) //default arguments of main
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(INI_X, INI_Y);
    glutInitWindowSize(WID_INI, HEI_INI);
    mainWindowIndex = glutCreateWindow("Book Database");

    BookAdder::addBookAdderComponents(&BookAdderPage);
    bd.bookPath = "./database/book/book1.pdf";
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
    glColor3f(0, 1, 0);
    WID = windowWidth();
    HEI = windowHeight();

    BookAdderPage.render();
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
    BookAdderPage.mouseHandler(button, state, x, y);
    if (BookAdderPage.buttonPressed(&BookAdder::AddBookButton))
    {
        getValues();
    }
}
void keyPressed(unsigned char key, int x, int y)
{
    BookAdderPage.keyboardHandler(key, x, y);
    if (key == ENTER_KEY || key == TAB_KEY)
    {
        if (BookAdderPage.isActiveBox(&BookAdder::NameB))
        {
            BookAdderPage.setActiveBox(&BookAdder::NameB, false);
            BookAdderPage.setActiveBox(&BookAdder::AuthorB, true);
        }
        else if (BookAdderPage.isActiveBox(&BookAdder::AuthorB))
        {
            BookAdderPage.setActiveBox(&BookAdder::AuthorB, false);
            BookAdderPage.setActiveBox(&BookAdder::GenreB, true);
        }
        else if (BookAdderPage.isActiveBox(&BookAdder::GenreB))
        {
            BookAdderPage.setActiveBox(&BookAdder::GenreB, false);
            BookAdderPage.setActiveBox(&BookAdder::DateB, true);
        }
        else if (BookAdderPage.isActiveBox(&BookAdder::DateB))
        {
            BookAdderPage.setActiveBox(&BookAdder::DateB, false);
            BookAdderPage.setActiveBox(&BookAdder::ExtraDesB, true);
        }
        else if (BookAdderPage.isActiveBox(&BookAdder::ExtraDesB) && key == ENTER_KEY)
        {
            getValues();
        }
    }
}
void getValues()
{
    bd.name = BookAdderPage.getText(&BookAdder::NameB);
    bd.author = BookAdderPage.getText(&BookAdder::AuthorB);
    bd.genre = BookAdderPage.getText(&BookAdder::GenreB);
    bd.date = BookAdderPage.getText(&BookAdder::DateB);
    bd.extrades = BookAdderPage.getText(&BookAdder::ExtraDesB);

    createRequiredDirectories();
    bd.createDescriptorFile();
    bd.createAllDirectories();

    BookAdderPage.setActiveBox(&BookAdder::ExtraDesB, false);
    BookAdderPage.setActiveBox(&BookAdder::NameB, true);

    BookAdderPage.setText(&BookAdder::NameB, "");
    BookAdderPage.setText(&BookAdder::AuthorB, "");
    BookAdderPage.setText(&BookAdder::GenreB, "");
    BookAdderPage.setText(&BookAdder::DateB, "");
    BookAdderPage.setText(&BookAdder::ExtraDesB, "");
}
int windowWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}
int windowHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}
