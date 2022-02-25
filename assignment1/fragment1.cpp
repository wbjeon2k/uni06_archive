#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string.h>

using namespace std;

int main(){
    
    ifstream txt;
    vector <int> szvec;

    txt.open("input.txt");

    string n1;

    getline(txt,n1);

    int n;
    istringstream ss(n1);
    ss >> n;

    vector< vector<string> > strtxt;


}
