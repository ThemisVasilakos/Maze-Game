#ifndef _HISCORE_H
#define _HISCORE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Score.h"
using namespace std;

class HiScore{

	private:
		string score_path;
		int score;
		char name[10];
		const int size=5;
		//vector<Score> scores;
	public:
		vector<Score> scores;
		HiScore(string score_path);
		
		void setName(char name[10]);
		void setScore(int score);
		void write();
		void read();
	
		friend HiScore &operator<<(HiScore &left,char new_name[10]);
		friend HiScore &operator<<(HiScore &left,int sc);
};

#endif