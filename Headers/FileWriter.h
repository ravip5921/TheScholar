#include "logIn.h"
/******
Write string in .txt file,choice are:
    1.Reading
    2.Completed
    3.Favourite
    4.Share

******/

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
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else if (choice == 4)
        {
            path = path + string("\\\\share.txt");
            fileWrite.open(path.c_str(), ios::app);
            fileWrite << toWrite << endl;
            fileWrite << bookmarkPage <<endl;
            fileWrite.close();
        }
        else
        {
            cout << "Invalid choice,unable to write";
        }
    }
}
