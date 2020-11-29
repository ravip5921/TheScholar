#include "./vars.h"
#include "./GUICompClass.h"
#include "./FileReader.h"
#include "./GUIPages.h"
#include "./ErrorWindow.h"
#include "./GUIBlocks.h"

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void mouseMotion(int x, int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);
void createErrorWindow(const char *);
void setFonts();
void showClock();
void getSearchResults();
int windowWidth();
int windowHeight();

//For pages
GUIPage loginPage;
GUIPage signupPage;
GUIPage welcomePage;
GUIPage homePage;
GUIPage bookDetailPage;
GUIPage searchingPage;

/*** Navigate Pages ****/
int PAGE = 0;
enum
{
    WELCOME_P = 0,
    LOGIN_P = 1,
    SIGNUP_P = 2,
    HOME_P = 3,
    BOOK_DETAIL_P = 4,
    SEARCH_P =5
};

std::vector<GUIPage *> activePage = {&welcomePage, &loginPage, &signupPage, &homePage, &bookDetailPage, &searchingPage};
//end of page navigator

//for blocks
GUIBlock readingB;
GUIBlock completedB;
GUIBlock favouriteB;
GUIBlock shareB;

/**** Navigate Blocks in HOME_PAGE *****/
int BLOCK = 0;
enum
{
    READING_MP = 0,
    COMPLETED_MP = 1,
    FAVOURITE_MP = 2,
    SHARED_MP = 3
};
std::vector<GUIBlock *> activeBlock = {&readingB, &completedB, &favouriteB, &shareB};
//end blocks

