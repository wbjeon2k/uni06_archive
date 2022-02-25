#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

int main(){
    
    vector< vector<string> >ans;
    string tmp1;
    char tmp[145];
    char txt;
    getline(cin,tmp1);
    int n=0;
    n = tmp1[0]-'0';
    getline(cin,tmp1);
    for(int i=0;i<n;i++){
        vector<string>temp;
        //getline(cin,tmp1);
        while(getline(cin,tmp1)){
            if (tmp1 == ""){
               // ans.push_back("\n");
                break;
            }
            temp.push_back(tmp1);
        }
        ans.push_back(temp);
    }

    for(int i=0;i<ans[1].size();i++){
        cout << ans[1][i]<<endl;
    }
    for(int i=0;i<ans[1].size();i++){
        cout << ans[1][i].size() << endl;
    }
    cout << "clear"<<endl;
    return 0;

}
