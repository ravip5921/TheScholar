/***** reading block *****/
namespace readingN{
    std::vector<string> books;
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "Reading Books", GLUT_BITMAP_HELVETICA_18);

    void printList(std::vector<string> _books){
        for (auto i = _books.begin(); i != _books.end(); ++i){
                std::cout <<" "<< *i <<std::endl;
            }
    }

     void addReadingComponents(GUIBlock *_readingPage)
    {
        _readingPage->addComponent(&testT);
    }

}
/****** completed block ******/
namespace completedN{
    std::vector<string> books;
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "Completed Books", GLUT_BITMAP_HELVETICA_18);

    void printList(std::vector<string> _books){
        for (auto i = _books.begin(); i != _books.end(); ++i){
                std::cout <<" "<< *i <<std::endl;
            }
    }

     void addCompletedComponents(GUIBlock *_completedPage)
    {
        _completedPage->addComponent(&testT);
    }
}
/**** favourite block *****/
namespace favouriteN{
    std::vector<string> books;
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "favourite Books", GLUT_BITMAP_HELVETICA_18);

    void printList(std::vector<string> _books){
        for (auto i = _books.begin(); i != _books.end(); ++i){
                std::cout <<" "<< *i <<std::endl;
            }
    }

     void addFavouriteComponents(GUIBlock *_favouritePage)
    {
        _favouritePage->addComponent(&testT);
    }
}
/**** shared block ****/
namespace sharedN{
    std::vector<string> books;
    Color testC(0.7, 0.67, 0.6);
    Text testT(-8.7, 4, testC, "Shared Books", GLUT_BITMAP_HELVETICA_18);

     void printList(std::vector<string> _books){
        for (auto i = _books.begin(); i != _books.end(); ++i){
                std::cout <<" "<< *i <<std::endl;
            }
    }

     void addSharedComponents(GUIBlock *_sharedPage)
    {
        _sharedPage->addComponent(&testT);
    }
}
