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
    cout << addr << endl;
    return true;
}

bool randomCorrupt(bool doTheSameThingAgain){
    target.open(file, std::ios::binary | std::ios::in | std::ios::out | ios::ate);
    if(!doTheSameThingAgain){
        cout << "where the header of your file ends?" << endl;
        cin >> headerSize;
    }
    randomAddr = headerSize + ( std::rand() % ( target.tellg() - headerSize + 1 ) );
    if(setByte(target,randomAddr,rand()))
        return true;
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
    }   
}

