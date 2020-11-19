/*void addDynamicComponent(GUIPage * _page,GUIcomponent* _component)
    {
        _page->addComponent(_component);
    }*/
/**** Welcome Page *****/
namespace welcome
{
    float devInfoX = -9.1;
    float devInfoY = -4.5;
    Color titleC(0.7, 0.67, 0.6);
    Color devInfo(0.9, 0.9, 0.91);
    Color loginButtonC(0.1, 0.3, 0.7);
    Color loginButtonTextC(1, 1, 1);

    Coord_Rect loginButtonD(2, -8, 3, 1.5);
    Coord_Rect signupButtonD(loginButtonD, 'x', 3.4);

    Text titleT(-2.5, 2.5, titleC, "THE SCHOLAR", GLUT_BITMAP_TIMES_ROMAN_24);
    Text subTitleT(-2.2, 1.8, titleC, "E-lib of some sort", GLUT_BITMAP_HELVETICA_18);
    Text devInfoA(devInfoX, devInfoY, devInfo, "DEVELOPED BY:", GLUT_BITMAP_TIMES_ROMAN_24);
    Text devInfoB(devInfoX, devInfoY - 1, devInfo, "Ravi Pandey", GLUT_BITMAP_HELVETICA_18);
    Text devInfoC(devInfoX, devInfoY - 2, devInfo, "Rohan Chhetry", GLUT_BITMAP_HELVETICA_18);
    Text devInfoD(devInfoX, devInfoY - 3, devInfo, "Nikesh D.C.", GLUT_BITMAP_HELVETICA_18);
    Button loginButton("Log In", loginButtonC, loginButtonTextC, loginButtonD);
    Button signupButton("Sign Up", loginButtonC, loginButtonTextC, signupButtonD);

    void addWelcomComponents(GUIPage *_welcomePage)
    {
        _welcomePage->addComponent(&titleT);
        _welcomePage->addComponent(&subTitleT);
        _welcomePage->addComponent(&devInfoA);
        _welcomePage->addComponent(&devInfoB);
        _welcomePage->addComponent(&devInfoC);
        _welcomePage->addComponent(&devInfoD);
        _welcomePage->addComponent(&loginButton);
        _welcomePage->addComponent(&signupButton);
    }
} // namespace welcome
/**** Login Page *****/

namespace LogIn
{
    Color userNameC(0.978, 0.849, 0.9055);
    Color passwordC = userNameC;
    Color boxTextC(0.23, 0.17, 0.91);
    Color logInTextC(1, 1, 0);
    Color logInButtonTextC(1, 0, 1);
    Color logInButtonC(0.1, 0.9, 0.43);
    Color toSignupC(0.3, 0.9, 0.6);
    Color pageTextC(1, 0, 0);
    Color rectBoxC(1, 1, 1);
    Color TitleC(0.5, 0, 0.5);

    Coord_Rect logInButtonD(-2, -6, 3, 1.2);
    Coord_Rect userNameD(-5, 0, 9, 1.9);
    Coord_Rect passwordD(userNameD, 'y', -3);
    Coord_Rect toSignupD(-5, -8, 5.5, 1.5);
    Coord_Rect rectBoxA(-6.5, -3.5, 12.5, 7);
    Coord_Rect rectBoxB(-6.3, -3.3, 12.1, 6.6);

    Text logInScreen(-2, 5, pageTextC, "LOGIN SCREEN", GLUT_BITMAP_TIMES_ROMAN_24);
    Text userNameT(-4.8, 2.2, TitleC, "Enter User-name:", GLUT_BITMAP_HELVETICA_18);
    Text passwordT(-4.8, -0.8, TitleC, "Enter Password:", GLUT_BITMAP_HELVETICA_18);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 4.5, -2.8, logInButtonC);
    Button logInButton("Log In", logInButtonC, logInButtonTextC, logInButtonD);
    Button toSignup("New to The SCHOLAR?", toSignupC, logInButtonTextC, toSignupD);
    rectOutline rectBoxa(rectBoxA, rectBoxC);
    rectOutline rectBoxb(rectBoxB, rectBoxC);

    void addlogInComponents(GUIPage *logInPage)
    {
        logInPage->addComponent(&logInScreen);
        logInPage->addComponent(&userNameB);
        logInPage->addComponent(&passwordB);
        logInPage->addComponent(&userNameT);
        logInPage->addComponent(&passwordT);
        logInPage->addComponent(&showPassword);
        logInPage->addComponent(&logInButton);
        logInPage->addComponent(&toSignup);
        logInPage->addComponent(&rectBoxa);
        logInPage->addComponent(&rectBoxb);
    }
} // namespace LogIn

