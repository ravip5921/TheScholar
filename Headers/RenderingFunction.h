#include "./Classes.h"
#include <cmath>

void glDrawP(float x, float y, float w, float h)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void glDrawP(Coord_Rect p)
{
    glBegin(GL_POLYGON);
    glVertex2f(p.x, p.y);
    glVertex2f(p.xw, p.y);
    glVertex2f(p.xw, p.yh);
    glVertex2f(p.x, p.yh);
    glEnd();
}
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle

        float x = r * cosf(theta); //calculate the x component
        float y = r * sinf(theta); //calculate the y component

        glVertex2f(x + cx, y + cy); //output vertex
    }
    glEnd();
}
void printText(float x, float y,Color rgb=Color(1,1,1), const char *text="", void *font=GLUT_BITMAP_HELVETICA_12)
{
    rgb.applyColor();
    char *c;
    glRasterPos2f(x, y);
    char buf[100] = {0};
    sprintf(buf, text);
    for (c = buf; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
    glColor3f(1.0, 1.0, 0.0);
    glutPostRedisplay();
}
void printText(std::string tex, double x, double y, float max_x, void *font)
{
    glRasterPos2d(x, y);
    int i = 0, a;
    float tsize = tex.size() * CHAR_WIDTH;
    if (tsize < (max_x - x))
        a = 0;
    else
        a = (tex.size() - (int)((max_x - x) / CHAR_WIDTH));

    for (i = a; tex[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, tex[i]);
    }
    glColor3f(0, 0, 0);
    glutPostRedisplay();
}

void printTextInBox(std::string tex, Coord_Rect pos, void *font,float GAP = CHAR_WIDTH*2)
{
    pos.x += GAP;
    pos.y += GAP;
    float max_x = pos.xw ;
    glRasterPos2d(pos.x, pos.y);
    int i = 0, a;
    float tsize = (tex.size()) * CHAR_WIDTH;
    if (tsize < (max_x - pos.x))
        a = 0;
    else
        a = (tex.size() - (int)((max_x - pos.x) / CHAR_WIDTH));

    for (i = a; tex[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, tex[i]);
    }
    glutPostRedisplay();
}
void printTextPass(std::string tex, Coord_Rect pos, void *font)
{
    float GAP = CHAR_WIDTH * 1.5; //PADDING
    pos.x += GAP;
    pos.y += GAP;
    int max_Len = ((pos.width) / CHAR_WIDTH) - 6.5; //To Stop Overflow caused by error in CHAR_WIDTH
    glRasterPos2d(pos.x, pos.y);
    for (int j = 0; j < max_Len && j < tex.size(); j++)
    {
        glutBitmapCharacter(font, CHAR_MASK);
    }
    glutPostRedisplay();
}
void printTextInButton(std::string text, Coord_Rect dim, void *font=GLUT_BITMAP_HELVETICA_12,float GAP=CHAR_WIDTH*2)
{
    char *c;
    glRasterPos2f(dim.x+GAP, dim.y+GAP);
    char buf[100] = {0};
    sprintf(buf, text.c_str());
    for (c = buf; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
    glColor3f(1.0, 1.0, 0.0);
    glutPostRedisplay();
}

float toFloatX(int x)
{
    float tx;

    tx = static_cast<float>(x) / (WID / (2 * COORD_X));

    if (tx < COORD_X)
    {
        tx = (COORD_X - tx) * (-1);
    }
    if (tx > COORD_X)
    {
        tx = (tx - COORD_X);
    }
    return tx;
}
float toFloatY(int y)
{
    float ty = static_cast<float>(y) / (HEI / (2 * COORD_Y));
    if (ty < COORD_Y)
    {
        ty = COORD_Y - ty;
    }
    if (ty > COORD_Y)
    {
        ty = (ty - COORD_Y) * (-1);
    }
    return ty;
}
void glDrawRecOutline(float a, float b, float c, float d)
{
    glBegin(GL_LINES);
    glVertex2f(a, b); //LefttLine
    glVertex2f(a, d);

    glVertex2f(c, b); //RightLine
    glVertex2f(c, d);

    glVertex2f(a, b); //RLowerLine
    glVertex2f(c, b);

    glVertex2f(a, d); //UpperLine
    glVertex2f(c, d);
    glEnd();
}
void glDrawRecOutlineTextBox(Coord_Rect pos)
{
    float PADDING = CHAR_WIDTH / 1.5;
    pos.x += PADDING;
    pos.y += PADDING;
    pos.xw -= PADDING;
    pos.yh -= PADDING;
    glBegin(GL_LINES);
    glVertex2f(pos.x, pos.y); //BottomLine
    glVertex2f(pos.xw, pos.y);

    glVertex2f(pos.xw, pos.y); //RightLine
    glVertex2f(pos.xw, pos.yh);

    glVertex2f(pos.xw, pos.yh); //TopLine
    glVertex2f(pos.x, pos.yh);

    glVertex2f(pos.x, pos.yh); //LeftLine
    glVertex2f(pos.x, pos.y);
    glEnd();
}
void glDrawRecOutlineCoordBox(Coord_Rect pos)
{
    glBegin(GL_LINES);
    glVertex2f(pos.x, pos.y); //BottomLine
    glVertex2f(pos.xw, pos.y);

    glVertex2f(pos.xw, pos.y); //RightLine
    glVertex2f(pos.xw, pos.yh);

    glVertex2f(pos.xw, pos.yh); //TopLine
    glVertex2f(pos.x, pos.yh);

    glVertex2f(pos.x, pos.yh); //LeftLine
    glVertex2f(pos.x, pos.y);
    glEnd();
}
