#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

int main() {
    fstream file("../assets/book.csv", ios::out | ios::in | ios::app);
    // read data from file as string
    string line;
    vector<string> data;
    while (getline(file, line)) {
        data.push_back(line);
    }
    // print data
    for (auto i : data) {
        cout << i << endl;
    }
}