#include <iostream>
#include <fstream>

using namespace std;

string readLines() {
    ifstream file("dataset/lines.csv");
    string line;
    string linecode;
    string line1;
    int i = 0;
    while(getline(file,line)){
        cout << endl;
        i++;
        if (i == 1) continue;
        int pos = line.find_first_of(',');
        string linecode = line.substr(0,pos);

        for(int dir = 0; dir <= 1; dir++) {
            ifstream file1("dataset/line_" + linecode + "_" + to_string(dir) + ".csv");
            if(!file1.is_open()) continue;
            while (getline(file1, line1)) {
                cout << line1 << endl;
            }
        }
    }

}

string readStops() {
    ifstream file("dataset/stops.csv");
    string line;

    while(getline(file,line,'\n')){
        cout << line << ";" << endl;
    }

}

int main() {
    //readStops();
    readLines();

    return 0;
}