/***** Sign Up Page *******/
namespace SignUp
{
    Color userNameC(0.978, 0.849, 0.9055);
    Color passwordC = userNameC;
    Color boxTextC(0.23, 0.17, 0.91);
    Color signUpTextC(1, 1, 0);
    Color signUpButtonTextC(1, 0, 1);
    Color signUpButtonC(0.1, 0.9, 0.43);
    Color pageTextC(1, 0, 0);
    Color toLoginC(0.3, 0.9, 0.6);
    Color rectBoxC(1, 1, 1);
    Color TitleC(0.5, 0, 0.5);

    Coord_Rect signUpButtonD(-2, -6, 3, 1.2);
    Coord_Rect userNameD(-5, 0, 9, 1.9);
    Coord_Rect passwordD(userNameD, 'y', -3);
    Coord_Rect toLoginD(-3, -8, 4.8, 1.3);
    Coord_Rect rectBoxA(-6.5, -3.5, 12.5, 7);
    Coord_Rect rectBoxB(-6.3, -3.3, 12.1, 6.6);

    Text signUpScreen(-2, 5, pageTextC, "SIGNUP SCREEN", GLUT_BITMAP_TIMES_ROMAN_24);
    Text userNameT(-4.8, 2.2, TitleC, "Enter User-name:", GLUT_BITMAP_HELVETICA_18);
    Text passwordT(-4.8, -0.8, TitleC, "Enter Password:", GLUT_BITMAP_HELVETICA_18);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 4.5, -2.8, signUpButtonC);
    Button signUpButton("Sign Up", signUpButtonC, signUpButtonTextC, signUpButtonD);
    Button toLogin("Already a member?", toLoginC, signUpButtonTextC, toLoginD);
    rectOutline rectBoxa(rectBoxA, rectBoxC);
    rectOutline rectBoxb(rectBoxB, rectBoxC);

    void addsignUpComponents(GUIPage *signUpPage)
    {
        signUpPage->addComponent(&signUpScreen);
        signUpPage->addComponent(&userNameB);
        signUpPage->addComponent(&passwordB);
        signUpPage->addComponent(&userNameT);
        signUpPage->addComponent(&passwordT);
        signUpPage->addComponent(&showPassword);
        signUpPage->addComponent(&signUpButton);
        signUpPage->addComponent(&toLogin);
        signUpPage->addComponent(&rectBoxa);
        signUpPage->addComponent(&rectBoxb);
    }
} // namespace SignUp
/********* Home page **********/
namespace Home{

    Color userNameC(1,1,1);
    Color logoutButtonC(0.1, 0.3, 0.7);
    Color logoutButtonTextC(1, 1, 1);
    Color miniButtonsC(1,0.5,0.6);

    Coord_Rect logoutButtonD(6.5, 8, 3, 1.5);
    Coord_Rect reading(-8,4,2,1);
    Coord_Rect completed(-6,4,2,1);
    Coord_Rect favourite(-4,4,2,1);
    Coord_Rect shared(-2,4,2,1);

    Text User(3.5,8.5,userNameC,userName,GLUT_BITMAP_HELVETICA_18);

    Button logoutButton("Log Out", logoutButtonC, logoutButtonTextC, logoutButtonD);
    Button readingButton("Reading", miniButtonsC, logoutButtonTextC, reading);
    Button completedButton("Completed", miniButtonsC, logoutButtonTextC, completed);
    Button favouriteButton("Favourite", miniButtonsC, logoutButtonTextC, favourite);
    Button sharedButton("Shared", miniButtonsC, logoutButtonTextC, shared);

    void addHomeComponents(GUIPage *_homePage)
    {
        _homePage->addComponent(&logoutButton);
        _homePage->addComponent(&User);
        _homePage->addComponent(&readingButton);
        _homePage->addComponent(&completedButton);
        _homePage->addComponent(&favouriteButton);
        _homePage->addComponent(&sharedButton);

    }
}//namespace Home
