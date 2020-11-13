#include "./Classes.h"
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
  // std::cout<<p.x<<'\t'<<p.xw;
  glBegin(GL_POLYGON);
  glVertex2f(p.x, p.y);
  glVertex2f(p.xw, p.y);
  glVertex2f(p.xw, p.yh);
  glVertex2f(p.x, p.yh);
  glEnd();
}
void printText(float x, float y, const char *text, void *font, float r, float g, float b)
{
  glColor3f(r, g, b);
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
// std::string& value()
//  return userName;

void printText(std::string tex, double x, double y, float max_x, void *font)
{
  // glColor3f(0,0,0);
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

void printTextInBox(std::string tex, Coord_Rect pos, void *font)
{
  // glColor3f(0,0,0);
  float GAP = CHAR_WIDTH * 2;
  pos.x += GAP;
  pos.y += GAP;
  pos.xw -= GAP;

  glRasterPos2d(pos.x, pos.y);
  int i = 0, a;
  float tsize = tex.size() * CHAR_WIDTH;
  if (tsize < (pos.xw - CHAR_WIDTH - pos.x))
    a = 0;
  else
    a = (tex.size() - (int)((pos.xw - CHAR_WIDTH - pos.x) / CHAR_WIDTH));

  for (i = a; tex[i] != '\0'; i++)
  {
    glutBitmapCharacter(font, tex[i]);
  }
  //glColor3f(0,0,0);
  glutPostRedisplay();
}
float toFloatX(int x)
{
  float tx;

  tx = static_cast<float>(x) / (70 / 2);

  if (tx < 10)
  {
    tx = (10 - tx) * (-1);
  }
  if (tx > 10)
  {
    tx = (tx - 10);
  }
  return tx;
}
float toFloatY(int y)
{
  float ty = static_cast<float>(y) / (65 / 2);
  if (ty < 10)
  {
    ty = 10 - ty;
  }
  if (ty > 10)
  {
    ty = (ty - 10) * (-1);
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
