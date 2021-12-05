#include "Engine.h"

Engine::Engine(string map_path,string score_path){
	cur_map=map_path;
	cur_score=score_path;
	
	//Start ncurses
	initscr();
	//Set color
	if(has_colors()){
		start_color();
		
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2,COLOR_RED,COLOR_BLACK);
		init_pair(3,COLOR_WHITE,COLOR_BLACK);
		init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	}

	curs_set(0);
	noecho();
}

Engine::~Engine(){
	endwin();
	if(potter==NULL){
		delete potter;
	}
	
	if(gnome==NULL){
		delete gnome;
	}
	
	if(traal==NULL){
		delete traal;
	}
}

void Engine::init_game(){
	
	fstream file;
	//Check for map file
	file.open(cur_map);
	if(!file){
		throw 1;
	}
	if(file.is_open()){
		string line;
		while(getline(file,line)){
		map.push_back(line);
		}
	}
	file.close();
	
	//Check for score file
	file.open(cur_score);
	if(!file){
		throw 2;
	}
	file.close();
	
	r=map.size();
	c=map[0].size();
	
	//Game window
	curwin=newwin(r+2,c+15,r-(r/2)+3,1);
	box(curwin,0,0);
	wborder(curwin,' ',' ',' ',' ',' ',' ',' ',' ');
	

	//Title
	title=newwin(r-(r/2),c*2,1,1);
	box(title,0,0);
	mvwprintw(title,(r-(r/2))/2-2,c-5,"GMELE VS BABIS");
	mvwprintw(title,(r-(r/2))/2-1,c-5,"--------------");
	mvwprintw(title,(r-(r/2))/2+1,c-6,"THE FINAL BATTLE");
	mvwprintw(title,(r-(r/2))/2+2,c-6,"----------------");
	
	
	//ScoreBoard
	score=newwin(r+2,c-15,r-(r/2)+3,c+16);
	box(score,0,0);
	mvwprintw(score,1,((c-15)/2)-2,"INFO");
	mvwprintw(score,2,((c-15)/2)-2,"====");
	
	//Highscore screen
	scores=newwin(r*2+4-(r/2),c*2,r-(r/2)+3,1);
	
	//Menu
	menu_win=newwin(r+2,c*2,r-(r/2)+3,1);
	box(menu_win,0,0);
	
	//Win screen
	win=newwin(r*2+4-(r/2),c*2,1,1);
	box(win,0,0);
	wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
}

void Engine::update_game(){
	
	//Refresh Title
	wrefresh(title);
	
	
	//Update info board
	mvwprintw(score,5,((c-15)/2)-7,"===============");
	mvwprintw(score,7,((c-15)/2)-7,"Score: %i",sc);
	mvwprintw(score,9,((c-15)/2)-7,"===============");
	mvwprintw(score,11,((c-15)/2)-7,"Stones: %i/10",stone_cnt);
	mvwprintw(score,13,((c-15)/2)-7,"===============");
	mvwprintw(score,15,((c-15)/2)-7,"Parchment: %i/1",parch);
	wrefresh(score);
	
	//Check for parchment spawn
	if(sc==100 && cnt==0){
		cnt=1;
		do{
			parchmentX=rand()%map[0].size() -1;
			parchmentY=rand()%map.size();
		}while(map[parchmentY][parchmentX]!=' ');
		
		map[parchmentY][parchmentX]=parchment;
	}
	
	//Refresh map
	for(int i=0;i<map.size();i++){
		wattrset(curwin,COLOR_PAIR(3));
		mvwprintw(curwin,i+1,1,map[i].c_str());
		for(int j=0;j<map[0].size();j++){
			//Print the unicode char of block instead of *
			if(map[i][j]=='*'){
				mvwaddch(curwin,i+1,j+1,block);		
			}
			//Print the correct colors for each character
			if(map[i][j]==player){
				mvwchgat(curwin,i+1,j+1,1,COLOR_PAIR(1),1,NULL);
			}
			if(map[i][j]==gn || map[i][j]==tr){
				mvwchgat(curwin,i+1,j+1,1,COLOR_PAIR(2),2,NULL);
			}
			if(map[i][j]==stone || map[i][j]==parchment){
				mvwchgat(curwin,i+1,j+1,1,COLOR_PAIR(4),4,NULL);
			}
		}
			
	}
	
	for(int i=0;i<10;i++){
		map[stoneY[i]][stoneX[i]]=stones[i];
	}
	
	if(sc==100 && cnt==1){
		map[parchmentY][parchmentX]=parchment;
	}
	
	wrefresh(curwin);
}

