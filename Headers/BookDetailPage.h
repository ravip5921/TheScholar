class BookDetail : public GUIcomponent
{
    std::string bookname;
    std::vector<std::string> bookDes;
    float bookNamePosX;
    float bookNamePosY;
    float descriptionX;
    float descriptionY;
    float featureButtonX;
    float featureButtonY;

    Coord_Rect backButtonD;
    Coord_Rect openBookButtonD;

    Color navButtonC;
    Color featureButtonC;
    Color titleTextC;
    Color subTitleTextC;
    Color textboxC;
    Color textboxTextC;

    BookDetail(std::string _bookname = "", float _bookNamePosX = -3, float _bookNamePosY = 5, float _descriptionX = -8, float _descriptionY = 4, float _featureButtonX = 1, float _featureButtonY = 1, Coord_Rect _backButtonD = Coord_Rect(8, 8, 2, 1.7), Coord_Rect _openBookButtonD = Coord_Rect(7, -6, 2.5, 1.7), Color _navButtonC = Color(1, 1, 1), Color _featureButtonC = Color(1, 1, 1), Color _titleTextC = Color(1, 1, 1), Color _subTitleTextC = Color(1, 1, 1), Color _textboxC = Color(1, 1, 1), Color _textboxTextC = Color(1, 1, 1)) : backButtonD(_backButtonD), openBookButtonD(_openBookButtonD), navButtonC(_navButtonC), featureButtonC(_featureButtonC), titleTextC(_titleTextC), subTitleTextC(_subTitleTextC), textboxC(_textboxC), textboxTextC(_textboxTextC)
    {
        bookDes.push_back("Name");
        bookDes.push_back("Genre");
        bookDes.push_back("Date");
        bookDes.push_back("ExtraDes");

        Button backButton("Back", navButtonC, titleTextC, backButtonD);
        Button readingButton("Add to reading", featureButtonC, titleTextC, backButtonD, CHAR_WIDTH * 1.5, CHAR_WIDTH);
        Button completedButton("Add to read", featureButtonC, titleTextC, Coord_Rect(featureButtonX, featureButtonY, 2.5, 1.5), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        Button reviewButton("review", featureButtonC, titleTextC, review, CHAR_WIDTH * 1.5, CHAR_WIDTH);
        Button sharedButton("share", featureButtonC, titleTextC, shared, CHAR_WIDTH * 1.5, CHAR_WIDTH);
        Button favouriteButton("Add to favourite", featureButtonC, titleTextC, favourite, CHAR_WIDTH * 1.5, CHAR_WIDTH);
        Button bookmarkButton("Add bookmark", featureButtonC, titleTextC, bookmark, CHAR_WIDTH * 1.5, CHAR_WIDTH);
        Button openBookButton("OPEN BOOK", navButtonC, titleTextC, openBookButtonD, CHAR_WIDTH * 1.5, CHAR_WIDTH);
    }
};
