class Coord_Rect
{
public:
    float x; //bottom left x co-ordinate
    float y; //bottom left y co-ordinate
    float height;
    float width;
    float xw;
    float yh;
    /* int x1; //x1,y1 is top left corner x2,y2 is bottom right corner
    int y1;
    int x2; //x2 = x1 + width
    int y2;  //y2 = y1 + height
    int height;
    int width;*/
public:
    Coord_Rect(float _x, float _y, float _w, float _h)
    {
        x = _x;
        y = _y;
        width = _w;
        height = _h;
        xw = _x + _w;
        yh = _y + _h;
    }
    /*Coord_Rect(int _x,int _y,int _w,int _h)
    {
        x= toFloatX(_x);
        y =toFloatY(_y);
        xw = toFloatX(_x+_w);
        yh = toFloatY(_y+_h);
        width = xw-x;
        height = yh -y;
    }*/
    bool liesInside(float x1, float y1) //checks to see if x,y lies inside given rectangular box
    {
        //if(x>x1 && x<x2&& y>y1 && y<y2)
        if ((x1 >= x && x1 <= (x + width)) && (y1 >= y && y1 <= (y + height)))
            return true;
        else
            return false;
    }
};
/*void glDrawP(Coord_Rect a)
  {
      std::cout<<a.x;
     glBegin(GL_POLYGON);
     glVertex2f(a.x,a.y);
     glVertex2f(a.x,w,a.y);
     glVertex2f(a.xw,a.yh);
     glVertex2f(a.x,a.yh);
     glEnd();
 }*/
class Color
{
    float r;
    float g;
    float b;
    float a=DIM_FACTOR;
public:
    Color(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    void setColor(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    void applyColor()
    {
        glColor3f(r, g, b);
    }
    void dimColor()
    {
        float r1=0;
        float g1=0;
        float b1=0;
        if(r-a>=0)
            r1=r-a;
        if(g-a>=0)
            g1=g-a;
        if(b-a>=0)
            b1=b-a;
        glColor3f(r1,g1,b1);
      // glColor3f(0,0,0);
    }
    void briColor()
    {
        float r1=1;
        float g1=1;
        float b1=1;
        if(r+a<=1)
            r1=r+a;
        if(g+a<=1)
            g1=g+a;
        if(b+a<=1)
            b1=b+a;
        glColor3f(r1,g1,b1);
    }
};