void Engine::menu(){
	//Update menu win
	wrefresh(menu_win);
	
	string choices[3]={"Start Game","View Highscores","Quit"};
	int choice;
	int highlight=0;
	
	keypad(menu_win,true);
	while(1){
		for(int i=0;i<3;i++){
			if(i==highlight){
				wattron(menu_win,A_REVERSE);
			}
			mvwprintw(menu_win,i-3+(map.size()+2)/2,((map[0].size()*2)/2)-5,choices[i].c_str());
			wattroff(menu_win,A_REVERSE);
		}
		
		choice=wgetch(menu_win);
		switch(choice){
			case KEY_UP:
				highlight--;
				if(highlight==-1){
					highlight=0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight==3){
					highlight=2;
				}
				break;
			default:
				break;
		}
		if(choice==10){
			if(choices[highlight]=="Start Game"){
				run_game=1;
				return;
			}
			if(choices[highlight]=="View Highscores"){
			
				
				keypad(scores,true);
				HiScore h(cur_score);
				int ch;
				while(1){
					mvwprintw(scores,(r)/2 -3,((c*2)/2)-23,"----------------HIGHSCORES---------------");
					mvwprintw(scores,(r)/2-2,((c*2)/2)-23,"-----------------------------------------");
					mvwprintw(scores,(r)/2,((c*2)/2)-23,"Press Enter to Start Game or Escape to quit");
					h.read();
					for(int i=0;i<5;i++){
						mvwprintw(scores,(r)/2 +3+i,((c*2)/2)-15,"%d. %s %d",i+1,h.scores[i].getName(),h.scores[i].getScore());
					}
					
					ch=wgetch(scores);
					if(ch==10){
						run_game=1;
						return;
					}
					if(ch==27){
						return;
					}
					
				}
			}
			if(choices[highlight]=="Quit"){
				return;
			}
		}
	}
}

void Engine::win_menu(){
	
	//Reset Every window
	werase(curwin);
	werase(menu_win);
	werase(title);
	werase(score);
	werase(scores);
	refresh();
	
	//reset all vars
	map.clear();
	run_game=0;
	stone_cnt=0;
	parch=0;
	stones.clear();
	stoneX.clear();
	stoneY.clear();
	
	//Delete objects
	delete potter;
	delete gnome;
	delete traal;
	
	if(eaten==1){
		wrefresh(win);
		wrefresh(title);
		eaten=0;
		keypad(win,true);
		int ch;
		while(1){
			echo();
			mvwprintw(win,(2*r)/2 -3,((c*2)/2)-15,"GAME OVER!!!GMELE BEAT YOU!!!");
			mvwprintw(win,(2*r)/2,((c*2)/2)-25,"Enter your name and then press Enter twice to continue");
			mvwgetstr(win,(2*r)/2+2,((c*2)/2)-15, round_name);
			HiScore h(cur_score);
			h<<round_name<<sc;
			ch=wgetch(win);
			sc=0;
			noecho();
			if(ch==10){
				break;
			}
		}
		
		//Reset win
		werase(win);
		refresh();
	}
	
	//Check is the score is 200 so the winner screen is displayed
	if(sc==200){
		
		wrefresh(win);
		wrefresh(title);
		
		keypad(win,true);
		int ch;
		while(1){
			echo();
			mvwprintw(win,(2*r)/2 -3,((c*2)/2)-15,"CONGRATULATIONS!!!YOU BEAT GMELE!!!");
			mvwprintw(win,(2*r)/2,((c*2)/2)-25,"Enter your name and then press Enter twice to continue");
			mvwgetstr(win,(2*r)/2+2,((c*2)/2)-15, round_name);
			HiScore h(cur_score);
			h<<round_name<<sc;
			ch=wgetch(win);
			sc=0;
			noecho();
			if(ch==10){
				break;
			}
		}
		
		//Reset win
		werase(win);
		refresh();
	}
	
	if(sc!=0){
		sc=0;
	}
	
	//Start again
	Engine::start();
}

