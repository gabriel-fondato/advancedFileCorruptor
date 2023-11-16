#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string option;
string file;
int headerSize;
int fileSize;
string doUserWantToContinue;
int randomAddr;
fstream target;
fstream clone;
int clones;
int i = 0;
string cloneFileName;
string fileExtention;
int fileExtentionPosition;

bool setByte(fstream &target, int addr, char val) {
    // Open the file in binary mode

    if (!target.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }
    fileSize = target.tellg();
    // Move to the desired position in the file
    target.seekp(addr);

    // Set the value of the byte
    target.write(&val, sizeof(char));

    // Close the file
    target.close();

    cout << "Byte value set successfully!" << endl;
    cout << addr << endl; //print the corrupted addr
    return true;
}

int getRandomAddr(fstream &target, int headerSize){
    randomAddr = headerSize + ( std::rand() % ( target.tellg() - headerSize + 1 ) ); // chose random number betteen headerSize and the size of the target
}

bool randomCorrupt(bool doTheSameThingAgain){
    target.open(file, std::ios::binary | std::ios::in | std::ios::out | ios::ate);
    if(!doTheSameThingAgain){
        cout << "where the header of your file ends?" << endl;
        cin >> headerSize;
    }
    
    if(setByte(target,getRandomAddr(target,headerSize),rand()))
        return true;
}

bool randomCloneCorrupt(){
    target.open(file, std::ios::binary | std::ios::in | std::ios::out | ios::ate);
    cout << "where the header of your file ends?" << endl;
    cin >> headerSize;
    randomAddr = getRandomAddr(target,headerSize);
    cout << "how many files do you want to create?" << endl;
    cin >> clones;

    fileExtentionPosition = file.find(".");  //find where is the file extention
    fileExtention = file.substr(fileExtentionPosition - 1); //get file extention
    string originalFileName = file + fileExtention;
    file = file.substr(0,file.length() - fileExtention.length());  //remove the file extention from the filename
      
    while (clones > 0){
        
        if(!i==0)
            cloneFileName = file;
            cloneFileName = cloneFileName + to_string(i);

        cout << cloneFileName << endl;

        target.open(file, ios::in | ios::binary);
        clone.open(cloneFileName, ios::out | ios::binary);
        clone << target.rdbuf();
        clone.close();
        target.close();
        clone.open(cloneFileName, std::ios::binary | std::ios::in | std::ios::out | ios::ate);
        setByte(clone,randomAddr,rand());
        clone.close();
        if(!i==0)
            cloneFileName = cloneFileName.substr(0, cloneFileName.length() - 1);
        ++i;
        --clones;
        cout << file + "" + fileExtention << endl;
        rename(cloneFileName.c_str(),originalFileName.c_str());
    }

}

int main(){
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator
    cout << "chose your option (read the README.md first)" << endl;
    cout << "1. Random corrupt" << endl;
    cout << "2. Random clone corrupt" << endl;
    cout << "3. Set a value for an adress" << endl;
    cin >> option;

    cout << "what is the path of your file?" << endl;
    cin >> file;

    if(option=="1"){
        randomCorrupt(false);
        do {
            cout << "want to do it again?" << endl;
            cin >> doUserWantToContinue;
            if(doUserWantToContinue=="yes") 
                randomCorrupt(true);
        } while (doUserWantToContinue=="yes");
    }else if(option=="2"){
        randomCloneCorrupt();
    }   
}

