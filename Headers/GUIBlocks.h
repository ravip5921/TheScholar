/***** reading block *****/
namespace readingN{
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "Reading Books", GLUT_BITMAP_HELVETICA_18);

     void addReadingComponents(GUIBlock *_readingPage)
    {
        _readingPage->addComponent(&testT);
    }

}
/****** completed block ******/
namespace completedN{
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "Completed Books", GLUT_BITMAP_HELVETICA_18);

     void addCompletedComponents(GUIBlock *_completedPage)
    {
        _completedPage->addComponent(&testT);
    }
}
/**** favourite block *****/
namespace favouriteN{
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "favourite Books", GLUT_BITMAP_HELVETICA_18);

     void addFavouriteComponents(GUIBlock *_favouritePage)
    {
        _favouritePage->addComponent(&testT);
    }
}
/**** shared block ****/
namespace sharedN{
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "Shared Books", GLUT_BITMAP_HELVETICA_18);

     void addSharedComponents(GUIBlock *_sharedPage)
    {
        _sharedPage->addComponent(&testT);
    }
}
