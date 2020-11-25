#include "./RenderingFunction.h"

class GUIcomponent
{
protected:
    bool active;

public:
    GUIcomponent() { active = false; }
    bool isActive() { return active; }
    void setActive(bool _active) { active = _active; }

    virtual void render() = 0;
    virtual void mouseHandler(int button, int state, int x, int y) = 0;
    virtual void keyboardHandler(unsigned char key, int x, int y) = 0;
    virtual void passiveMouseHandler(int x, int y) = 0;
};

class TextBox : public GUIcomponent
{
protected:
    bool selected;
    std::string textField;
    Coord_Rect position;
    Color boxC;
    Color textC;
    void *f;

public:
    TextBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : position(pos), boxC(box), textC(txt)
    {
        selected = _selected;
        f = GLUT_BITMAP_HELVETICA_12;
    }
    std::string getText()
    {
        return textField;
    }
    void setText(std::string _text) //probably won't be used
    {
        textField = _text;
    }
    void setFont(void *_f)
    {
        f = _f;
    }
    void setActive(bool _active = true)
    {
        active = _active;
        selected = active;
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
        printTextInBox(textField, position, f);
        if (isActive())
        {
            if (blinkerT % 200 >= 0 && blinkerT % 200 <= 100)
                glutBitmapCharacter(f, '|');
            blinkerT++;
        }
        else
            blinkerT = 0;
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        if (selected)
        {
            if (key == ENTER_KEY || key == TAB_KEY)
            {
            }
            else if (key >= 36 && key <= 126 || key == SPACE_KEY)
            {
                textField.push_back(key);
            }
            else if (key = DEL_KEY && textField.size() > 0)
            {
                textField.pop_back();
            }
        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        float X = toFloatX(x);
        float Y = toFloatY(y);
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && position.liesInside(X, Y))
        {
            selected = true;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            selected = false;
        }
    }
    void passiveMouseHandler(int x, int y)
    {
        return;
    }
};
class PasswordBox : public TextBox
{
    bool showpass;
    void *f;

public:
    PasswordBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : TextBox(pos, box, txt, _selected)
    {
        showpass = false;
        f = GLUT_BITMAP_HELVETICA_12;
    }
    void showPass(bool _showPass)
    {
        showpass = _showPass;
    }
    bool isShowing()
    {
        return showpass;
    }
    void setFont(void *_f)
    {
        f = _f;
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
        if (showpass)
            printTextInBox(textField, position, f);
        else
            printTextPass(TextBox::textField, TextBox::position, GLUT_BITMAP_TIMES_ROMAN_24);
        if (isActive())
        {
            if (blinkerP % 200 >= 0 && blinkerP % 200 <= 100)
                glutBitmapCharacter(f, '|');
            blinkerP++;
        }
        else
            blinkerP = 0;
    }
};
class Text : public GUIcomponent
{
    float x;
    float y;
    Color rgb;
    void *font;
    std::string text;
    bool background;
    Color backgroundC;
    Coord_Rect backgroundD;

public:
    Text(float _x, float _y, Color _rgb, const char *_text, void *_f, bool _bg = false, Color _bgC = Color(WC_R, WC_G, WC_B), float _w = 0, float _h = 0) : rgb(_rgb), text(std::string(_text)), backgroundC(_bgC), backgroundD(_x - 0.1, _y - 0.3, _w, _h)
    {
        x = _x;
        y = _y;
        font = _f;
        background = _bg;
    }
    Text(float _x, float _y, Color _rgb, std::string _text, void *_f, bool _bg = false, Color _bgC = Color(WC_R, WC_G, WC_B), float _w = 0, float _h = 0) : rgb(_rgb), text(_text), backgroundC(_bgC), backgroundD(_x - 0.1, _y - 0.3, _w, _h)
    {
        x = _x;
        y = _y;
        font = _f;
        background = _bg;
    }
    void setText(std::string *_text)
    {
        text = *_text;
    }
    void render()
    {
        if (background)
        {
            backgroundC.applyColor();
            glDrawP(backgroundD);
        }
        printText(x, y, rgb, text.c_str(), font);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
    void passiveMouseHandler(int x, int y)
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
        parent->setActive();
    }
    void render()
    {
        colr.applyColor();
        glDrawRecOutlineCoordBox(dimensions);
        if (selected)
        {
            glRasterPos2f(dimensions.getx() + 0.09, dimensions.gety() + 0.11);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '/');
        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        std::cout << dimensions.getx() << " " << toFloatX(x);
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
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void passiveMouseHandler(int x, int y)
    {
        return;
    }
};
class Button : public GUIcomponent
{
    bool pressed;
    std::string buttonText;
    Coord_Rect buttonDimension;
    Color buttonColor;
    Color textColor;
    float gapX;
    float gapY;
    void *f;

public:
    Button(const char *_text, Color _bColor, Color _tColor, Coord_Rect _dim, float _x = CHAR_WIDTH * 2, float _y = CHAR_WIDTH * 2) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        pressed = false;
        buttonText = std::string(_text);
        f = GLUT_BITMAP_HELVETICA_12;
        gapX = _x;
        gapY = _y;
    }
    Button(std::string _text, Color _bColor, Color _tColor, Coord_Rect _dim, float _x = CHAR_WIDTH * 2, float _y = CHAR_WIDTH * 2) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        pressed = false;
        buttonText = _text;
        f = GLUT_BITMAP_HELVETICA_12;
        gapX = _x;
        gapY = _y;
    }
    void setText(std::string _text)
    {
        buttonText = _text;
    }
    std::string getText()
    {
        return buttonText;
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
        printTextInButton(buttonText, buttonDimension, f, gapX, gapY);
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
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void passiveMouseHandler(int x, int y)
    {
        return;
    }
};
class ScrollBox : public GUIcomponent
{
    std::vector<std::string> data;
    Color bgColor;
    Coord_Rect dim;
    std::vector<Coord_Rect> bDim;
    std::vector<Button> dataB;
    int maxN;
    int top;
    bool scrolled;

public:
    ScrollBox(std::vector<std::string> _data, Coord_Rect _dim, int _maxN, Color _bgC = Color(WC_R, WC_G, WC_B)) : dim(_dim), bgColor(_bgC)
    {
        data = _data;
        maxN = _maxN;
        top = 0;
        scrolled = false;
        for (int i = 1; i <= maxN; i++)
        {
            Coord_Rect d(dim.getx(), dim.getyh() - (i * (dim.getheight() / maxN)), dim.getwidth(), (dim.getheight() / maxN));
            bDim.push_back(d);
        }
        for (int i = 0; i < maxN; i++)
        {
            Button button(data[i], Color(1, 0, 0), Color(1, 1, 1), bDim[i], 0.1, 0.1);
            dataB.push_back(button);
        }
    }
    void refreshBox()
    {
        for (int i = 0; i < maxN; i++)
        {
            dataB[i].setText(data[i + top]);
        }
    }
    std::string getButtonText(int button,int state,int x,int y)
    {
        for(int i=0;i<maxN;i++)
        if (bDim[i].liesInside(toFloatX(x), toFloatY(y) && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN))
        {
            return dataB[i].getText();
        }
        return "";
    }
    void render()
    {
        if (scrolled)
        {
            refreshBox();
            scrolled = false;
        }
        glDrawRecOutlineCoordBox(dim);
        for (int i = 0; i < maxN; i++)
        {
            dataB[i].render();
            if (i != 0)
            {
                glColor3f(1, 1, 1);
                glBegin(GL_LINES);
                glVertex2f(bDim[i].getx(), bDim[i].getyh());
                glVertex2f(bDim[i].getxw(), bDim[i].getyh());
                glEnd();
            }
        }
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        std::cout<<getButtonText(button,state, x, y);
        if (dim.liesInside(toFloatX(x), toFloatY(y)))
        {
            if (button == 4 && state == GLUT_DOWN && (data.size() - top > maxN))
            {
                top++;
                scrolled = true;
            }
            else if (button == 3 && state == GLUT_DOWN && (top > 0))
            {
                top--;
                scrolled = true;
            }
            else
            {
                for (int i = 0; i < maxN; i++)
                    dataB[i].mouseHandler(button, state, x, y);
            }
        }
    }
    void passiveMouseHandler(int x, int y)
    {
        return;
    }
};
class rectOutline : public GUIcomponent
{
    Coord_Rect dimension;
    Color color;

public:
    rectOutline(Coord_Rect _dim, Color _color = Color(0, 0, 0)) : dimension(_dim), color(_color) {}
    void render()
    {
        color.applyColor();
        glDrawRecOutlineCoordBox(dimension);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
    void passiveMouseHandler(int x, int y)
    {
        return;
    }
};
class GUIBlock
{
    std::vector<GUIcomponent *> components;

public:
    void addComponent(GUIcomponent *_component)
    {
        components.push_back(_component);
    }
    bool buttonPressed(Button *_button)
    {
        if (_button->isActive())
            return true;
        return false;
    }

