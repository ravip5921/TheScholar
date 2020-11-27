/***** reading block *****/
namespace readingN
{
    Color scrollBoxC(0,1,0);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1,1,1);

    Coord_Rect BookListD(-8.5, -6.5, 8, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListReading(dataf, BookListD, 8,scrollBoxC);
    Button refreshButton("Refresh1", refreshButtonC, refreshButtonTextC, refreshButtonD,CHAR_WIDTH * 1.2, CHAR_WIDTH * 1.3);

    void addReadingComponents(GUIBlock *_readingPage)
    {
        _readingPage->addComponent(&BookListReading);
        _readingPage->addComponent(&refreshButton);
    }

} // namespace readingN
/****** completed block ******/
namespace completedN
{
    Color scrollBoxC(0,1,0);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1,1,1);

    Coord_Rect BookListD(-8.5, -6.5, 8, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListCompleted(dataf, BookListD, 8,scrollBoxC);
    Button refreshButton("Refresh2", refreshButtonC, refreshButtonTextC, refreshButtonD, CHAR_WIDTH * 1.2, CHAR_WIDTH * 1.3);

    void addCompletedComponents(GUIBlock *_completedPage)
    {
        _completedPage->addComponent(&BookListCompleted);
        _completedPage->addComponent(&refreshButton);
    }
} // namespace completedN
/**** favourite block *****/
namespace favouriteN
{
    Color scrollBoxC(0,1,0);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1,1,1);

    Coord_Rect BookListD(-8.5, -6.5, 8, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListFavourite(dataf, BookListD, 8,scrollBoxC);
    Button refreshButton("Refresh3", refreshButtonC, refreshButtonTextC, refreshButtonD, CHAR_WIDTH * 1.2, CHAR_WIDTH * 1.3);

    void addFavouriteComponents(GUIBlock *_favouritePage)
    {
        _favouritePage->addComponent(&BookListFavourite);
        _favouritePage->addComponent(&refreshButton);
    }
} // namespace favouriteN
/**** shared block ****/
namespace sharedN
{
    Color scrollBoxC(0,1,0);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1,1,1);

    Coord_Rect BookListD(-8.5, -6.5, 8, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListShare(dataf, BookListD, 8,scrollBoxC);
    Button refreshButton("Refresh4", refreshButtonC, refreshButtonTextC, refreshButtonD, CHAR_WIDTH * 1.2, CHAR_WIDTH * 1.3);

    void addSharedComponents(GUIBlock *_sharedPage)
    {
        _sharedPage->addComponent(&BookListShare);
        _sharedPage->addComponent(&refreshButton);
    }
} // namespace sharedN