void callBackFun()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0, 1, 0);
    WID = windowWidth();
    HEI = windowHeight();
    setFonts();

    activePage[PAGE]->render();
    if (PAGE == HOME_P)
    {
        activeBlock[BLOCK]->render();
    }

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
            activePage[LOGIN_P]->setActiveBox(&SignUp::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&welcome::loginButton))
        {
            PAGE = LOGIN_P;
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&welcome::exitButton))
            exit(EXIT_SUCCESS);
    }
    else if (PAGE == LOGIN_P)
    {
        if (activePage[PAGE]->buttonPressed(&LogIn::logInButton))
        {
            userName = activePage[PAGE]->getText(&LogIn::userNameB);
            password = activePage[PAGE]->getText(&LogIn::passwordB);
            std::cout << "\nUser = " << userName << "\nPass = " << password << "\n";
            logIn LogInObject(userName, password);

            if (LogInObject.IsLogedIn())
            {
                PAGE = HOME_P;
                activePage[HOME_P]->setText(&Home::User, &userName);

                FileReader fr(userName);
                //reading scroll box
                dataf = fr.Reader(READING_MP + 1);
                activeBlock[BLOCK]->setData(&readingN::BookListReading, dataf);

                //completed scroll box
                dataf = fr.Reader(COMPLETED_MP + 1);
                activeBlock[BLOCK]->setData(&completedN::BookListCompleted, dataf);

                //favourite scroll box
                dataf = fr.Reader(FAVOURITE_MP + 1);
                activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite, dataf);

                //share scroll box
                dataf = fr.Reader(SHARED_MP + 1);
                activeBlock[BLOCK]->setData(&sharedN::BookListShare, dataf);
            }
            else
            {
                createErrorWindow("User name or password incorrect!");
            }
        }
        else if (activePage[PAGE]->buttonPressed(&LogIn::toSignup))
        {
            PAGE = SIGNUP_P;
            activePage[LOGIN_P]->setActiveBox(&SignUp::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&LogIn::exitButton))
            exit(EXIT_SUCCESS);
    }
    else if (PAGE == SIGNUP_P)
    {
        if (activePage[PAGE]->buttonPressed(&SignUp::signUpButton))
        {
            userNameN = activePage[PAGE]->getText(&SignUp::userNameB);
            passwordN = activePage[PAGE]->getText(&SignUp::passwordB);
            std::cout << "\nUser = " << userNameN << "\nPass = " << passwordN << "\n";
            if (userNameN == "" || passwordN == "")
            {
                createErrorWindow("UserName and Password required!");
            }
            else
            {
                signUp SignUpObject(userNameN, passwordN);
                if (!SignUpObject.valid())
                {
                    createErrorWindow("Password must contain at least a digit, an alphabet and a special character.");
                }
                else if (SignUpObject.userExists())
                {
                    createErrorWindow("User already exists. Try Logging In.");
                }
                else
                {
                    SignUpObject.signup();
                    userName = userNameN;
                    password = passwordN;
                    activePage[HOME_P]->setText(&Home::User, &userNameN);
                    PAGE = HOME_P;

                    FileReader fr(userNameN);
                    //reading scroll box
                    dataf = fr.Reader(READING_MP + 1);
                    activeBlock[BLOCK]->setData(&readingN::BookListReading, dataf);

                    //completed scroll box
                    dataf = fr.Reader(COMPLETED_MP + 1);
                    activeBlock[BLOCK]->setData(&completedN::BookListCompleted, dataf);

                    //favourite scroll box
                    dataf = fr.Reader(FAVOURITE_MP + 1);
                    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite, dataf);

                    //share scroll box
                    dataf = fr.Reader(SHARED_MP + 1);
                    activeBlock[BLOCK]->setData(&sharedN::BookListShare, dataf);
                }
            }
        }
        else if (activePage[PAGE]->buttonPressed(&SignUp::toLogin))
        {
            PAGE = LOGIN_P;
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&SignUp::exitButton))
            exit(EXIT_SUCCESS);
    }
    else if (PAGE == HOME_P)
    {
        activeBlock[BLOCK]->mouseHandler(button, state, x, y);
        activeBlock[BLOCK]->mouseMotionHandler(x, y);
        if (activePage[PAGE]->buttonPressed(&Home::logoutButton))
        {
            PAGE = LOGIN_P;
            userName = "";
            password = "";
            activePage[LOGIN_P]->setText(&LogIn::userNameB, &userName);
            activePage[LOGIN_P]->setText(&LogIn::passwordB, &userName);
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
            activePage[LOGIN_P]->setActiveBox(&LogIn::passwordB, false);
            activePage[SIGNUP_P]->setText(&SignUp::userNameB, &userName);
            activePage[SIGNUP_P]->setText(&SignUp::passwordB, &userName);
            activePage[SIGNUP_P]->setActiveBox(&SignUp::userNameB);
            activePage[SIGNUP_P]->setActiveBox(&SignUp::passwordB, false);
        }
        else if (activePage[PAGE]->buttonPressed(&Home::readingButton))
        {
            BLOCK = READING_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, true);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
        }
        else if (activePage[PAGE]->buttonPressed(&Home::completedButton))
        {
            BLOCK = COMPLETED_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, true);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
        }
        else if (activePage[PAGE]->buttonPressed(&Home::favouriteButton))
        {
            BLOCK = FAVOURITE_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, true);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
        }
        else if (activePage[PAGE]->buttonPressed(&Home::sharedButton))
        {
            BLOCK = SHARED_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, true);
        }
        //trial for book detail page
        else if (activePage[PAGE]->buttonPressed(&Home::bookButton))
        {
            PAGE = BOOK_DETAIL_P;
        }
        else if (activePage[PAGE]->buttonPressed(&Home::searchButton))
        {
            PAGE = SEARCH_P;
            //getSearchResults();
        }

        else if (activeBlock[BLOCK]->buttonPressed(&readingN::refreshButton))
        {
            readingN::BookListReading.refreshBox();
        }

        else if (activeBlock[BLOCK]->buttonPressed(&completedN::refreshButton))
        {
            completedN::BookListCompleted.refreshBox();
        }

        else if (activeBlock[BLOCK]->buttonPressed(&favouriteN::refreshButton))
        {
            favouriteN::BookListFavourite.refreshBox();
        }

        else if (activeBlock[BLOCK]->buttonPressed(&sharedN::refreshButton))
        {
            sharedN::BookListShare.refreshBox();
        }
        std::cout << activeBlock[BLOCK]->getButtonText(button, state, x, y, &readingN::BookListReading);
        std::cout << activeBlock[BLOCK]->getButtonText(button, state, x, y, &completedN::BookListCompleted);
        std::cout << activeBlock[BLOCK]->getButtonText(button, state, x, y, &sharedN::BookListShare);
        std::cout << activeBlock[BLOCK]->getButtonText(button, state, x, y, &favouriteN::BookListFavourite);
    }
    else if (PAGE == BOOK_DETAIL_P)
    {
        if (activePage[PAGE]->buttonPressed(&BookDetail::backButton))
        {
            PAGE = HOME_P;
        }
        else if (activePage[PAGE]->buttonPressed(&BookDetail::readingButton))
        {
            FileWriter fw(userName);
            fw.Writer(1, "reading Book");
        }
        else if (activePage[PAGE]->buttonPressed(&BookDetail::completedButton))
        {
            FileWriter fw(userName);
            fw.Writer(2, "read Book");
        }
        else if (activePage[PAGE]->buttonPressed(&BookDetail::favouriteButton))
        {
            FileWriter fw(userName);
            fw.Writer(3, "favourite Book");
        }
        else if (activePage[PAGE]->buttonPressed(&BookDetail::sharedButton))
        {
            FileWriter fw(userName);
            fw.Writer(4, "shared Book");
        }
    }
    else if(PAGE == SEARCH_P){
        if(activePage[PAGE]->buttonPressed(&SearchN::backButton)){
            PAGE = HOME_P;
        }
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
                std::cout << "\nUser = " << userName << "\nPass = " << password << "\n";
                logIn LogInObject(userName, password);

                if (LogInObject.IsLogedIn())
                {
                    PAGE = HOME_P;
                    activePage[HOME_P]->setText(&Home::User, &userName);

                    FileReader fr(userName);
                    //reading scroll box
                    dataf = fr.Reader(READING_MP + 1);
                    activeBlock[BLOCK]->setData(&readingN::BookListReading, dataf);

                    //completed scroll box
                    dataf = fr.Reader(COMPLETED_MP + 1);
                    activeBlock[BLOCK]->setData(&completedN::BookListCompleted, dataf);

                    //favourite scroll box
                    dataf = fr.Reader(FAVOURITE_MP + 1);
                    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite, dataf);

                    //share scroll box
                    dataf = fr.Reader(SHARED_MP + 1);
                    activeBlock[BLOCK]->setData(&sharedN::BookListShare, dataf);
                }
                else
                {
                    createErrorWindow("User name or password incorrect!");
                }
            }
        }
    }
    else if (PAGE == SIGNUP_P)
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
                std::cout << "\nUser = " << userNameN << "\nPass = " << passwordN << "\n";
                if (userNameN == "" || passwordN == "")
                {
                    createErrorWindow("UserName and Password required!");
                }
                else
                {
                    signUp SignUpObject(userNameN, passwordN);
                    if (!SignUpObject.valid())
                    {
                        createErrorWindow("Password must contain at least a digit, an alphabet and a special character.");
                    }
                    else if (SignUpObject.userExists())
                    {
                        createErrorWindow("User already exists. Try Logging In.");
                    }
                    else
                    {
                        SignUpObject.signup();
                        userName = userNameN;
                        password = passwordN;
                        activePage[HOME_P]->setText(&Home::User, &userNameN);
                        PAGE = HOME_P;

                        FileReader fr(userNameN);
                        //reading scroll box
                        dataf = fr.Reader(READING_MP + 1);
                        activeBlock[BLOCK]->setData(&readingN::BookListReading, dataf);

                        //completed scroll box
                        dataf = fr.Reader(COMPLETED_MP + 1);
                        activeBlock[BLOCK]->setData(&completedN::BookListCompleted, dataf);

                        //favourite scroll box
                        dataf = fr.Reader(FAVOURITE_MP + 1);
                        activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite, dataf);

                        //share scroll box
                        dataf = fr.Reader(SHARED_MP + 1);
                        activeBlock[BLOCK]->setData(&sharedN::BookListShare, dataf);
                    }
                }
            }
        }
    }
    else if (PAGE == SEARCH_P)
    {
        if (key == ENTER_KEY || key == TAB_KEY)
        {
            if (activePage[PAGE]->isActiveBox(&SearchN::SNameB))
            {
                activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, true);
                activePage[PAGE]->setActiveBox(&SearchN::SNameB, false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SAuthorB))
            {
                activePage[PAGE]->setActiveBox(&SearchN::SGenreB, true);
                activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SGenreB))
            {
                activePage[PAGE]->setActiveBox(&SearchN::SDateB, true);
                activePage[PAGE]->setActiveBox(&SearchN::SGenreB, false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SDateB) && key == ENTER_KEY)
            {
                getSearchResults();
            }
        }
    }
}
void mouseMotion(int x, int y)
{
    activeBlock[BLOCK]->mouseMotionHandler(x, y);
    std::cout << "x= " << x << " y= " << y << '\n';
}
void createErrorWindow(const char *err)
{
    if (ErrorWindow::canMake)
        ErrorWindow::create(err, glutGet(GLUT_WINDOW_X) + 150, glutGet(GLUT_WINDOW_Y) + 200);
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
    glLoadIdentity();             //resets the matrix transformation done is previous options(i.e.,make default coordinate points)
    glClearColor(WC_R, WC_G, WC_B, WC_A);
    Showtime s1(-9, 1.5, 1, 1, 1);
    s1.displayClock(GLUT_BITMAP_TIMES_ROMAN_24);
    s1.displayCalendar(-5, -2.5, GLUT_BITMAP_HELVETICA_18);
    glutPostRedisplay();
    glutSwapBuffers();
}
void getSearchResults()
{
    std::cout << activePage[PAGE]->getText(&SearchN::SNameB) << std::endl;
    std::cout << activePage[PAGE]->getText(&SearchN::SAuthorB) << std::endl;
    std::cout << activePage[PAGE]->getText(&SearchN::SGenreB) << std::endl;
   std::cout << activePage[PAGE]->getText(&SearchN::SDateB) << std::endl;
    activePage[PAGE]->setText(&SearchN::SNameB, "");
    activePage[PAGE]->setText(&SearchN::SAuthorB, "");
    activePage[PAGE]->setText(&SearchN::SGenreB, "");
    activePage[PAGE]->setText(&SearchN::SDateB, "");
    activePage[PAGE]->setActiveBox(&SearchN::SNameB, true);
    activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SGenreB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SDateB, false);
}
