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
    virtual void mouseMotionHandler(int x, int y) = 0;
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
    float padding;

public:
    TextBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : position(pos), boxC(box), textC(txt)
    {
        selected = _selected;
        f = GLUT_BITMAP_HELVETICA_12;
        padding = CHAR_WIDTH * 2;
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
    void setPadding(float _gap)
    {
        padding = _gap;
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
        printTextInBox(textField, position, f,padding);
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
    void mouseMotionHandler(int x, int y)
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
    void mouseMotionHandler(int x, int y)
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
            colr.briColor();
            glDrawP(dimensions.getx() + 0.09, dimensions.gety() + 0.09, dimensions.getwidth() - 0.18, dimensions.getheight() - 0.15);
        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
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
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class Button : public GUIcomponent
{
    bool showB;
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
        showB=true;
        pressed = false;
        buttonText = std::string(_text);
        f = GLUT_BITMAP_HELVETICA_12;
        gapX = _x;
        gapY = _y;
    }
    Button(std::string _text, Color _bColor, Color _tColor, Coord_Rect _dim, float _x = CHAR_WIDTH * 2, float _y = CHAR_WIDTH * 2) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        showB=true;
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
    void show(bool _show)
    {
        showB=_show;
    }
    void render()
    {
        if(showB)
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
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        if(showB)
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
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class ScrollBox : public GUIcomponent
{
    std::vector<std::string> data;
    Color bgColor;
    Color textC;
    Coord_Rect dim;
    std::vector<Coord_Rect> bDim;
    std::vector<Button> dataB;
    int maxN;
    int top;
    bool scrolled;
    bool scrollable;
    float scrollerX;
    float scrollerY;
    float scrollerW;
    float scrollerH;
    float dec;
    float prevY;

public:
    ScrollBox(std::vector<std::string> _data, Coord_Rect _dim, int _maxN, Color _bgC = Color(WC_R, WC_G, WC_B), Color _textC = Color(0, 0, 0), bool _scrollable = true) : dim(_dim), bgColor(_bgC), textC(_textC)
    {
        data = _data;
        maxN = _maxN;
        top = 0;
        scrolled = false;
        scrollable = _scrollable;
        scrollerX = dim.getxw();
        scrollerY = dim.getyh() - dim.getheight() / 5;
        scrollerW = dim.getwidth() / 15;
        scrollerH = dim.getheight() / 5;
        dec = 0;
        prevY = scrollerY + scrollerH;
        for (int i = 1; i <= maxN; i++)
        {
            Coord_Rect d(dim.getx(), dim.getyh() - (i * (dim.getheight() / maxN)), dim.getwidth(), (dim.getheight() / maxN));
            bDim.push_back(d);
        }
        for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
        {
            Button button(data[i], bgColor, textC, bDim[i], 0.1, 0.1);
            dataB.push_back(button);
        }
    }
    void refreshBox()
    {
        dec = ((scrollerY - dim.gety()) / (data.size() - maxN));
        int i;
        for (i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
        {
            dataB[i].setText(data[i + top]);
        }
        for (int j = i; j < maxN; j++)
        {
            dataB[j].setText("");
        }
    }
    void setData(std::vector<std::string> _data)
    {
        data = _data;
        refreshBox();
    }
    std::string getButtonText(int button, int state, int x, int y)
    {
        if (isActive())
            for (int i = 0; i < maxN; i++)
                if (bDim[i].liesInside(toFloatX(x), toFloatY(y)) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                {
                    return dataB[i].getText();
                }
        return "";
    }
    void render()
    {
        if (scrollable)
        {
            if (scrolled)
            {
                refreshBox();
                scrolled = false;
            }
            if (data.size() > maxN)
            {
                glDrawRecOutlineCoordBox(dim);
                bgColor.briColor();
                glDrawP(dim.getxw(), dim.gety(), scrollerW, dim.getheight());

                bgColor.dimColor();
                glDrawP(scrollerX, scrollerY - top * dec, scrollerW, scrollerH);
            }
        }
        for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
        {
            dataB[i].render();
            if (i != 0)
            {
                textC.applyColor();
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
        if (scrollable)
        {
            prevY = toFloatY(y);
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
        else
        {
            for (int i = 0; i < maxN; i++)
                dataB[i].mouseHandler(button, state, x, y);
        }
    }
    void mouseMotionHandler(int x, int y)
    {
        if (scrollable)
        {
            Coord_Rect scroller(scrollerX, scrollerY - top * dec, scrollerW, scrollerH);
            if (scroller.liesInside(toFloatX(x), toFloatY(y)) && (data.size() - top > maxN) && toFloatY(y) <= prevY)
            {
                top++;
                refreshBox();
                prevY = toFloatY(y);
            }
            else if (scroller.liesInside(toFloatX(x), toFloatY(y)) && top > 0 && toFloatY(y) > prevY)
            {
                top--;
                refreshBox();
                prevY = toFloatY(y);
            }
        }
        return;
    }
};
class BookDetail : public GUIcomponent
{
    std::string bookname;
    std::vector<std::string> bookDes;
    char mode;
    float bookNamePosX;
    float bookNamePosY;
    float descriptionX;
    float descriptionY;
    float featureButtonX;
    float featureButtonY;

    Color navButtonC;
    Color featureButtonC;
    Color titleTextC;
    Color subTitleTextC;
    Color textboxC;
    Color textboxTextC;

    Coord_Rect backButtonD;
    Coord_Rect openBookButtonD;
    void *f1;
    void *f2;
public:

    Button backButton;
    Button openBookButton;
    Button readingButton;
    Button completedButton;
    Button sharedButton;
    Button favouriteButton;
    Button reviewButton;
    Button bookmarkButton;

    TextBox reviewNum;
    TextBox shareUser;
    TextBox bookmarkText;

    BookDetail(char _mode, std::string _bookname = "", Color _navButtonC = Color(0.1, 0.3, 0.7), Color _featureButtonC = Color(0.6, 0.5, 0.8), Color _titleTextC = Color(0, 1, 0), Color _subTitleTextC = Color(1, 1, 0), Color _textboxC = Color(0.23, 0.17, 0.91), Color _textboxTextC = Color(0.978, 0.849, 0.9055), Coord_Rect _backButtonD = Coord_Rect(7, 8, 2, 1), Coord_Rect _openBookButtonD = Coord_Rect(7, -9, 3, 1.1), float _bookNamePosX = -4, float _bookNamePosY = 6, float _descriptionX = -8, float _descriptionY = 4, float _featureButtonX = 6.0, float _featureButtonY = 5, Button _tempButton = Button("", Color(0, 0, 0), Color(0, 0, 0), Coord_Rect(0, 0, 0, 0)), TextBox _tempTextBox = TextBox(Coord_Rect(0,0,0,0),Color(0,0,0),Color(0,0,0))) : navButtonC(_navButtonC), featureButtonC(_featureButtonC), titleTextC(_titleTextC), subTitleTextC(_subTitleTextC), textboxC(_textboxC), textboxTextC(_textboxTextC), backButtonD(_backButtonD), openBookButtonD(_openBookButtonD), backButton(_tempButton), openBookButton(_tempButton), readingButton(_tempButton), completedButton(_tempButton), sharedButton(_tempButton), favouriteButton(_tempButton), reviewButton(_tempButton), bookmarkButton(_tempButton),reviewNum(_tempTextBox),shareUser(_tempTextBox),bookmarkText(_tempTextBox)
    {
        mode = _mode;
        bookname = _bookname;
        bookNamePosX = _bookNamePosX;
        bookNamePosY = _bookNamePosY;
        descriptionX = _descriptionX;
        descriptionY = _descriptionY;
        featureButtonX = _featureButtonX;
        featureButtonY = _featureButtonY;
        backButton =  Button("Back", navButtonC, titleTextC, backButtonD,CHAR_WIDTH*1.2,CHAR_WIDTH*1.2);
        openBookButton = Button("OPEN BOOK", navButtonC, titleTextC, openBookButtonD, CHAR_WIDTH , CHAR_WIDTH);
        openBookButton.setFont(GLUT_BITMAP_9_BY_15);
        setDescription();
        setButtonAndTextBox();
        f1 = GLUT_BITMAP_HELVETICA_18;
        f2 = GLUT_BITMAP_HELVETICA_12;
    }
    void setDescription();
    void setButtonAndTextBox();
    void showBookDescription();
    void render();
    void mouseHandler(int button, int state, int x, int y);
    void keyboardHandler(unsigned char key, int x, int y);
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
    void changeMode(char _mode)
    {
        mode = _mode;
        setButtonAndTextBox();
    }
    void changeName(std::string _name)
    {
        bookname = _name;
    }
    std::string getText(TextBox * _box)
    {
        return _box->getText();
    }
    void setText(TextBox * _box,std::string _text)
    {
        _box->setText(_text);
    }
    bool buttonPressed(Button* _button)
    {
        if (_button->isActive())
            return true;
        return false;
    }
};
void BookDetail::setDescription()
{
    bookDes.push_back(bookname);
    bookDes.push_back("AName");
    bookDes.push_back("Genre");
    bookDes.push_back("Date");
    bookDes.push_back("ExtraDes");
    bookDes.push_back("Review");
    bookDes.push_back("BookMark");
}
void BookDetail::setButtonAndTextBox()
{
    if (mode == 'R')
    {
        completedButton = Button("Add to read", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 2, CHAR_WIDTH);
        favouriteButton = Button("Add to favourite", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 2.2, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        bookmarkButton = Button("Add bookmark", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 3.4, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        sharedButton = Button("Share", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 4.6, 3, 1.0), 1.1, CHAR_WIDTH);
        bookmarkText = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-3.4,2.9,1.1),textboxC,textboxTextC);
        shareUser = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-4.6,2.9,1.1),textboxC,textboxTextC);
        bookmarkText.setPadding(0.25);
        shareUser.setPadding(0.25);
    }
    else if (mode == 'C')
    {
        favouriteButton = Button("Add to favourite", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        bookmarkButton = Button("Add bookmark", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 2.2, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        reviewButton = Button("Review", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 3.4, 3, 1), CHAR_WIDTH * 2, CHAR_WIDTH);
        sharedButton = Button("Share", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 4.6, 3, 1.0), 1.1, CHAR_WIDTH);
        bookmarkText = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-2.2,2.9,1.1),textboxC,textboxTextC);
        reviewNum = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-3.4,1.5,1.1),textboxC,textboxTextC);
        shareUser = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-4.6,2.9,1.1),textboxC,textboxTextC);
        bookmarkText.setPadding(0.25);
        shareUser.setPadding(0.25);
        reviewNum.setPadding(0.23);
    }
    else if (mode == 'F')
    {
         readingButton = Button("Add to reading", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 1, CHAR_WIDTH);
         reviewButton = Button("Review", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 2.2, 3, 1), CHAR_WIDTH * 2, CHAR_WIDTH);
         sharedButton = Button("Share", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 3.4, 3, 1.0), 1.1, CHAR_WIDTH);
         reviewNum = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-2.2,1.5,1.1),textboxC,textboxTextC);
         shareUser = TextBox(Coord_Rect(featureButtonX-3,featureButtonY-3.4,2.9,1.1),textboxC,textboxTextC);
         shareUser.setPadding(0.25);
         reviewNum.setPadding(0.23);
    }
    else if (mode == 'S')
    {
        readingButton = Button("Add to reading", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 1, CHAR_WIDTH);
    }
}
void BookDetail::showBookDescription()
{
    printText(bookNamePosX, bookNamePosY, titleTextC, bookDes[0], f1);
    printText(bookNamePosX + 7, bookNamePosY, titleTextC, "Rating: ", f1);
    printText(descriptionX, descriptionY, titleTextC, "Author Name:", f1);
    printText(descriptionX, descriptionY - 1.5, titleTextC, "Genre:", f1);
    printText(descriptionX, descriptionY - 3, titleTextC, "Published date:", f1);
    printText(descriptionX, descriptionY - 4.5, titleTextC, "Description:", f1);
    printText(descriptionX, descriptionY - 11, titleTextC, "Bookmark", f1);
    printText(descriptionX + 5, descriptionY, subTitleTextC, bookDes[1], f2);
    printText(descriptionX + 5, descriptionY - 1.5, subTitleTextC, bookDes[2], f2);
    printText(descriptionX + 5, descriptionY - 3, subTitleTextC, bookDes[3], f2);
    printText(descriptionX + 5, descriptionY - 4.5, subTitleTextC, bookDes[4], f2);
    printText(descriptionX + 5, descriptionY - 11, subTitleTextC, bookDes[6], f2);
    textboxC.applyColor();
    glDrawP(Coord_Rect(descriptionX, descriptionY - 9.7, 13, 5));
    printText(bookNamePosX + 10, bookNamePosY, subTitleTextC, bookDes[5], f1);
}
void BookDetail::render()
{
    showBookDescription();
    backButton.render();
    openBookButton.render();
    if (mode == 'R')
    {
        completedButton.render();
        favouriteButton.render();
        bookmarkButton.render();
        sharedButton.render();
        bookmarkText.render();
        shareUser.render();
    }
    else if (mode == 'C')
    {
        reviewButton.render();
        favouriteButton.render();
        bookmarkButton.render();
        sharedButton.render();
        bookmarkText.render();
        shareUser.render();
        reviewNum.render();
        printText(featureButtonX-1.1,featureButtonY-3,titleTextC,"[0-5]",f2);
    }
    else if (mode == 'F')
    {
        readingButton.render();
        reviewButton.render();
        sharedButton.render();
        shareUser.render();
        reviewNum.render();
        printText(featureButtonX-1.1,featureButtonY-1.8,titleTextC,"[0-5]",f2);
    }
    else if (mode == 'S')
    {
        readingButton.render();
    }
}
void BookDetail::mouseHandler(int button, int state, int x, int y)
{
    openBookButton.mouseHandler(button,state,x,y);
    backButton.mouseHandler(button,state,x,y);
    if (mode == 'R')
    {
        completedButton.mouseHandler(button, state, x, y);
        favouriteButton.mouseHandler(button, state, x, y);
        bookmarkButton.mouseHandler(button, state, x, y);
        sharedButton.mouseHandler(button, state, x, y);
        bookmarkText.mouseHandler(button, state, x, y);
        shareUser.mouseHandler(button, state, x, y);
    }
    else if (mode == 'C')
    {
        reviewButton.mouseHandler(button, state, x, y);
        favouriteButton.mouseHandler(button, state, x, y);
        bookmarkButton.mouseHandler(button, state, x, y);
        sharedButton.mouseHandler(button, state, x, y);
        bookmarkText.mouseHandler(button, state, x, y);
        shareUser.mouseHandler(button, state, x, y);
        reviewNum.mouseHandler(button, state, x, y);
    }
    else if (mode == 'F')
    {
        readingButton.mouseHandler(button, state, x, y);
        reviewButton.mouseHandler(button, state, x, y);
        sharedButton.mouseHandler(button, state, x, y);
        shareUser.mouseHandler(button, state, x, y);
        reviewNum.mouseHandler(button, state, x, y);
    }
    else if (mode == 'S')
    {
        readingButton.mouseHandler(button, state, x, y);
    }
}
void BookDetail::keyboardHandler(unsigned char key, int x, int y)
{
    backButton.keyboardHandler(key,x,y);
    openBookButton.keyboardHandler(key,x,y);
    if (mode == 'R')
    {
        bookmarkText.keyboardHandler(key,x,y);
        shareUser.keyboardHandler(key,x,y);
    }
    else if (mode == 'C')
    {
        bookmarkText.keyboardHandler(key,x,y);
        shareUser.keyboardHandler(key,x,y);
        reviewNum.keyboardHandler(key,x,y);
    }
    else if (mode == 'F')
    {
        shareUser.keyboardHandler(key,x,y);
        reviewNum.keyboardHandler(key,x,y);
    }
}
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
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class rectBox : public GUIcomponent
{
    Coord_Rect dimension;
    Color color;

public:
    rectBox(Coord_Rect _dim, Color _color = Color(0, 0, 0)) : dimension(_dim), color(_color) {}
    void render()
    {
        color.applyColor();
        glDrawP(dimension);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
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
    void setActiveScrollBox(ScrollBox *_sb, bool _value)
    {
        _sb->setActive(_value);
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
    void setData(ScrollBox *sb, std::vector<std::string> data)
    {
        sb->setData(data);
    }
    std::string getButtonText(int button, int state, int x, int y, ScrollBox *sb)
    {
        return sb->getButtonText(button, state, x, y);
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
    void mouseMotionHandler(int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseMotionHandler(x, y);
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
    bool buttonPressed(BookDetail * _bd,Button *_button)
    {
        return _bd->buttonPressed(_button);
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
    void setText(BookDetail* _bd,TextBox * _box,std::string _text)
    {
        _bd->setText(_box,_text);
    }
    void setData(ScrollBox *sb, std::vector<std::string> data)
    {
        sb->setData(data);
    }
    std::string getText(BookDetail* _bd,TextBox * _box)
    {
        return _bd->getText(_box);
    }
    std::string getButtonText(int button, int state, int x, int y, ScrollBox *sb)
    {
        return sb->getButtonText(button, state, x, y);
    }
    void changeBookName(BookDetail * bd,std::string _name)
    {
        bd->changeName(_name);
    }
    void changeMode(BookDetail* bd,char _mode)
    {
        bd->changeMode(_mode);
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
    void mouseMotionHandler(int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseMotionHandler(x, y);
    }
};
