#include "./RenderingFunction.h"
//#include "./classes.h"
class GUIcomponent
{
    protected:
    bool active;

public:
    GUIcomponent() { active = true; }
    bool isActive() { return active; }
    void setActive(bool _active) { active = _active; }

    virtual void render() = 0;
    virtual void mouseHandler(int button, int state, int x, int y) = 0;
    virtual void keyboardHandler(unsigned char key, int x, int y) = 0;
};

class GUIPage
{
    std::vector<GUIcomponent *> components;

public:
    void addComponent(GUIcomponent *_component)
    {
        components.push_back(_component);
    }
    void render()
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->render();
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            if (components[i]->isActive())
                components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            if (components[i]->isActive())
                components[i]->mouseHandler(button, state, x, y);
    }
};

class TextBox : public GUIcomponent
{
protected:
    bool selected;
    // bool showTxt;
    std::string textField;
    Coord_Rect position;
    Color boxC;
    Color textC;

public:
    TextBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : position(pos), boxC(box), textC(txt)
    {
        selected = _selected;
    }
    std::string getText()
    {
        return textField;
    }
    void setText(std::string _text) //probably won't be used
    {
        textField = _text;
    }
    //void showText(bool show)

    //  showTxt = show;
    void render()
    {
        setActive(selected);
        if (isActive())
        {
            boxC.applyColor();
        }
        else
        {
            boxC.dimColor();
        }
        glDrawP(position);
        textC.applyColor();
        glDrawRecOutlineTextBox(position);
        //draw rectangular box of textbox based on position
        //if active draw one kind of box if not active draw another kind
        //if (selected || showTxt)
        // {
        // textC.applyColor();
        // printText(textField,position.x+0.1,position.y+0.2,position.x+position.width,GLUT_BITMAP_HELVETICA_12);
        printTextInBox(textField, position, GLUT_BITMAP_HELVETICA_12);
        //}
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        //if selected then text.push_back(key) after checking the key value
        if (selected)
        {
            if (key == TAB_KEY || key == ENTER_KEY)
            {
                // userName = textField;
                // std::cout<<userName;
            }
            else if (key >= 36 && key <= 126 || key == SPACE_KEY)
            {
                textField.push_back(key);
            }
            else if (key = DEL_KEY && textField.size() > 0)
            {
                textField.pop_back();
                // userName = textField;
            }
        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        //if button == right and state == down and liesInside(x,y) set selected = true
        float X = toFloatX(x);
        float Y = toFloatY(y);
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && position.liesInside(X, Y))
        {
            selected = true;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            //std::cout<<userName;
            selected = false;
        }
    }
};

class PasswordBox : public TextBox
{
    bool showpass;

public:
    PasswordBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : TextBox(pos, box, txt, _selected)
    {

        showpass = false;
    }
    /*
    void keyboardHandler(unsigned char key,int x,int y) //NEED TO MODIFY ACCORDING TO PASSWORD STANDARDS
    {
    }*/
    void showPass(bool _showPass)
    {
        showpass = _showPass;
    }
    bool isShowing()
    {
        return showpass;
    }
    void render()
    {
        setActive(selected);
        if (isActive())
        {
            boxC.applyColor();
        }
        else
        {
            boxC.dimColor();
        }
        glDrawP(position);
        textC.applyColor();
        glDrawRecOutlineTextBox(position);
        // if (selected || showPass)
        //{
        if (showpass)
            printTextInBox(textField, position, GLUT_BITMAP_HELVETICA_12);
        else
            printTextPass(TextBox::textField, TextBox::position, GLUT_BITMAP_TIMES_ROMAN_24);
        //}
    }
};
class CheckBox : public GUIcomponent
{
    bool selected;
    Coord_Rect dimensions;
    Color colr;

public:
    CheckBox(Coord_Rect _dimensions, Color _colr=Color(1,1,1),bool _selected=false):dimensions(_dimensions),colr(_colr)
    {
        selected = _selected;
    }
    CheckBox(float x,float y,Color _colr=Color(1,1,1),bool _selected=false):dimensions(x,y,CHECK_BOX_DIMENSION,CHECK_BOX_DIMENSION),colr(_colr)
    {
        selected = _selected;
    }
     void setActive(bool _active) { active = _active;
     selected=active; }
    void render()
    {
        colr.applyColor();
        glDrawRecOutlineCoordBox(dimensions);
        if(selected)
        {
            glRasterPos2f(dimensions.x+0.09,dimensions.y+0.11);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'x');
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'/');
        }

       // DrawCircle(0, 0, .1, 20);
    }
    void keyboardHandler(unsigned char key,int x,int y)
    {
        //selected=true;

        /*if(key=='/')
            selected=true;
        else if(key=='.')
            selected=false;*/
    }
    void mouseHandler(int button,int state,int x,int y)
    {
        std::cout<<dimensions.x<<" "<<toFloatX(x);
        if(dimensions.liesInside(toFloatX(x),toFloatY(y)))
            setActive(true);
    }
};
