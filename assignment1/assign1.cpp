#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <sstream>

using namespace std;

bool comp(const string& a, const string& b){
    //function to sort the fragments with their size
    if (a.length() < b.length()){
        return true;
    }
}

int maxi(const vector<string>&ans){
    //this is the function which
    //gets the list of possible answers
    //and print out the original fragment

    //vector<int>maxi;
    vector<string>candi;//vector for the answer candidates

    string temp="";

    for(int i=0;i<ans.size();i++){
        if(ans[i]!=temp){
            temp = ans[i];
            candi.push_back(temp);
        }//if ans[i] is not a blank, then add it to the candidate list
    }

    int m=0;
    int mx=0;
    for(int i=0;i<candi.size();i++){//finds which answer is chosen the most
        for(int j=0;j<ans.size();j++){
            if(candi[i]==ans[j]){
                m++;
            }
        }
        if(m>mx){
            temp = candi[i];
            mx = m;
        }
        m=0;
    }
    cout<<temp << endl;//prints out the most selected answer

}

int main(){

    vector< vector<string> > strtxt;
    vector<int> szvec;


    string n1;

    //getline(txt,n1);

    int n;
    char blank;

    //cout << n << endl;
    cin >> n1;//get the number of sets given
    //cout << n << endl;
    n = n1[0]-'0';
    getline(cin,n1);
    getline(cin,n1);//ignores a blank line
    string tmp1;
    char tmp[145];

    int cnt=0;
    int sz=0;
    for(int i=0;i<n;i++){//saves the fragment sets
        vector<string>temp;
        //cout << i+1 << endl;
        while( true){
            getline(cin,tmp1);
            if(tmp1 == ""){//if it reaches to the end of set, the get out
                //cout << "check" << endl;
                break;
            }
            else{
                temp.push_back(tmp1);
                //sz+= tmp.size();
                cnt ++;
            }
        }
        sz=0;
        //for(int i=0;i<temp.size();i++){
        //    cout << temp[i] << endl;
        //}
        for(int i=0;i<temp.size();i++){
            sz += temp[i].size();
        }

        sz = (2*sz)/cnt;//gets the size of the answer
        szvec.push_back(sz);//saves the size of the answer set by set
        sort(temp.begin(),temp.end(),comp);
        //sort the fragments by their size

        strtxt.push_back(temp);//saves a set
        temp.clear();//clear
        sz=0;//clear
        cnt=0;//clear
    }
    
    //cout << "checkpoint" << endl;

    vector<string>ansvec;

    int a=0;
    int b=0;
    int c=0;
    string str1;
    string str2;
    bool check = false;

    for(int i=0;i<n;i++){//for the given number of times
        c = szvec[i];//this is the length of the answer of i times
        for(int j=0;j<strtxt[i].size();j++){
            a = strtxt[i][j].size();
            for(int k=j+1;k<strtxt[i].size();k++){
                str1 =strtxt[i][j] + strtxt[i][k];
                //match two fragments in A+B order

                str2 = strtxt[i][k] + strtxt[i][j];
                //match two fragments in opposite order, as B+A

                if(a + strtxt[i][k].size()==c){
                    //if the length of a combined fragment
                    //matches the length of the original answer
                    ansvec.push_back(str1);//add them to the ansvec
                    ansvec.push_back(str2);
                    //cout << str1 << endl << str2 << endl;
                }
            }

        }
        sort(ansvec.begin(),ansvec.end());//sort them

        maxi(ansvec);//print out the answer
        ansvec.clear();//clears ansvec
        check=false;//clears check
        cout << endl;//prints blank line under the results 
    }


    return 0;

}