void Engine::start(){
	cnt=0;
	Engine::init_game();
	wrefresh(title);

	Engine::spawn();
	
	Engine::menu();
	wrefresh(title);
	
	while(run_game){
			
		//Screen update
		Engine::update_game();
		
		
		//Move player
		player_choice=potter->move();
			
		//Move Gnome
		gnome_choice=gnome->move(playerY,playerX,map);
			

		//Move Traal
		traal_choice=traal->move(playerY,playerX,map);
			
		//Check for player collision
		Engine::check_coll(player_choice,gnome_choice,traal_choice);
			
			
	}
	
}

void Engine::spawn(){
	srand(time(NULL));
	
	//Player spawn
	do{
		playerX=rand()%map[0].size()-1;
		playerY=rand()%map.size();
	}
	while(map[playerY][playerX]!=' ');
	
	map[playerY][playerX]=player;
	//Create Player
	potter= new Potter(curwin,player,playerX,playerY);
	
	//Gnome spawn	
	do{
		gnomeX=rand()%map[0].size()-1;
		gnomeY=rand()%map.size();
	}
	while(map[gnomeY][gnomeX]!=' ');
	
	map[gnomeY][gnomeX]=gn;
	//Create Gnome
	gnome = new Gnome(curwin,gn,gnomeX,gnomeY);
	
	//Traal spawn	
	do{
		traalX=rand()%map[0].size()-1;
		traalY=rand()%map.size();
	}
	while(map[traalY][traalX]!=' ');
	
	map[traalY][traalX]=tr;
	//Create Traal
	traal = new Traal(curwin,tr,traalX,traalY);
	
	//Stones spawn
	for(int i=0;i<10;i++){
		stones.push_back(stone);
		stoneX.push_back(rand()%map[0].size()-1);
		stoneY.push_back(rand()%map.size());			
			
		while(map[stoneY[i]][stoneX[i]]!=' '){
			stoneX[i]=rand()%map[0].size()-1;
			stoneY[i]=rand()%map.size();
		}
		
		map[stoneY[i]][stoneX[i]]=stone;
	}
	
}

void Engine::check_coll(int player_choice,int gnome_choice,int traal_choice){
		
		Engine::check_player_coll(player_choice);
		Engine::check_gnome_coll(gnome_choice);
		Engine::check_traal_coll(traal_choice);
	
}

void Engine::check_player_coll(int choice){
	//Check for right arrow key
		if(choice==KEY_RIGHT){
			map[playerY][playerX]=' ';
			playerX++;
			
			if(map[playerY][playerX]=='*')
			{	
				playerX--;
			}
			if(map[playerY][playerX]==stone)
			{	
				sc+=10;
				stone_cnt+=1;
				
				for(int i=0;i<10;i++){
					if(stoneY[i]==playerY && stoneX[i]==playerX){
						stones[i]=' ';
						
					}
				}
			}
			if(map[playerY][playerX]==parchment)
			{	
				sc+=100;
				parch+=1;
				Engine::win_menu();
			}
	
			map[playerY][playerX]=player;
			potter->setX(playerX);
		}

		//Check for left arrow key
		if(choice==KEY_LEFT){
			map[playerY][playerX]=' ';
			playerX--;
			
			if(map[playerY][playerX]=='*')
			{	
				playerX++;
			}
			if(map[playerY][playerX]==stone)
			{	
				sc+=10;
				stone_cnt+=1;
				for(int i=0;i<10;i++){
					if(stoneY[i]==playerY && stoneX[i]==playerX){
						stones[i]=' ';
				
					}
				}
			}
			if(map[playerY][playerX]==parchment)
			{	
				sc+=100;
				parch+=1;
				Engine::win_menu();
			}
			map[playerY][playerX]=player;
			potter->setX(playerX);
		}

		//Check for up arrow key
		if(choice==KEY_UP){
			map[playerY][playerX]=' ';
			playerY--;
			
			if(map[playerY][playerX]=='*')
			{	
				playerY++;
			}
			if(map[playerY][playerX]==stone)
			{	
				sc+=10;
				stone_cnt+=1;
				for(int i=0;i<10;i++){
					if(stoneY[i]==playerY && stoneX[i]==playerX){
						stones[i]=' ';
						
					}
				}
			}
			if(map[playerY][playerX]==parchment)
			{	
				sc+=100;
				parch+=1;
				Engine::win_menu();
			}
			map[playerY][playerX]=player;
			potter->setY(playerY);
		}

		//Check for down arrow key
		if(choice==KEY_DOWN){
			map[playerY][playerX]=' ';
			playerY++;
			
			if(map[playerY][playerX]=='*')
			{	
				playerY--;
			}
			if(map[playerY][playerX]==stone)
			{	
				sc+=10;
				stone_cnt+=1;
				for(int i=0;i<10;i++){
					if(stoneY[i]==playerY && stoneX[i]==playerX){
						stones[i]=' ';
						
					}
				}
			}
			if(map[playerY][playerX]==parchment)
			{	
				sc+=100;
				parch+=1;
				Engine::win_menu();
			}
			map[playerY][playerX]=player;
			potter->setY(playerY);
		}
			
		//Escape check
		if(choice==27){
			Engine::win_menu();	
		}
}

