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
public:
    FileReader()
    {
        username = "";
    }

    FileReader(std::string username) : username(std::move(username)) {}

    std::vector<std::string> Reader(const int choice);
    std::string ReaderPage(const int choice,string book);
};

std::vector<std::string> FileReader::Reader(const int choice){
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
                if(myText[0] == '$')
                    continue;
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
                if(myText[0] == '$')
                    continue;
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
                if(myText[0] == '$')
                    continue;
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
                if(myText[0] == '$')
                    continue;
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

std::string FileReader::ReaderPage(const int choice,string book){
    ifstream fileReader;
        path = std::string(".\\\\") + std::string("Users\\\\") + username;
        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            while (getline(fileReader, myText)){ // text data from text file stored in vector
                getline(fileReader,pages);
                if(myText == book){
                    fileReader.close();
                    if(pages == "$")
                        pages ="";
                    return pages;
                }
            }
            fileReader.close();
            return "";
        }
        return "";
}
