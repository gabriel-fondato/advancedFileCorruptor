#include <iostream>
#include <fstream>
using namespace std;

string option;
string file;
int headerSize;
int fileSize;

bool setByte(const string& filename, int addr, char val) {
    // Open the file in binary mode
    fstream target(filename, std::ios::binary | std::ios::in | std::ios::out);

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
        cout << "where the header of your file ends?" << endl;
        cin >> headerSize;
        setByte();
    }
}