void Engine::check_gnome_coll(int choice){
	
	//Down Movement
	if(choice==0){
		
		//Update empty space
		map[gnomeY][gnomeX]=' ';
		gnomeY++;
		
		
		//Check for wall collition
		if(map[gnomeY][gnomeX]=='*'){
			gnomeY--;
		}
		
			///////
		if(map[gnomeY][gnomeX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
			
		gnome->setY(gnomeY);
		map[gnomeY][gnomeX]=gn;
		return;
	}
	
	//Up Movement
	if(choice==1){
		
		//Update empty space
		map[gnomeY][gnomeX]=' ';
		gnomeY--;
		
		//Check for wall
		if(map[gnomeY][gnomeX]=='*'){
			gnomeY++;
		}
		
		///////
		if(map[gnomeY][gnomeX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
		
		gnome->setY(gnomeY);
		map[gnomeY][gnomeX]=gn;
		return;
	}
	
	
	//Left Movement
	if(choice==2){
		
		//Update empty space
		map[gnomeY][gnomeX]=' ';
		gnomeX--;
		
		//Check for wall
		if(map[gnomeY][gnomeX]=='*'){
			gnomeX++;
		}
		
		///////
		if(map[gnomeY][gnomeX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
		
		gnome->setX(gnomeX);
		map[gnomeY][gnomeX]=gn;
		return;
	
	}
	
	//Right Movement
	if(choice==3){
		
		//Update empty space
		map[gnomeY][gnomeX]=' ';
		gnomeX++;
		 
		
		//Check for wall
		if(map[gnomeY][gnomeX]=='*'){
			gnomeX--;
			 
		}
		
		///////
		if(map[gnomeY][gnomeX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
		
		gnome->setX(gnomeX);
		map[gnomeY][gnomeX]=gn;
		return;
	
	}
	
}

void Engine::check_traal_coll(int choice){
	
//Down Movement
	if(choice==0){
		
		//Update empty space
		map[traalY][traalX]=' ';
		traalY++;
		
		
		//Check for wall collition
		if(map[traalY][traalX]=='*'){
			traalY--;
		}
		
			///////
		if(map[traalY][traalX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
			
		traal->setY(traalY);
		map[traalY][traalX]=tr;
		return;
	}
	
	//Up Movement
	if(choice==1){
		
		//Update empty space
		map[traalY][traalX]=' ';
		traalY--;
		
		//Check for wall
		if(map[traalY][traalX]=='*'){
			traalY++;
		}
	///////
		if(map[traalY][traalX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
			
		traal->setY(traalY);
		map[traalY][traalX]=tr;
		return;
	}
	
	
	//Left Movement
	if(choice==2){
		
		//Update empty space
		map[traalY][traalX]=' ';
		traalX--;
		
		//Check for wall
		if(map[traalY][traalX]=='*'){
			traalX++;
		}
	///////
		if(map[traalY][traalX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
			
		traal->setX(traalX);
		map[traalY][traalX]=tr;
		return;
	
	}
	
	//Right Movement
	if(choice==3){
		
		//Update empty space
		map[traalY][traalX]=' ';
		traalX++;
		 
		
		//Check for wall
		if(map[traalY][traalX]=='*'){
			traalX--;
			 
		}
	///////
		if(map[traalY][traalX]==player)
		{	
			eaten=1;
			Engine::win_menu();
		}/////////
			
		traal->setX(traalX);
		map[traalY][traalX]=tr;
		return;
	
	}
	
}

		
		
		
		
		
		
		
		
		
		