    void setText(Text *_textB, std::string *_text)
    {
        _textB->setText(_text);
    }
    void setText(TextBox *_textB, std::string *_text)
    {
        _textB->setText(*_text);
    }
    void render()
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->render();
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseHandler(button, state, x, y);
    }
    void passiveMouseHandler(int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->passiveMouseHandler(x, y);
    }
};
class GUIPage
{
    std::vector<GUIcomponent *> components;

public:
    void addComponent(GUIcomponent *_component)
    {
        components.push_back(_component);
    }
    bool buttonPressed(Button *_button)
    {
        if (_button->isActive())
            return true;
        return false;
    }
    std::string getText(TextBox *_textbox)
    {
        return _textbox->getText();
    }
    bool isActiveBox(TextBox *_textbox)
    {
        return _textbox->isActive();
    }
    void setActiveBox(TextBox *_textbox, bool _value = true)
    {
        _textbox->setActive(_value);
    }
    void setText(Text *_textB, std::string *_text)
    {
        _textB->setText(_text);
    }
    void setText(TextBox *_textB, std::string *_text)
    {
        _textB->setText(*_text);
    }
    void setText(TextBox *_textB, const char *_text)
    {
        _textB->setText(_text);
    }
    std::string getButtonText(int button,int state,int x,int y,ScrollBox * sb)
    {
            return sb->getButtonText(button,state,x,y);
    }
    void render()
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->render();
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseHandler(button, state, x, y);
    }
    void passiveMouseHandler(int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->passiveMouseHandler(x, y);
    }
};
