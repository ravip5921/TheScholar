#include "./vars.h"
#include "./GUICompClass.h"
#include "./FileHandler.h"
#include "./GUIPages.h"
#include "./ErrorWindow.h"
#include "./GUIBlocks.h"
#include "DatabaseSearch.h"
#include "RelavantOptions.h"
//#include "./Events.h"

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
    SEARCH_P = 5
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

namespace USERS_BOOKS
{
    std::vector<DATABASE_SEARCH::BookDescriptor> reading;
    std::vector<std::string> reading_name;
    std::vector<std::string> reading_bookmark;
    std::vector<DATABASE_SEARCH::BookDescriptor> completed;
    std::vector<std::string> completed_name;
    std::vector<std::string> completed_bookmark;
    std::vector<DATABASE_SEARCH::BookDescriptor> favourite;
    std::vector<std::string> favourite_name;
    std::vector<DATABASE_SEARCH::BookDescriptor> shared;
    std::vector<std::string> share_name;
    std::vector<std::string> shared_bookmark;

    void clearAll()
    {
        reading_name.clear();
        completed_name.clear();
        reading_bookmark.clear();
        reading.clear();
        completed_bookmark.clear();
        completed_name.clear();
        completed.clear();
        shared.clear();
        shared_bookmark.clear();
        share_name.clear();
        favourite_name.clear();
        favourite.clear();
    }
} // namespace USERS_BOOKS

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
                USERS_BOOKS::clearAll();
                FileReader fr(userName);
                //reading scroll box
                    dataf = fr.Reader(READING_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdReading;
                    int i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdReading.path =*it;
                            bdReading.readFromFile();
                            USERS_BOOKS::reading.push_back(bdReading);
                            USERS_BOOKS::reading_name.push_back(bdReading.name);
                        }
                        else{
                            USERS_BOOKS::reading_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&readingN::BookListReading,USERS_BOOKS::reading_name);
                    dataf.clear();
                //completed scroll box
                    dataf = fr.Reader(COMPLETED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdCompleted;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdCompleted.path= *it;
                            bdCompleted.readFromFile();
                            USERS_BOOKS::completed.push_back(bdCompleted);
                            USERS_BOOKS::completed_name.push_back(bdCompleted.name);
                        }
                        else{
                            USERS_BOOKS::completed_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&completedN::BookListCompleted,USERS_BOOKS::completed_name);
                    dataf.clear();
                //favourite scroll box
                    dataf = fr.Reader(FAVOURITE_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdFavourite;
                    for(auto it:dataf){
                        bdFavourite.path= it;
                        bdFavourite.readFromFile();
                        USERS_BOOKS::favourite.push_back(bdFavourite);
                        USERS_BOOKS::favourite_name.push_back(bdFavourite.name);

                    }
                    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite,USERS_BOOKS::favourite_name);
                    dataf.clear();
                //share scroll box
                    dataf = fr.Reader(SHARED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdShare;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdShare.path= *it;
                            bdShare.readFromFile();
                            USERS_BOOKS::shared.push_back(bdShare);
                            USERS_BOOKS::share_name.push_back(bdShare.name);
                        }
                        else{
                            USERS_BOOKS::shared_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&sharedN::BookListShare,USERS_BOOKS::share_name);
                    dataf.clear();
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
                    USERS_BOOKS::clearAll();
                    FileReader fr(userName);
                //reading scroll box
                    dataf = fr.Reader(READING_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdReading;
                    int i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdReading.path =*it;
                            bdReading.readFromFile();
                            USERS_BOOKS::reading.push_back(bdReading);
                            USERS_BOOKS::reading_name.push_back(bdReading.name);
                        }
                        else{
                            USERS_BOOKS::reading_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&readingN::BookListReading,USERS_BOOKS::reading_name);
                    dataf.clear();
                //completed scroll box
                    dataf = fr.Reader(COMPLETED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdCompleted;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdCompleted.path= *it;
                            bdCompleted.readFromFile();
                            USERS_BOOKS::completed.push_back(bdCompleted);
                            USERS_BOOKS::completed_name.push_back(bdCompleted.name);
                        }
                        else{
                            USERS_BOOKS::completed_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&completedN::BookListCompleted,USERS_BOOKS::completed_name);
                    dataf.clear();
                //favourite scroll box
                    dataf = fr.Reader(FAVOURITE_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdFavourite;
                    for(auto it:dataf){
                        bdFavourite.path= it;
                        bdFavourite.readFromFile();
                        USERS_BOOKS::favourite.push_back(bdFavourite);
                        USERS_BOOKS::favourite_name.push_back(bdFavourite.name);

                    }
                    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite,USERS_BOOKS::favourite_name);
                    dataf.clear();
                //share scroll box
                    dataf = fr.Reader(SHARED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdShare;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdShare.path= *it;
                            bdShare.readFromFile();
                            USERS_BOOKS::shared.push_back(bdShare);
                            USERS_BOOKS::share_name.push_back(bdShare.name);
                        }
                        else{
                            USERS_BOOKS::shared_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&sharedN::BookListShare,USERS_BOOKS::share_name);
                    dataf.clear();
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
            BLOCK = READING_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, true);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BLOCK = READING_MP;
            BookDetails::page.changeMode('R');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::readingButton))
        {
            BLOCK = READING_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, true);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('R');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::completedButton))
        {
            BLOCK = COMPLETED_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, true);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('C');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::favouriteButton))
        {
            BLOCK = FAVOURITE_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, true);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('F');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::sharedButton))
        {
            BLOCK = SHARED_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, true);
            BookDetails::page.changeMode('S');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::searchButton))
        {
            PREV_PAGE = SEARCH_P;
            PAGE = SEARCH_P;
        }
        if (activeBlock[BLOCK]->buttonPressed(button, state, x, y, &readingN::BookListReading))
        {
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &readingN::BookListReading);
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &readingN::BookListReading);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
        else if (activeBlock[COMPLETED_MP]->buttonPressed(button, state, x, y, &completedN::BookListCompleted))
        {
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &completedN::BookListCompleted);
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &completedN::BookListCompleted);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
        else if (activeBlock[BLOCK]->buttonPressed(button, state, x, y, &favouriteN::BookListFavourite))
        {
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &favouriteN::BookListFavourite);
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &favouriteN::BookListFavourite);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
        else if (activeBlock[BLOCK]->buttonPressed(button, state, x, y, &sharedN::BookListShare))
        {
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &sharedN::BookListShare);
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &sharedN::BookListShare);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
        activePage[BOOK_DETAIL_P]->setDetails(&BookDetails::page, bookNameSB);
    }
    else if (PAGE == BOOK_DETAIL_P)
    {
        if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.backButton))
        {
            PAGE = PREV_PAGE;
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.reviewButton))
        {
            reviewT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.reviewNum);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.reviewNum, "");
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.sharedButton))
        {
            shareT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.shareUser);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.shareUser, "");
            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
            //write in share of another user
            FileWriter shareWriter(shareT);
            if (!shareWriter.UserExists())
            {
                createErrorWindow("User does not exist");
            }
            else
            {
                shareWriter.Writer(4, bookNameSB,bookmarkT);
            }
            std::cout << bookmarkT << " " << reviewT << " " << shareT << "\n";
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.readingButton) && (BookDetails::page.getMode() == 'S'))
        {
            std::cout << "Reading Button Pressed. in share";
            FileWriter fw(userName);
            fw.Writer(1, bookNameSB);
            fw.maskBookName(bookNameIndex, 'S');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.readingButton) && (BookDetails::page.getMode() == 'F'))
        {
            std::cout << "Reading Button Pressed in fav";
            FileWriter fw(userName);
            fw.Writer(1, bookNameSB);
            fw.maskBookName(bookNameIndex, 'F');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.favouriteButton) && (BookDetails::page.getMode() == 'C'))
        {
            std::cout << "Fav Button Pressed in completed";
            FileWriter fw(userName);
            fw.Writer(3, bookNameSB);
            fw.maskBookName(bookNameIndex, 'C');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.bookmarkButton) && (BookDetails::page.getMode() == 'C'))
        {

            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
            std::cout << "bookmark in completed";
            FileWriter fw(userName);
            fw.updateBookmark(bookNameIndex, 'C', bookNameSB, bookmarkT);
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.completedButton) && (BookDetails::page.getMode() == 'R'))
        {
            std::cout << "Read Button Pressed in reading";
            FileWriter fw(userName);
            fw.Writer(2, bookNameSB);
            fw.maskBookName(bookNameIndex, 'R');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.favouriteButton) && (BookDetails::page.getMode() == 'R'))
        {
            std::cout << "Fav Button Pressed in reading";
            FileWriter fw(userName);
            fw.Writer(3, bookNameSB);
            fw.maskBookName(bookNameIndex, 'R');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.bookmarkButton) && (BookDetails::page.getMode() == 'R'))
        {

            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
            std::cout << "bookmark in reading";
            FileWriter fw(userName);
            fw.updateBookmark(bookNameIndex, 'R', bookNameSB, bookmarkT);
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.openBookButton))
        {
            std::cout << "Open Book button pressed.\n";
            //removeBook();
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.removeButton))
        {
            std::cout << "Remove button pressed.\n";
            FileWriter fw(userName);
            fw.maskBookName(bookNameIndex, BookDetails::page.getMode());
        }
    }
    else if (PAGE == SEARCH_P)
    {
        if (activePage[PAGE]->buttonPressed(&SearchN::backButton))
        {
            PAGE = HOME_P;
        }
        else if (activePage[PAGE]->buttonPressed(&SearchN::searchButton))
        {
            getSearchResults();
        }
        else if (activePage[SEARCH_P]->buttonPressed(button, state, x, y, &SearchN::searchResultList))
        {
            int bindex = activePage[PAGE]->getButtonIndex(button, state, x, y, &SearchN::searchResultList);
            std::cout << bindex;
            BookDetails::page.setDescription(DATABASE_SEARCH::bdlist[bindex], "page 1");
            PAGE = BOOK_DETAIL_P;
            BookDetails::page.changeMode('O');
            /**********************************************************************************************************/
        }
        else if (activePage[SEARCH_P]->buttonPressed(button, state, x, y, &SearchN::relevantOptionsList))
        {
            std::string bText = activePage[PAGE]->getButtonText(button, state, x, y, &SearchN::relevantOptionsList);
            std::cout << bText;
            if (activePage[PAGE]->isActiveBox(&SearchN::SNameB))
            {
                SearchN::SNameB.setText(bText);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SAuthorB))
            {
                SearchN::SAuthorB.setText(bText);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SGenreB))
            {
                SearchN::SGenreB.setText(bText);
            }
            /**********************************************************************************************************/
        }
        else if (activePage[PAGE]->buttonPressed(&SearchN::nextButton))
        {
            SearchN::searchIndex++;
            std::cout << SearchN::searchIndex;
            SearchN::prevButton.show(true);
        }
        else if (activePage[PAGE]->buttonPressed(&SearchN::prevButton))
        {
            SearchN::searchIndex--;
            std::cout << SearchN::searchIndex;
            if (SearchN::searchIndex == 0)
            {
                SearchN::prevButton.show(false);
            }
        }
        else if (SearchN::bookCB.isActive())
        {
            //std::cout<<"\n1111";
            if (article_flag == 1)
            {
                article_flag = 0;
                DATABASE_SEARCH::SEARCH_DIRS::setDirsForBook();
                std::cout << "\nbookCB";
            }
        }
        else if (SearchN::articleCB.isActive())
        {
            if (article_flag == 0)
            {
                article_flag = 1;
                DATABASE_SEARCH::SEARCH_DIRS::setDirsForArticle();
                std::cout << "\narticleCB";
            }
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

                    USERS_BOOKS::clearAll();
                    FileReader fr(userName);
                //reading scroll box
                    dataf = fr.Reader(READING_MP + 1);

                    DATABASE_SEARCH::BookDescriptor bdReading;
                    int i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdReading.path =*it;
                            bdReading.readFromFile();
                            USERS_BOOKS::reading.push_back(bdReading);
                            USERS_BOOKS::reading_name.push_back(bdReading.name);
                        }
                        else{
                            USERS_BOOKS::reading_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&readingN::BookListReading,USERS_BOOKS::reading_name);
                    dataf.clear();
                //completed scroll box
                    dataf = fr.Reader(COMPLETED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdCompleted;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdCompleted.path= *it;
                            bdCompleted.readFromFile();
                            USERS_BOOKS::completed.push_back(bdCompleted);
                            USERS_BOOKS::completed_name.push_back(bdCompleted.name);
                        }
                        else{
                            USERS_BOOKS::completed_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&completedN::BookListCompleted,USERS_BOOKS::completed_name);
                    dataf.clear();
                //favourite scroll box
                    dataf = fr.Reader(FAVOURITE_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdFavourite;
                    for(auto it:dataf){
                        bdFavourite.path= it;
                        bdFavourite.readFromFile();
                        USERS_BOOKS::favourite.push_back(bdFavourite);
                        USERS_BOOKS::favourite_name.push_back(bdFavourite.name);

                    }
                    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite,USERS_BOOKS::favourite_name);
                    dataf.clear();
                //share scroll box
                    dataf = fr.Reader(SHARED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdShare;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdShare.path= *it;
                            bdShare.readFromFile();
                            USERS_BOOKS::shared.push_back(bdShare);
                            USERS_BOOKS::share_name.push_back(bdShare.name);
                        }
                        else{
                            USERS_BOOKS::shared_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&sharedN::BookListShare,USERS_BOOKS::share_name);
                    dataf.clear();
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
                        USERS_BOOKS::clearAll();
                        FileReader fr(userName);
                //reading scroll box
                    dataf = fr.Reader(READING_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdReading;
                    int i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdReading.path =*it;
                            bdReading.readFromFile();
                            USERS_BOOKS::reading.push_back(bdReading);
                            USERS_BOOKS::reading_name.push_back(bdReading.name);
                        }
                        else{
                            USERS_BOOKS::reading_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&readingN::BookListReading,USERS_BOOKS::reading_name);
                    dataf.clear();
                //completed scroll box
                    dataf = fr.Reader(COMPLETED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdCompleted;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdCompleted.path= *it;
                            bdCompleted.readFromFile();
                            USERS_BOOKS::completed.push_back(bdCompleted);
                            USERS_BOOKS::completed_name.push_back(bdCompleted.name);
                        }
                        else{
                            USERS_BOOKS::completed_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&completedN::BookListCompleted,USERS_BOOKS::completed_name);
                    dataf.clear();
                //favourite scroll box
                    dataf = fr.Reader(FAVOURITE_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdFavourite;
                    for(auto it:dataf){
                        bdFavourite.path= it;
                        bdFavourite.readFromFile();
                        USERS_BOOKS::favourite.push_back(bdFavourite);
                        USERS_BOOKS::favourite_name.push_back(bdFavourite.name);

                    }
                    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite,USERS_BOOKS::favourite_name);
                    dataf.clear();
                //share scroll box
                    dataf = fr.Reader(SHARED_MP + 1);
                    DATABASE_SEARCH::BookDescriptor bdShare;
                    i=0;
                    for(auto it = dataf.begin(); it != dataf.end(); ++it) {
                        if(i%2 == 0){
                            bdShare.path= *it;
                            bdShare.readFromFile();
                            USERS_BOOKS::shared.push_back(bdShare);
                            USERS_BOOKS::share_name.push_back(bdShare.name);
                        }
                        else{
                            USERS_BOOKS::shared_bookmark.push_back(*it);
                        }
                        i++;
                    }
                    activeBlock[BLOCK]->setData(&sharedN::BookListShare,USERS_BOOKS::share_name);
                    dataf.clear();
                }
                }
            }
        }
    }
    else if (PAGE == BOOK_DETAIL_P)
    {
        if (activePage[PAGE]->isActiveBox(&BookDetails::page, &BookDetails::page.bookmarkText) && key == ENTER_KEY)
        {
            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
        }
        else if (activePage[PAGE]->isActiveBox(&BookDetails::page, &BookDetails::page.reviewNum) && key == ENTER_KEY)
        {
            reviewT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.reviewNum);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.reviewNum, "");
        }
        else if (activePage[PAGE]->isActiveBox(&BookDetails::page, &BookDetails::page.shareUser) && key == ENTER_KEY)
        {
            shareT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.shareUser);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.shareUser, "");
            std::cout << bookmarkT << " " << reviewT << " " << shareT << "\n";
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
        else
        {
            if (activePage[PAGE]->isActiveBox(&SearchN::SNameB) && SearchN::SNameB.getText().size() > 0)
            {
                RELEVANT_OPTIONS::SEARCH_DIRS::setDirsForBook();
                RELEVANT_OPTIONS::results.clear();
                RELEVANT_OPTIONS::result_size = 0;
                RELEVANT_OPTIONS::getRelevantBookNames(SearchN::SNameB.getText(), RELEVANT_OPTIONS::results, RELEVANT_OPTIONS::result_size);
                SearchN::relevantOptionsList.setData(RELEVANT_OPTIONS::results);
                SearchN::relevantOptionsList.setActive(true);
                SearchN::searchResultList.setActive(false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SAuthorB) && SearchN::SAuthorB.getText().size() > 0)
            {
                RELEVANT_OPTIONS::SEARCH_DIRS::setDirsForBook();
                RELEVANT_OPTIONS::results.clear();
                RELEVANT_OPTIONS::result_size = 0;
                RELEVANT_OPTIONS::getRelevantBookAuthors(SearchN::SAuthorB.getText(), RELEVANT_OPTIONS::results, RELEVANT_OPTIONS::result_size);
                SearchN::relevantOptionsList.setData(RELEVANT_OPTIONS::results);
                SearchN::relevantOptionsList.setActive(true);
                SearchN::searchResultList.setActive(false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SGenreB) && SearchN::SGenreB.getText().size() > 0)
            {
                RELEVANT_OPTIONS::SEARCH_DIRS::setDirsForBook();
                RELEVANT_OPTIONS::results.clear();
                RELEVANT_OPTIONS::result_size = 0;
                RELEVANT_OPTIONS::getRelevantBookGenres(SearchN::SGenreB.getText(), RELEVANT_OPTIONS::results, RELEVANT_OPTIONS::result_size);
                SearchN::relevantOptionsList.setData(RELEVANT_OPTIONS::results);
                SearchN::relevantOptionsList.setActive(true);
                SearchN::searchResultList.setActive(false);
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
    //DATABASE_SEARCH::SEARCH_DIRS::setDirsForBook();
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::NAME] = activePage[PAGE]->getText(&SearchN::SNameB);
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::AUTHOR] = activePage[PAGE]->getText(&SearchN::SAuthorB);
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::DATE] = activePage[PAGE]->getText(&SearchN::SDateB);
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::GENRE] = activePage[PAGE]->getText(&SearchN::SGenreB);
    DATABASE_SEARCH::bdlist.clear();
    DATABASE_SEARCH::FullSearch(DATABASE_SEARCH::keywords, DATABASE_SEARCH::bdlist);

    std::vector<std::string> searchBookNameList;
    for (int i = 0; i < DATABASE_SEARCH::bdlist.size(); i++)
        searchBookNameList.push_back(DATABASE_SEARCH::bdlist[i].name);
    SearchN::searchResultList.setData(searchBookNameList);

    activePage[PAGE]->setText(&SearchN::SNameB, "");
    activePage[PAGE]->setText(&SearchN::SAuthorB, "");
    activePage[PAGE]->setText(&SearchN::SGenreB, "");
    activePage[PAGE]->setText(&SearchN::SDateB, "");
    activePage[PAGE]->setActiveBox(&SearchN::SNameB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SGenreB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SDateB, false);
    activePage[SEARCH_P]->setActiveBox(&SearchN::relevantOptionsList, false);
    activePage[SEARCH_P]->setActiveBox(&SearchN::searchResultList, true);
}

