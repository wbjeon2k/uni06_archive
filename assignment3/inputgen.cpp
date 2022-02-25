#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int randt(){
    int i=0;
    i = 1 + rand%100;
    return i;
}

int randp(){
    int i=0;
    i = 1 + rand%10;
    return i;
}

int randsol(){
    int i=0;
    i = 1 + rand%100;
    return i;
}

int main(){
    
    ofstream input;
    ofstream output;

    input.open("input.txt");
    output.open("answer.txt");
    
    input << "2\n";
    input << "\n"

    int teamn=0;
    int probn=0;
    int solvmin=0;

    
    for(int j=0;j<12;j++){
        teamn = randt();
        probn = randp();
        solvmin = randsol();
        input << teamn << " "<<randp<<" "<<randsol<<"\n";
        output << teamn << " "<<randp<<" "<<randsol<<"\n"
    }

    input <<



}
