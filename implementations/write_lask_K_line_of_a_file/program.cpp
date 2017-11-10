#include <iostream>
#include <fstream>
 
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3) {
        cout << "usage : ./programm filename K" << endl;
        return 0;
    }
    
    string filename = argv[1];
    int k = (int) strtol(argv[2], NULL, 10);

    ifstream myfile(filename);
    string line;
    if (myfile.is_open()) {
        //myfile.seekg(20);
        while(getline(myfile, line)) {
            cout << line << endl;
        }
        myfile.close();
    } else {
        cout << "no file" << endl;
    }

    return 0;
}
