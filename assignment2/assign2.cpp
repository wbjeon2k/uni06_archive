//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

void getinput(int n, vector<int>&ansvec1, vector<int>&ansvec2) {
	vector<int>stemp;
	vector<int>etemp;
	int shh, smm;
	int ehh, emm;
	int startmin, endmin;
	etemp.push_back(600);
	for (int i = 0;i < n;i++) {
		
		string blank;
		scanf("%d:%d", &shh, &smm);
		scanf("%d:%d", &ehh, &emm);
		startmin = shh * 60 + smm;
		endmin = ehh * 60 + emm;
		stemp.push_back(startmin);
		etemp.push_back(endmin);
		getline(cin, blank);

	}
	stemp.push_back(1080);
	sort(stemp.begin(), stemp.end());
	sort(etemp.begin(), etemp.end());
	
	int max = stemp[0]-etemp[0];
	int maxnum = 0;
	int tmp;
	for (int i = 1;i < n + 1;i++) {
		tmp = stemp[i] - etemp[i];
		if (tmp > max) {
			max = tmp;
			maxnum = i;
		}
	}

	ansvec1.push_back(max);
	ansvec2.push_back(etemp[maxnum]);
}

int main() {

	string num;
	int n;
	vector<int >timestart;
	vector<int>interval;
	

	while (true) {
		getline(cin, num);
		if (num == "") {
			break;
		}
		n = num[0] - '0';
		getinput(n,interval,timestart);
	}

	for (int i = 0;i < interval.size();i++) {
		if (interval[i] >= 60) {
			int hour;
			int min;
			hour = timestart[i] / 60;
			min = timestart[i] % 60;
			printf("Day #%d: the longest nap starts at %d:%02d and will last for %d hours and %d minutes.",
				    i+1, hour, min, interval[i]/60, interval[i]%60);
		}
		else {
			int hour;
			int min;
			min = timestart[i] % 60;
			hour = timestart[i] / 60;
			printf("Day #%d: the longest nap starts at %d:%02d and will last for %d minutes.",
				    i+1, hour, min, interval[i]);
		}
		printf("\n");
	}

	return 0;

}
