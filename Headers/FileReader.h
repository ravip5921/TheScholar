#include "FileWriter.h"
/******
 Read .txt file,choice are:
    1.Reading
    2.Completed
    3.Share
    4.Favourite
******/

class FileReader{
private:
    int i=1;
    std::string username, path ,myText;
public:
    FileReader(){
        username = "";
    }

    FileReader(std::string username):username(std::move(username)){}

    void Reader(const int choice);
};

void FileReader::Reader(const int choice){
    if(username != ""){
        ifstream fileReader;
        path = std::string(".\\\\") + std::string("Users\\\\") + username;

        if(choice == 1){
            path = path + string("\\\\reading.txt");
            fileReader.open(path.c_str());
            cout<<endl<<"Reading list:"<<endl;
            while (getline (fileReader, myText)) {      // Output the text from the file
                cout <<i<<"."<< myText<<endl;
                i++;
            }
            fileReader.close();
        }
        else if(choice == 2){
            path = path + string("\\\\completed.txt");
            fileReader.open(path.c_str());
            cout<<endl<<"Completed list:"<<endl;
            while (getline(fileReader, myText)) {      // Output the text from the file
                cout <<i<<"."<< myText<<endl;
                i++;
            }
            fileReader.close();
        }
        else if(choice == 3){
            path = path + string("\\\\share.txt");
            fileReader.open(path.c_str());
            cout<<endl<<"Share list:"<<endl;
            while (getline(fileReader, myText)) {      // Output the text from the file
                cout <<i<<"."<< myText<<endl;
                i++;
            }
            fileReader.close();
        }
        else if(choice == 4){
            path = path + string("\\\\favourite.txt");
            fileReader.open(path.c_str());
            cout<<endl<<"Favourite list:"<<endl;
            while (getline(fileReader, myText)) {      // Output the text from the file
                cout <<i<<"."<< myText<<endl;
                i++;
            }
            fileReader.close();
        }
        else{
            cout<<"Invalid choice,unable to read";
        }
    }
}
