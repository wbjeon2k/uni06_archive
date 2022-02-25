#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct card {//a datatype for a card
	char suit;
	int value;

	card(string input) {//generates a card
		suit = input[1];


		if (input[0] == 'A') {
			value = 14;
		}
		else if (input[0] == 'K') {
			value = 13;
		}
		else if (input[0] == 'Q') {
			value = 12;
		}
		else if (input[0] == 'J') {
			value = 11;
		}
		else if (input[0] == 'T') {
			value = 10;
		}
		else {
			value = input[0] - '0';
		}
	}
};

bool comp(const card& a, const card& b) {//a comparator for card datatype
	if (a.value > b.value) {//if a card's value is bigger, return true
		return true;
	}
	else {
		return false;
	}
}

bool intcomp(pair<int, int>a, pair<int, int>b) {//a comparator for pair datatypes
	if (a.first > b.first) {//value of first is bigger, then return true
		return true;
	}
	else {
		return false;
	}
}

bool suitcomp(const card& a, const card& b) {//comparator to compair suit of card
	int asuit = 0;
	int bsuit = 0;
	asuit = a.suit - 'A';
	bsuit = b.suit - 'B';

	if (a.suit > b.suit) {
		return true;
	}
	else {
		return false;
	}
}

class hand {//datatype for a hand
private:
	vector<card> handlist;//list of 5 cards
	int status[9];//total 9 game status, starting from high card, ends with straight flush
	vector< pair<int, int> >histo;//histogram of counts, how many values are each counted (total 14 cases)
	int maxstatus;//saves the maximum game status
public:
	hand(vector<card>&list) {//generates a hand

		for (int i = 0;i < 5;i++) {//copies the hand list
			this->handlist.push_back(list[i]);
		}
		for (int i = 0;i < 9;i++) {//initialize status
			this->status[i] = 0;
		}
		for (int i = 0;i < 13;i++) {//initialize histo for every 14 values
			histo.push_back(*new pair<int, int>);
			this->histo[i].first = 0;
			this->histo[i].second = i + 2;
		}
		for (int i = 0;i < 5;i++) {//counts how many times a value is selected
			this->histo[this->handlist[i].value - 2].first += 1;
		}

		sort(histo.begin(), histo.end(), intcomp);//sort the histogram by the descending order

	}

	int strflush(vector<card>&list);//function to evaluate straight flush
	int flush(vector<card>&list);//function to evaluate flush
	int straight(vector<card>&list);//function to evaluate straight


	void printhand() {//prints hand
		for (int i = 0;i < 5;i++) {
			cout << this->handlist[i].suit << this->handlist[i].value << endl;
		}
	}

	void printstatus() {//prints game status from high card to straight flush
		for (int i = 0;i < 9;i++) {
			if (this->status[i] == 0) {
				cout << "0" << endl;
			}
			else if (this->status[i] == 1) {
				cout << "1" << endl;
			}
			else {
				cout << "R" << endl;
			}
		}
	}

	void check() {//evaluate the hand

		if (histo[0].first == 4) {
			//the only case for four cards
			//aaaa*
			status[7] = 1;
		}
		else if (histo[0].first == 3) {//full house or three of a kind
			if (histo[1].first == 2) {//aaabb
				status[6] = 1;
			}
			else {//aaabc
				status[3] = 1;
			}
		}
		else if (histo[0].first == 2) {//pair or two pair
			if (histo[1].first == 2) {//aa bb *
				status[2] = 1;
			}
			else { //aa b c d
				status[1] = 1;
			}
		}
		else {//only case for high card
			status[0] = this->handlist[0].value;
		}

		status[8] = strflush(handlist);
		status[4] = straight(handlist);
		status[5] = flush(handlist);

		int m = 0;
		for (int i = 0;i < 9;i++) {//finds the maximum game status
			if (this->status[i] == 1) {
				m = i + 1;
			}
		}
		this->maxstatus = m;

	}

	friend bool operator<(const hand&a, const hand&b);//operator overloads
	friend bool operator>(const hand&a, const hand&b);//operator overloads
	friend int samehandcomp(const hand&a, const hand&b);//compares hand when the game status is same


};


bool operator<(const hand&a, const hand&b) {//return true when maximum game status is smaller
	return (a.maxstatus < b.maxstatus);
}

bool operator>(const hand&a, const hand&b) {//return true when maximum game status is larger
	return (a.maxstatus > b.maxstatus);
}

int hand::strflush(vector<card>&list) {
	int chk = 0;

	for (int i = 0;i < 5;i++) {//when five values are consecutive && suits are same
		if (list[0].suit != list[i].suit) {
			chk = 1;
		}
		if (list[i].value != list[0].value - i) {
			chk = 1;
		}
	}

	if (chk == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int hand::flush(vector<card>&list) {
	int chk = 0;

	for (int i = 0;i < 5;i++) {//when five suits are same
		if (list[0].suit != list[i].suit) {
			chk = 1;
		}
	}

	if (chk == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int hand::straight(vector<card>&list) {
	int chk = 0;

	for (int i = 0;i < 5;i++) {//when five values are consecutive
		if (list[i].value != list[0].value - i) {
			chk = 1;
		}
	}

	if (chk == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int handcomp(const hand&a, const hand&b) {
	if (a > b) {//if a wins with bigger game status
		return 1;
	}
	else if (b > a) {//if b wins with bigger game status
		return -1;
	}
	else {
		//if a and b have same game status
		return samehandcomp(a, b);
	}
}

int samehandcomp(const hand&a, const hand&b) {
	int a1 = 0;
	int b1 = 0;
	if (a.status[0] != 0 && b.status[0] != 0) {//when we have to evaluate with high card
		for (int i = 0;i < 5;i++) {
			if (a.handlist[i].value > b.handlist[i].value) {
				return 1;
			}
			else if (a.handlist[i].value < b.handlist[i].value) {
				return -1;
			}
		}
	}
	else {
		for (int i = 0;i < 13;i++) {
			a1 = a.histo[i].second;
			b1 = b.histo[i].second;
			if (a1 > b1) {
				return 1;
			}
			else if (a1 < b1) {
				return -1;
			}
		}
	}
	return 0;
}


int main() {
	string temp;
	string tmp1;
	string tmp2;
	stringstream ss;
	vector<card> blackhand;
	vector<card> whitehand;

	while (true) {
		
		getline(cin, temp);
		ss.str(temp);
		tmp1 = "";
		tmp2 = "";
		if (temp == "") {
			break;
		}
		else {
			
			for (int i = 0;i < 5;i++) {
				ss >> tmp1;
				
				blackhand.push_back(*new card(tmp1));
			}
			sort(blackhand.begin(), blackhand.end(), comp);




			for (int i = 0;i < 5;i++) {
				ss >> tmp1;
				
				whitehand.push_back(*new card(tmp1));
			}
			sort(whitehand.begin(), whitehand.end(), comp);

			hand black(blackhand);
			hand white(whitehand);

			black.check();
			white.check();


			int w = handcomp(black, white);

			if (w == 1) {
				cout << "Black wins." << endl;
			}
			else if (w == -1) {
				cout << "White wins." << endl;
			}
			else {
				cout << "Tie." << endl;
			}


			blackhand.clear();
			whitehand.clear();
			ss.str("");
			ss.clear();
		}
	}
	return 0;
}
