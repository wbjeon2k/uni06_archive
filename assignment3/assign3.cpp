//#define CRT_NO_SECURE_WARNINGS

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct sublog {//datatype for input

	int teamnum;//contestant number
	int probnum;//problem number
	int solvmin;//submitted minute
	char status;//one of C,I,R,U,E

};

struct teamlog {
	int teamnum;//contestant number
	int problem[10];//solved status from problem 1 to 9
	int penalty[10];//penalty time for each problem
	int pentime;//total penalty time
	int probn;//total solved problems

	teamlog(int n) {//consturctor for a specific team number
		//initialize a variant
		teamnum = n;
		probn = 0;
		pentime = 0;
		for (int i = 0;i < 10;i++) {
			problem[i] = 0;
			penalty[i] = 0;
		}
	}

};

void printlog(sublog &s) {//used to test some submit logs
	cout << s.teamnum << endl;
	cout << s.probnum << endl;
	cout << s.solvmin << endl;
	cout << s.status << endl;
}

sublog processinput(string &input) {//process string input into sublog datatype
	sublog templog;
	stringstream ss;
	ss.str(input);
	//gets input separated by space blanks
	ss >> templog.teamnum;
	ss >> templog.probnum;
	ss >> templog.solvmin;
	ss >> templog.status;

	//printlog(templog);

	return templog;
}

void anscheck(teamlog &t, const sublog &s) {//checks the submit attempt
	if (t.problem[s.probnum] == 1) {//if the problem has solved, pass it away
		return;
	}
	
	if (s.status == 'C') {//if the submit is correct
		t.probn++;//add 1 to total solved problem
		t.problem[s.probnum] = 1;//check the problem is solved
		t.penalty[s.probnum] += s.solvmin;//add penalty time the solved time
		//cout << t.penalty[s.probnum] << endl;
	}
	else if (s.status == 'I') {//if the submit is wrong
		t.penalty[s.probnum] += 20;//add 20min to the problem number
	}
}

bool comp(const teamlog &a, const teamlog &b) {
	//this is a boolean function which compares two teamlog variables
	//this is used in the sort function below sort(a,b,comp);
	if (a.probn > b.probn) {//returns true when total solved problem is bigger
		return true;
	}
	else if (a.probn == b.probn && a.pentime < b.pentime) {//with less penalty time
		return true;
	}
	else if (a.probn == b.probn && a.pentime == b.pentime && a.teamnum < b.teamnum) {//in team number order
		return true;
	}
	else {
		return false;
	}
		
}


int main() {

	//vector < vector <teamlog > > inputlist;

	string n1;
	getline(cin, n1);

	int n = 0;
	n = n1[0] - '0';

	string temp;
	getline(cin, n1);

	for (int i = 0;i < n;i++) {
		int teamarr[102];// an array for a maximum 100 teams
		for (int i = 0;i < 102;i++) {
			teamarr[i] = -1;
		}
		sublog tmp;

		vector<teamlog>templog;

		while (true) {//gets input
			getline(cin, temp);
			if (temp == "") {//get input until blank
				break;
			}
			else {
				tmp = processinput(temp);
				if (teamarr[tmp.teamnum] == -1) {
					//if the submitted attempt is the first ever to a problem
					
					templog.push_back(*new teamlog(tmp.teamnum));
					teamarr[tmp.teamnum] = templog.size() - 1;
					//gives the static address to the specific team number
				}
				anscheck(templog[teamarr[tmp.teamnum]], tmp);
			}
		}
		//cout << "check1" << endl;
		//int k = templog.size();
		for (int i = 0; i < templog.size(); i++) {//adds total penalty time
			templog[i].pentime = 0;
			for (int j = 1;j < 10;j++) {
				
				if (templog[i].problem[j] == 1) {//if the problem is solved, add penalty time
					templog[i].pentime += templog[i].penalty[j];
				}
				
			}
		}

		
		//cout << "check2" << endl;
		sort(templog.begin(),templog.end(),comp);//sort it by the given criterion
		//cout << "check3" << endl;
		for (int i = 0; i < templog.size(); i++) {//print it by order
			printf("%d %d %d\n", templog[i].teamnum, templog[i].probn, templog[i].pentime);
		}
		
		cout << endl;

	}

	return 0;
}

