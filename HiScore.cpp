#include "HiScore.h"

HiScore::HiScore(string score_path){
	this->score_path=score_path;
	Score tmp;
	
	for(int i=0;i<size;i++){
		scores.push_back(tmp);
	}
			
	ifstream file;
	
	
	file.open(score_path,ios::binary | ios::in);
	if(!file){
		throw 2;
	}
		
	for(int i=0;i<size;i++){
		file.read((char*)&scores[i],sizeof(Score));
	}
		
	file.close();
	
}

void HiScore::setName(char name[10]){
	strcpy(this->name,name);
}

void HiScore::setScore(int score){
	this->score=score;
}

void HiScore::write(){
	Score tmp;
	
	//Check if current score must enter the highscores
	for(int i=5;i>0;i--){
		if(scores[i].score<=this->score){
			tmp.score=this->score;
			strcpy(tmp.name,this->name);
			scores.erase(scores.end());
			scores.push_back(tmp);
			break;
		}
	}
	
	//Bubble Short
	for(int i=0;i<4;i++){
		for(int j=0;j<4-i;j++){
			if(scores[j].getScore()<scores[j+1].getScore()){
				tmp=scores[j];
				scores[j]=scores[j+1];
				scores[j+1]=tmp;
			}
		}
	}
			
	fstream file;
	
	file.open(score_path,ios::binary | ios::out);
	if(!file){
		throw 2;
	}
		
	for(int i=0;i<size;i++){
		file.write((char*)&scores[i],sizeof(Score));
	}
		
	file.close();
	
	
}

void HiScore::read(){
	ifstream file;
	
	file.open(score_path,ios::binary | ios::in);
	if(!file){
		throw 2;
	}
		
	for(int i=0;i<size;i++){
		file.read((char*)&scores[i],sizeof(Score));
	}
			
	file.close();
	
	
}

HiScore &operator<<(HiScore &left,char new_name[10]){
	left.setName(new_name);
	return left;
}

HiScore &operator<<(HiScore &left,int sc){
	left.setScore(sc);
	
	left.write();
			
	return left;
}




