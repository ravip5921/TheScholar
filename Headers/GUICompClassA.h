#include "Headers/RenderingFunction.h"
#include "Headers/classes.h"
class GUIcomponent
{
    bool active;
public:
    GUIcomponent() {active = true;}
    bool isActive() { return active;}
    void setActive(bool _active) { active = _active;}

    virtual void render() = 0;
    virtual void mouseHandler(int button,int state,int x,int y) = 0;
    virtual void keyboardHandler(unsigned char key,int x, int y) = 0;
};

class GUIPage
{
    std::vector<GUIcomponent*> components;
public:
    void addComponent(GUIcomponent* _component)
    {
        components.push_back(_component);
    }
    void render()
    {
        for(int i=0;i<components.size();i++)
                components[i]->render();
    }
    void keyboardHandler(unsigned char key,int x, int y)
    {
        for(int i=0;i<components.size();i++)
            if(components[i]->isActive())
                components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button,int state,int x,int y)
    {
        for(int i=0;i<components.size();i++)
            if(components[i]->isActive())
                components[i]->mouseHandler( button, state, x, y);
    }
};

class TextBox:public GUIcomponent
{
    bool selected;
    bool showTxt;
    std::string textField;
    Coord_Rect position;
    float tc[3];
    Color c1;
public:
    TextBox(float x,float y,float h=1,float w=3,float r=0,float g=0,float b=0,bool Selected=false):position(x,y,w,h),c1(r,g,b)
    {
       /* position.x =x;
        position.y = y;
        position.height =h;
        position.width =w;*/
        selected = Selected;
        showTxt= Selected;
        setColour(r,g,b);
    }
    TextBox(Coord_Rect pos,Color rgb=Color(0,0,0),bool _selected =false):position(pos),c1(rgb)
    {
        selected =_selected;
        c1.applyColor();
    }
    void setColour(float r=0,float g=0,float b=0)
    {
        tc[0]=r;
        tc[1]=g;
        tc[2]=b;
    }
    void showText(bool show)
    {
        showTxt=show;
    }
    void render()
    {
        //glDrawRecOutline(position.x,position.y,position.x+position.width,position.y+position.height);
         glDrawP(position.x,position.y,position.x+position.width,position.y+position.height);
        //draw rectangular box of textbox based on position
        //if active draw one kind of box if not active draw another kind
        if(selected || showTxt)
        {
            glColor3f(tc[0],tc[1],tc[2]);
            printText(textField,position.x+0.1,position.y+0.2,position.x+position.width,GLUT_BITMAP_HELVETICA_12);
        }

    }
     void keyboardHandler(unsigned char key,int x, int y)
    {
        //if selected then text.push_back(key) after checking the key value
        if(selected)
        {
            if(key == TAB_KEY || key == ENTER_KEY)
            {
                value() = textField;
                std::cout<<name;
            }
            else if(key>=36 && key<=126)
            {
              textField.push_back(key);
            }
            else if(key=DEL_KEY && textField.size()>0)
            {
                textField.pop_back();
                value()=textField;
            }
        }

    }
    void mouseHandler(int button,int state,int x,int y)
    {
        //if button == right and state == down and liesInside(x,y) set selected = true
        float X=toFloatX(x);
        float Y=toFloatY(y);
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && position.liesInside(X,Y))
        {
            selected=true;
        }
        else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            selected = false;
        }
    }
};

class PasswordBox:public TextBox
{
    bool showPass;
//    PasswordBox()
};



