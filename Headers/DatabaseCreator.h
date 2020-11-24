#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include "./Utility.h"
#include "./Sort.h"

const char DIRECTORY_SEPERATOR = '/';
const int MAX_AUTHOR_NAME = 15;
const int FILE_NOT_SORTED = 0;
const int FILE_SORTED = 1;
const char AUTHOR_HEADER_BLANK_CHAR = ' ';
const std::string BOOKDES_EXT = ".des";
const std::string PATH_FILE = "#.txt";
//required directories
const std::string DIR_DATA = "./data/";
const std::string DIR_DATA_BOOK = "./data/book/";
const std::string DIR_SEARCH = "./search/";
const std::string DIR_SEARCH_BOOK = "./search/book/";
const std::string DIR_SEARCH_BOOK_NAME = "./search/book/name/";
const std::string DIR_SEARCH_BOOK_AUTHOR = "./search/book/author/";
const std::string DIR_SEARCH_BOOK_GENRE = "./search/book/genre/";
const std::string DIR_SEARCH_BOOK_DATE = "./search/book/date/";
const std::string FILE_BOOKCOUNT = DIR_DATA_BOOK + "#bookcount.txt";
const std::string FILE_AUTHOR_HEADER = "#header.txt";
const std::string FILE_AUTHOR_STATUS = "#status.txt";
const std::string FILE_AUTHOR_PAIR = "#pair.txt";

void createRequiredDirectories()
{
    mkdir(DIR_DATA.c_str());
    mkdir(DIR_DATA_BOOK.c_str());
    mkdir(DIR_SEARCH.c_str());
    mkdir(DIR_SEARCH_BOOK.c_str());
    mkdir(DIR_SEARCH_BOOK_NAME.c_str());
    mkdir(DIR_SEARCH_BOOK_AUTHOR.c_str());
    mkdir(DIR_SEARCH_BOOK_GENRE.c_str());
    mkdir(DIR_SEARCH_BOOK_DATE.c_str());

    if (!Utility::FileHandler::exists(FILE_BOOKCOUNT))
    {
        std::ofstream outStream;
        outStream.open(FILE_BOOKCOUNT.c_str());
        outStream << 0;
    }
}

class BookDescriptor
{
public:
    static const char NEXT_FIELD_DELIM = '\n';
    static const char SAME_FIELD_DELIM = '+';
    std::string bookPath;
    std::string name;
    std::string author;
    std::string genre;
    std::string date;
    std::string extrades;
    std::string path;

