#include "FileWriter.h"
/******
 Read .txt file,choice are:
    1.Reading
    2.Completed
    3.Favourite
    4.Share
******/

class FileReader
{
private:
    int i = 1;
    std::string username, path, myText, pages;
    std::vector<std::string> books;
    std::vector<std::string> bookmarkPages;

public:
    FileReader()
    {
        username = "";
    }

    FileReader(std::string username) : username(std::move(username)) {}

    std::vector<std::string> Reader(const int choice);
    //std::vector<std::string> ReaderPages(const int choice);
};

std::vector<std::string> FileReader::Reader(const int choice)
{
    if (username != "")
    {
        ifstream fileReader;
        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        books.clear();
        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                getline(fileReader,pages);
                if(pages == "$"){
                    pages = "";
                }
                else{
                    pages ="        Page " + pages;
                }
                myText = myText + pages;
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 2)
        {
            path = path + string("\\\\completed.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                getline(fileReader,pages);
                if(pages == "$"){
                    pages = "";
                }
                else{
                    pages ="        Page " + pages;
                }
                myText = myText + pages;
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 4)
        {
            path = path + string("\\\\share.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                getline(fileReader,pages);
                if(pages == "$"){
                    pages = "";
                }
                else{
                    pages ="        Page " + pages;
                }
                myText = myText + pages;
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 3)
        {
            path = path + string("\\\\favourite.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                getline(fileReader,pages);
                if(pages == "$"){
                    pages = "";
                }
                else{
                    pages ="        Page " + pages;
                }
                myText = myText + pages;
                books.push_back(myText);
                i++;
            }
            fileReader.close();
        }
        else
        {
            cout << "Invalid choice,unable to read";
        }
    }
    return books;
}

/*std::vector<std::string> FileReader::ReaderPages(const int choice)
{
    if (username != "")
    {
        ifstream fileReader;
        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        bookmarkPages.clear();
        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, pages)){ // text data from text file stored in vector
                books.push_back(pages);
                getline(fileReader,myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 2)
        {
            path = path + string("\\\\completed.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, pages)){ // text data from text file stored in vector
                books.push_back(pages);
                getline(fileReader,myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 4)
        {
            path = path + string("\\\\share.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, pages)){ // text data from text file stored in vector
                books.push_back(pages);
                getline(fileReader,myText);
                i++;
            }
            fileReader.close();
        }
        else if (choice == 3)
        {
            path = path + string("\\\\favourite.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, pages)){ // text data from text file stored in vector
                books.push_back(pages);
                getline(fileReader,myText);
                i++;
            }
            fileReader.close();
        }
        else
        {
            cout << "Invalid choice,unable to read";
        }
    }
    return bookmarkPages;
}*/
