#include <iostream>
#include <fstream>
using namespace std;

string option;
string file;

int main(){
    cout << "chose your option (read the README.md first)" << endl;
    cout << "1. Random corrupt" << endl;
    cout << "2. Random clone corrupt" << endl;
    cout << "3. Set a value for an adress" << endl;
    cin >> option;

    cout << "what is the path of your file?" endl;
    cin >> file;
    fstream target(file, std::ios::binary | std::ios::in | std::ios::out); //open file


}

bool setByte(int addr, int val){

}