    void createDescriptorFile()
    {
        std::ifstream inStream(FILE_BOOKCOUNT.c_str());
        int bc;
        inStream >> bc;
        inStream.close();
        bc++;
        path = DIR_DATA_BOOK + std::to_string(bc) + BOOKDES_EXT;
        std::ofstream outStream(FILE_BOOKCOUNT.c_str());
        outStream << bc;
        outStream.close();

        outStream.open(path.c_str());
        outStream << bookPath << NEXT_FIELD_DELIM;
        outStream << name << NEXT_FIELD_DELIM;
        outStream << author << NEXT_FIELD_DELIM;
        outStream << genre << NEXT_FIELD_DELIM;
        outStream << date << NEXT_FIELD_DELIM;
        outStream << extrades;

        outStream.close();
    }

private:
    void _name()
    {
        std::vector<std::string> bookWords;
        Utility::String::breakString(name, bookWords, std::string(" :"));
        std::string curBookPath = DIR_SEARCH_BOOK_NAME + name[0];
        mkdir(curBookPath.data());
        for (int i = 0; i < bookWords.size(); i++)
        {
            curBookPath += DIRECTORY_SEPERATOR + bookWords[i];
            mkdir(curBookPath.data());
        }
        curBookPath += DIRECTORY_SEPERATOR + PATH_FILE;
        //create #.txt <- path of bookdescriptor
        std::ofstream outstream;
        outstream.open(curBookPath.data(), std::ios_base::app);
        outstream << path << "\n";
        outstream.close();
    }
    void _author()
    {
        std::vector<std::string> authors;
        Utility::String::breakString(author, authors, std::string(" +"));
        std::string baseBookPath = DIR_SEARCH_BOOK_AUTHOR;
        std::string curBookPath;
        std::string bdBookPath;
        std::string headerPath;
        std::string statusPath;
        std::fstream outstream;
        std::fstream astream;
        int nameCount;
        int status = FILE_NOT_SORTED;
        for (int i = 0; i < authors.size(); i++)
        {
            baseBookPath.push_back(authors[i][0]);
            mkdir(baseBookPath.data());
            curBookPath = baseBookPath + DIRECTORY_SEPERATOR + authors[i];
            mkdir(curBookPath.data());

            headerPath = baseBookPath + DIRECTORY_SEPERATOR + FILE_AUTHOR_HEADER;
            statusPath = baseBookPath + DIRECTORY_SEPERATOR + FILE_AUTHOR_STATUS;
            //std::cout<<"\nCP: "<<curBookPath<<"  SP: "<<statusPath<<"  HP: "<<headerPath;
            if (!Utility::FileHandler::exists(statusPath))
            {
                astream.open(statusPath.c_str(), std::ios_base::out);
                astream << FILE_NOT_SORTED; //<<"\n"<<0<<"\n"; //status \n namecount
                astream.close();
            }
            else
            {
                astream.open(statusPath.c_str(), std::ios_base::in);
                astream >> status;
                astream.close();
            }

            if (status == FILE_NOT_SORTED)
            {
                outstream.open(headerPath.c_str(), std::ios_base::app);
                for (int j = 0; j < MAX_AUTHOR_NAME; j++)
                {
                    if (j < authors[i].size())
                        outstream << authors[i][j];
                    else
                        outstream << AUTHOR_HEADER_BLANK_CHAR;
                }
            }
            else
            {
                outstream.open(headerPath.c_str());
                outstream.seekg(0, std::ios::end);
                int noOfEls = outstream.tellg() / MAX_AUTHOR_NAME;
                outstream.seekg(0, std::ios::beg);
                insertInSortedFile(outstream, authors[i], noOfEls, MAX_AUTHOR_NAME);
            }
            outstream.close();

            bdBookPath = curBookPath + DIRECTORY_SEPERATOR + PATH_FILE;
            outstream.open(bdBookPath.data(), std::ios_base::app);
            outstream << path << "\n";
            outstream.close();
            /*bdBookPath = curBookPath + DIRECTORY_SEPERATOR + FILE_AUTHOR_PAIR;
            outstream.open(bdBookPath.data(),std::ios_base::app);
            outstream<<path<<"\n";
            outstream.close();*/

            baseBookPath.pop_back();
            //create #.txt <- path of bookdescriptor
        }
    }
    void _date()
    {
        std::string bookPath;
        bookPath = DIR_SEARCH_BOOK_DATE + date;
        mkdir(bookPath.data());
        std::ofstream outstream;
        std::string bdBookPath = bookPath + DIRECTORY_SEPERATOR + PATH_FILE; // replace path file with book name
        outstream.open(bdBookPath.data(), std::ios_base::app);
        outstream << path;
        outstream.close();
    }
    void _genre()
    {
        std::vector<std::string> genres;
        Utility::String::breakString(genre, genres, std::string(" +"));
        std::string baseBookPath = DIR_SEARCH_BOOK_GENRE;
        std::string curBookPath;
        std::string bdBookPath;
        std::ofstream outstream;
        for (int i = 0; i < genres.size(); i++)
        {
            baseBookPath.push_back(genres[i][0]);
            mkdir(baseBookPath.data());
            curBookPath = baseBookPath + DIRECTORY_SEPERATOR + genres[i];
            //std::cout<<"\n"<<curBookPath;
            mkdir(curBookPath.data());
            //create #.txt <- path of bookdescriptor
            bdBookPath = curBookPath + DIRECTORY_SEPERATOR + PATH_FILE;
            outstream.open(bdBookPath.data(), std::ios_base::app);
            outstream << path;
            outstream.close();

            baseBookPath.pop_back();
        }
    }

public:
    void createAllDirectories()
    {
        _name();
        _author();
        _genre();
        _date();
    }
};
