#ifndef _ENGINE_H
#define _ENGINE_H

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"
#include "HiScore.h"

//Defining the unicode character for block
#define block (char)'\u2588'
using namespace std;

class Engine{
	private:
		//Windows and boxes
		WINDOW *curwin;
		WINDOW *title;
		WINDOW *score;
		WINDOW *menu_win;
		WINDOW *win;
		WINDOW *scores;

		vector<string> map;
	
		//Player 
		Potter *potter;
		char player='B';
		int playerX;
		int playerY;		
		
		//Gnome
		Gnome *gnome;
		char gn='G';
		int gnomeX;
		int gnomeY;
	
		//Traal
		Traal *traal;
		char tr='T';
		int traalX;
		int traalY;
	
		//string hiscores;
		string cur_map;
		string cur_score;
		char round_name[10];
		int round_score;
		int r,c;
		
		//score,stones,parchment vars
		int sc=0;
		int stone_cnt=0;
		int parch=0;
	
		char parchment='p';
		int parchmentX;
		int parchmentY;
	
		char stone='s';
		vector<char> stones;
		vector<int> stoneX;
		vector<int> stoneY;
	
		//Game loop check vars
		int run_game=0;
		int player_choice;
		int gnome_choice;
		int traal_choice;
		int cnt;
		int eaten=0;
	
	public:
		//Constructor
		Engine(string map_path,string score_path);
		//Destructor
		~Engine();
		
		//init windows methods
		void init_game();
	
		void update_game();
		void menu();
		void win_menu();
	
		//game methods
		void start_game();
		void start();
		void spawn();
	
		//Collition methods
		void check_coll(int player_choice,int gnome_choice,int traal_choice);
		void check_player_coll(int choice);
		void check_gnome_coll(int choice);
		void check_traal_coll(int choice);
};


#endif