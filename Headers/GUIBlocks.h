/***** reading block *****/
namespace readingN
{
    std::vector<string> books;
    //Color testC(0.7, 0.67, 0.6);
    //Coord_Rect sb(5, 0, 4, 3);
    //Text testT(-8.7, 4, testC, "Reading Books", GLUT_BITMAP_HELVETICA_18);
   // ScrollBox test(dataf, sb, 5);
    /*void printList(std::vector<std::string> _books){      //prints the list elements of vector in console
        for (auto i = _books.begin(); i != _books.end(); ++i){
            std::cout << " " << *i << std::endl;
        }
    }*/

    void addReadingComponents(GUIBlock *_readingPage)
    {
      //  _readingPage->addComponent(&testT);
      //  _readingPage->addComponent(&test);
    }

} // namespace readingN
/****** completed block ******/
namespace completedN
{
    std::vector<string> books;
    //Color testC(0.7, 0.67, 0.6);
    //Text testT(-8.7, 4, testC, "Completed Books", GLUT_BITMAP_HELVETICA_18);

    void addCompletedComponents(GUIBlock *_completedPage)
    {
      //  _completedPage->addComponent(&testT);
    }
} // namespace completedN
/**** favourite block *****/
namespace favouriteN
{
    std::vector<std::string> books;
    //Color testC(0.7, 0.67, 0.6);
    //Text testT(-8.7, 4, testC, "favourite Books", GLUT_BITMAP_HELVETICA_18);

    void addFavouriteComponents(GUIBlock *_favouritePage)
    {
      //  _favouritePage->addComponent(&testT);
    }
} // namespace favouriteN
/**** shared block ****/
namespace sharedN
{
    std::vector<string> books;
    //Color testC(0.7, 0.67, 0.6);
    //Text testT(-8.7, 4, testC, "Shared Books", GLUT_BITMAP_HELVETICA_18);

    void addSharedComponents(GUIBlock *_sharedPage)
    {
      //  _sharedPage->addComponent(&testT);
    }
} // namespace sharedN
