#include "logIn.h"
#include<cstdlib>
/******
 Read .txt file,choice are:
    1.Reading
    2.Completed
    3.Favourite
    4.Share
******/

/********** FILE READER CLASS **********/
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

/***********  FILE WRITER CLASS ************/
class FileWriter
{
private:
    std::string username;

public:
    FileWriter()
    {
        username = "";
    }

    FileWriter(std::string username) : username(std::move(username)) {}
    void Writer(const int choice, std::string toWrite, std::string bookmarkPage= "$");
    void maskBookName(const int position, char choice, std::string bookName);
    bool UserExists();

};

void FileWriter::Writer(const int choice, std::string toWrite, std::string bookmarkPage)
{
    if (username != "")
    {
        ofstream fileWrite;
        string path = std::string(".\\\\") + std::string("Users\\\\") + username;

        if (choice == 1)
        {
            path = path + string("\\\\reading.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else if (choice == 2)
        {
            path = path + string("\\\\completed.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else if (choice == 3)
        {
            path = path + string("\\\\favourite.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite.close();
        }
        else if (choice == 4)
        {
            path = path + string("\\\\share.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite.close();
        }
        else
        {
            cout << "Invalid choice,unable to write";
        }
    }
}

bool FileWriter::UserExists()
{
    DirectoryHandler checkUserDir;
    std::string checkDirPath = std::string(".\\\\") + std::string("Users\\\\") + username;
    checkUserDir.setDirName(checkDirPath.data());
    if (checkUserDir.exists()){
        return true;
    }
    return false;
}

void FileWriter::maskBookName(const int position, char choice,std::string bookName){
        fstream fileWrite;
        string path = std::string(".\\\\") + std::string("Users\\\\") + username;
        int i;
        std::string maskBook= "$" + bookName,temp;
        if (choice == 'R')
        {
            std::cout<<"Reading\n";
            path = path + string("\\\\reading.txt");
            fileWrite.open(path.c_str(),ios::out | ios::in);
            i=((2*position)+1);

            fileWrite.close();
        }
        else if (choice == 'C')
        {
            path = path + string("\\\\completed.txt");
            fileWrite.open(path.c_str(),ios::out | ios::in);
            //fileWrite << toWrite << endl;
            //fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else if (choice == 'F')
        {
            std::cout<<"Fav\n";
            path = path + string("\\\\favourite.txt");
            fileWrite.open(path.c_str(),ios::out | ios::in);
            i=position;
            for(int j=0;j<i;j++){
                getline(fileWrite,temp);
                std::cout<<j<<"."<<temp<<std::endl;
            }
            fileWrite<<maskBook<<std::endl;
            fileWrite.close();
        }
        else if (choice == 'S')
        {
            path = path + string("\\\\share.txt");
            fileWrite.open(path.c_str(),ios::out | ios::in);
            //fileWrite << toWrite << endl;
            fileWrite.close();
        }


}
