#include <string> 
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    fstream linksCSV("links.csv");
    if (!linksCSV) {
        ofstream linksCSV("links.csv");
        cout << "File created." << endl;
        linksCSV <<"Test\n";
        linksCSV.close();
    }
    else {
        cout << "File already exists." << endl;
    }
    return 0;
}