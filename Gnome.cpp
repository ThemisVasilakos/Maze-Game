#include "Gnome.h"

Gnome::Gnome(WINDOW *win,char c,int x,int y):
	Moving(win,c,x,y)
{
	
}

int Gnome::move(int potter_y,int potter_x,const vector<string> &map){
	
	vector<double> choice;
	
	double dist0=sqrt(pow(potter_x-x,2)+pow(potter_y-(y+1),2));
	double dist1=sqrt(pow(potter_x-x,2)+pow(potter_y-(y-1),2));
	double dist2=sqrt(pow(potter_x-(x-1),2)+pow(potter_y-y,2));
	double dist3=sqrt(pow(potter_x-(x+1),2)+pow(potter_y-y,2));	
	
	if(map[y+1][x]!='*'){
		choice.push_back(dist0);
	}
	if(map[y-1][x]!='*'){
		choice.push_back(dist1);
	}
	if(map[y][x-1]!='*'){
		choice.push_back(dist2);
	}
	if(map[y][x+1]!='*'){
		choice.push_back(dist3);
	}
	
	float tmp;
	for(int i=0;i<choice.size()-1;i++){
		for(int j=0;j<choice.size()-1-i;j++){
			if(choice[j]<choice[j+1]){
				tmp=choice[j];
				choice[j]=choice[j+1];
				choice[j+1]=tmp;
			}
		}
	}

	int n=choice.size()-1;
	if(choice[n]==dist0){
		return 0;
	}
	if(choice[n]==dist1){
		return 1;
	}
	if(choice[n]==dist2){
		return 2;
	}
	if(choice[n]==dist3){
		return 3;
	}
	//////
	if(map[y+1][x]!='*'){
		return 0;
	}
	if(map[y-1][x]!='*'){
		return 1;
	}
	if(map[y][x-1]!='*'){
		return 2;
	}
	if(map[y][x+1]!='*'){
		return 3;
	}
	
	return 5;
}














