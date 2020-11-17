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
            //if (components[i]->isActive())
            components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            //if (components[i]->isActive())
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
        printTextInBox(textField, position, GLUT_BITMAP_HELVETICA_12);
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
class Text : public GUIcomponent
{
    float x;
    float y;
    Color rgb;
    void *font;
    const char *text;

public:
    Text(float _x, float _y, Color _rgb, const char *_text, void *_f) : rgb(_rgb)
    {
        x = _x;
        y = _y;
        text = _text;
        font = _f;
    }
    Text(float _x, float _y, Color _rgb, std::string _text, void *_f) : rgb(_rgb)
    {
        x = _x;
        y = _y;
        text = _text.data();
        font = _f;
    }
    void render()
    {
        printText(x, y, rgb, text, font);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
};
class CheckBox : public GUIcomponent
{
    bool selected;
    Coord_Rect dimensions;
    Color colr;
    PasswordBox *parent;

public:
    CheckBox(PasswordBox *_parent, Coord_Rect _dimensions, Color _colr = Color(1, 1, 1), bool _selected = false) : dimensions(_dimensions), colr(_colr)
    {
        parent = _parent;
        selected = _selected;
    }
    CheckBox(PasswordBox *_parent, float x, float y, Color _colr = Color(1, 1, 1), bool _selected = false) : dimensions(x, y, CHECK_BOX_DIMENSION, CHECK_BOX_DIMENSION), colr(_colr)
    {
        parent = _parent;
        selected = _selected;
    }
    void setActive(bool _active)
    {
        active = _active;
        selected = active;
    }
    void render()
    {
        colr.applyColor();
        glDrawRecOutlineCoordBox(dimensions);
        if (selected)
        {
            glRasterPos2f(dimensions.x + 0.09, dimensions.y + 0.11);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '/');
        }

        // DrawCircle(0, 0, .1, 20);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        //selected=true;

        /*if(key=='/')
            selected=true;
        else if(key=='.')
            selected=false;*/
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        std::cout << dimensions.x << " " << toFloatX(x);
        if (dimensions.liesInside(toFloatX(x), toFloatY(y)) && !selected && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
        {
            setActive(true);
            parent->showPass(true);
        }
        else if (dimensions.liesInside(toFloatX(x), toFloatY(y)) && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
        {
            setActive(false);
            parent->showPass(false);
        }
    }
};
class Button : public GUIcomponent
{
    bool pressed;
    std::string buttonText;
    Coord_Rect buttonDimension;
    Color buttonColor;
    Color textColor;
    void *f;

public:
    Button(const char *_text, Color _bColor, Color _tColor, Coord_Rect _dim) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        pressed = false;
        buttonText = std::string(_text);
        f = GLUT_BITMAP_HELVETICA_12;
    }
    Button(std::string _text, Color _bColor, Color _tColor, Coord_Rect _dim) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        pressed = false;
        buttonText = _text;
        f = GLUT_BITMAP_HELVETICA_12;
    }
    void setFont(void *_f)
    {
        f = _f;
    }
    void render()
    {
        setActive(pressed);
        if (isActive())
        {
            buttonColor.dimColor();
        }
        else
        {
            buttonColor.applyColor();
        }
        glDrawP(buttonDimension);
        textColor.applyColor();
        printTextInBox(buttonText, buttonDimension, f);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        if (buttonDimension.liesInside(toFloatX(x), toFloatY(y)) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            pressed = true;
        }
        else
        {
            pressed = false;
        }
    }
};
class rectOutline:public GUIcomponent
{
    Coord_Rect dimension;
    Color color;
public:
    rectOutline(Coord_Rect _dim,color _color=Color(0,0,0)):dimension(_dim),color(_color){}
    void render()
    {
        color.applyColor();
        glDrawRecOutlineCoordBox(dimension);
    }
    void keyboardHandler(unsigned char key,int x,,int y)
    {
        return;
    }
    void mouseHandler(int button ,int state,int x,int y)
    {
        return;
    }
};
