/*Aditya Panda
Roll CS1723
Assignment 4
Prog 2
Snake Ladder Game*/
#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <cstring>
#include <cmath>
#include <ctime>
#include <sys/time.h>
using namespace std;
//bool L_Validity_Check (map <int, int> ladder);
//bool S_Validity_Check (map <int, int> snake);
int main(int argc, char *argv[]) {

	if (argc != 3) {
		cout << "INSUFFICIENT ARGUMENT" << endl;
		//cout << "Input format: Program Name <input file> <No. of Players>" << endl;
		return 0;
	}
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile) {
		cout << "INPUT FILE CANNOT BE OPENED" << endl;
		return 0;
	}
	map <int, int> snake,ladder;
	int no_Snake = 0, no_Ladder = 0, n1, n2, sum = 0, x, d;
	string line;

	x = atoi(argv[2]);
	if ((x > 6) || (x < 2)) {
		cout << "NO OF PLAYERS CANNOT BE OUTSIDE [2,6]" << endl;
		return 0;
	}
	getline (inFile,line);
	istringstream is_Snake (line);
	while (is_Snake >> n1) {
		if (is_Snake >> n2) {
			snake.insert(pair <int, int> (n1, n2));
			no_Snake++ ;
		}
	}
	getline (inFile,line);
	istringstream is_Ladder (line);
	while (is_Ladder >> n1) {
		if (is_Ladder >> n2) {
			ladder.insert(pair <int, int> (n1, n2));
			no_Ladder++ ;
		}}
		inFile.close();
	bool tmp = true;
	map <int, int> :: iterator i;
	for (i = snake.begin(); i != snake.end(); i++) {
		if ((i->first <= i->second) || (i->first > 100) || 
			(i->second > 100) || (i->first <= 0) || (i->second <= 0)) {
			tmp = false;
			cout << "ERROR IN SNAKE CONFIGURATION" << endl;
			return 0;
		}}			
	tmp = true;
	map <int, int> :: iterator j;
	for (j = ladder.begin(); j != ladder.end(); j++) {
		if ((j->first >= j->second) || (j->first > 100) || 
			(j->second > 100) || (j->first <= 0) || (j->second <= 0)){
			tmp = false;
			cout << "ERROR IN LADDER% CONFIGURATION" << endl;
			return 0;}}			
	 tmp = true;
	int n;
	vector <int> alpha;
	map <int, int> :: iterator p, q, r;
	vector <int> :: iterator s;
	p = ladder.begin();
	while ((p != ladder.end()) && (tmp)) {
	alpha.push_back(p->first);
	q = snake.find(p->second);
	r = ladder.find(p->second);
		while ((q != snake.end()) || (r != ladder.end())) {
			if (q != snake.end()) {
				n = q->second;
				s = find(alpha.begin(), alpha.end(), n);
				if (s != alpha.end()) {
					tmp = false;
					break;}
				else {
					alpha.push_back(n);
					q = snake.find(n);
					r = ladder.find(n);	}	}			
			if (r != ladder.end()) {
				n = r->second;
				s = find(alpha.begin(), alpha.end(), n);
				if (s != alpha.end()) {
					tmp = false;
					break;	}
				else {
					alpha.push_back(n);
					q = snake.find(n);
					r = ladder.find(n);	}}}
		p++;
		alpha.clear();}
	if (!tmp){
	cout << "LOOP DETECTED IN BOARD" << endl; 
	return 0;}		
	tmp = true;
	int m;
	map <int, int> :: iterator adi1,adi2;
	for (adi1 = snake.begin(); adi1 != snake.end(); adi1++) {
		m = adi1->first;
		adi2 = ladder.find(m);
		if (adi2 != ladder.end()) {
			tmp = false;
			cout << "THERE IS ATLEST ONE CELL WITH LOWER END OF LADDER AND UPPER END OF SNAKE" << endl;
			return 0;}}
	vector <int> plrs(x);
	bool winflag = false;
	while (!winflag) {
		for (int i=0; i < x; i++) {
			cout << "PLAYER " <<  i+1 << " (CELL " << plrs[i] << "): ";
    timeval tx;
    gettimeofday(&tx, NULL);
    srand(tx.tv_usec * tx.tv_sec);
    d = rand() % 6 + 1;
	//timeval t;
	//gettimeofday(&t, NULL);
	//srand(t.tv_usec * t.tv_sec);
	//d=(rand()%6 + 1);
			//d = die_roll();
			if ((plrs[i] == 0) && (d != 1)) {
				cout << "ROLLS " << d << ", NO MOVEMENT." << endl;
				continue;
			}
			if ((plrs[i] + d) > 100) {
				cout << "ROLLS " << d << ", NO MOVEMENT." << endl;
				continue;
			}
			if ((plrs[i]+d) == 100) {
				cout << "ROLLS " << d << ", WINS." << endl;
				winflag = true;
				cout << "GAME OVER" << endl;
				break;
			}
			plrs[i] += d;
			cout << "ROLLS " << d << ", MOVES TO CELLS " << plrs[i];

			map <int, int> :: iterator it1, it2;
			p = snake.find(plrs[i]);
			q = ladder.find(plrs[i]);

			while ((p != snake.end()) || (q != ladder.end())) {
				if (p != snake.end()) {
					plrs[i] = p->second;
					cout << ", SLIDES DOWN THROUGH SNAKE TO CELL " << plrs[i];
					p = snake.find(plrs[i]);
					q = ladder.find(plrs[i]);
				}
				if (q != ladder.end()) {
					plrs[i] = q->second;
					cout << ", CLIMBS UP LADDER TO CELL " << plrs[i];
					p = snake.find(plrs[i]);
					q = ladder.find(plrs[i]);
				}
			}
			cout << "." << endl;
		}
	}
	
	return 0;
}


/*
using namespace std;
typedef pair<int,int> point;

      switch ( c ){
           case 'A':cout << "No Movement";  break;
           case 'D':cout << "MOVES TO " << plrs[pl_no];  break;
           case 'I':cout << "CLIMBS UP DUE TO LADDER " << plrs[pl_no];  break;
           case 'T':cout << "SLIPS DOWN DUE TO SNAKES MOUTH " << plrs[pl_no];  break;
           default :cout << " No Movemnent";}}

int die_outcome_generator()
{
	int lo=1;int hi=6;
    int n = hi - lo + 1;
    int i = rand() % n;
    if (i < 0) i = -i;
    return lo + i;
}*/
