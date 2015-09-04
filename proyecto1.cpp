#include <ncurses.h>
#include <ctime>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace std;

int menu();
vector<string> Text_Read(vector<string>,int);
vector<char> Word_Selec(vector<string>,vector<char>);
char** createMatrix(int);
void fillMatrix(char**,int);
void head(char**,int);
void body(char**,int);
void leg1(char**,int);
void leg2(char**,int);
void arm1(char**,int);
void arm2(char**,int);
void printMatrix(char**,int);
void print_array(char[]);
void print_array2(char*, int);
char* fillArray(int);
void deleteMatrix(char***,int);
void deleteArray(char*); 

int main(int argc, char** argv){
	initscr();
	srand (time(0));

	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	attron(COLOR_PAIR(1));

	int opt;
	vector<string> words;
	vector<char> guess_word;
	vector<char> used_word;
	int const SIZE=30;
	bool win=true;
	bool end=true;
	char letter;
	char** hangman=NULL;
	hangman=createMatrix(SIZE);
	fillMatrix(hangman,SIZE);
	int life=6;
	int cont2=0;
	do{
		refresh();
			opt=menu();
		clear();
	}while(!(opt>0 && !opt<4));

	words=Text_Read(words,opt);
	guess_word=Word_Selec(words,guess_word);

	char* empty=NULL;
	empty=fillArray(guess_word.size());
	char abc[] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

	do{
		refresh();
		printMatrix(hangman,SIZE);
		printw("\n");
		move(14,50);
		print_array(abc);
		printw("\n");
		move(15,50);
		print_array2(empty,guess_word.size());
		//printw("%d",cont2);
		printw("\n");
		letter=' ';
		move(16,50);
		scanw("%c",&letter);
		letter=tolower(letter);
		while(letter==' '){
			move(16,50);
			printw("Error input correct character");
			printw("\n");
			letter=' ';
			move(17,50);
			scanw("%c",&letter);
			letter=tolower(letter);
		}

		win=true;
		for(int i=0;i<used_word.size();i++){
			while(letter==used_word[i]){
				move(16,50);	
				printw("You have used this letter");
				printw("\n");
				letter=' ';
				move(17,50);
				scanw("%c",&letter);
				letter=tolower(letter);
			}
			for(int j=0;j<27;j++){
				if(letter==abc[j]){
					abc[j]='X';
				}
			}
		}
		used_word.push_back(letter);

		clear();
		int cont=0;
		for(int i=0;i<guess_word.size();i++){
			if(letter==guess_word[i]){
				empty[i]=letter;
				cont++;
			}
		}
		if(cont>0){
			win=true;
		}else{
			win=false;
		}
		
		if(win==true){
			refresh();
			printMatrix(hangman,SIZE);
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}else if(life==6 && win==false){
			refresh();
			head(hangman,SIZE);
			printMatrix(hangman,SIZE);
			life--;
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}else if(life==5 && win==false){
			refresh();
			head(hangman,SIZE);
			body(hangman,SIZE);
			printMatrix(hangman,SIZE);
			life--;
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}else if(life==4 && win==false){
			refresh();
			head(hangman,SIZE);
			body(hangman,SIZE);
			leg1(hangman,SIZE);
			printMatrix(hangman,SIZE);
			life--;
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}else if(life==3 && win==false){
			refresh();
			head(hangman,SIZE);
			body(hangman,SIZE);
			leg1(hangman,SIZE);
			leg2(hangman,SIZE);
			printMatrix(hangman,SIZE);
			life--;
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}else if(life==2 && win==false){
			refresh();
			head(hangman,SIZE);
			body(hangman,SIZE);
			leg1(hangman,SIZE);
			leg2(hangman,SIZE);
			arm1(hangman,SIZE);
			printMatrix(hangman,SIZE);
			life--;
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}else if(life==1 && win==false){
			refresh();
			head(hangman,SIZE);
			body(hangman,SIZE);
			leg1(hangman,SIZE);
			leg2(hangman,SIZE);
			arm1(hangman,SIZE);
			arm2(hangman,SIZE);
			printMatrix(hangman,SIZE);
			life--;
			printw("\n");
			print_array(abc);
			printw("\n");
			print_array2(empty,guess_word.size());
			printw("\n");
			clear();
		}
		if(life==0){
			end=false;
		}
		cont2=0;
		for(int i=0;i<guess_word.size();i++){
			if(empty[i]!=guess_word[i]){
				cont2++;
			}
		}
		if(life==0){
			move(15,50);
			printw("You losse!!!");
			printw("\n");
			move(16,50);
			printw("The word is: ");
			for(int i=0;i<guess_word.size();i++){
				printw("%c",guess_word[i]);
			}
		}else if(cont2==0){
			end=false;
			move(15,50);
			printw("You win!!!");
		}
	}while(end==true);

	attroff(COLOR_PAIR(1));
	refresh();
	getch();
	endwin();
	deleteMatrix(&hangman,SIZE);
	deleteArray(empty);
	return 0;
}

int menu(){
	int opt;
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	move(15,50);
	printw("%s","-----HANGMAN----\n");
	move(16,50);
	printw("%s","1.Normal Level\n");
	move(17,50);
	printw("%s","2.Medium Level\n");
	move(18,50);
	printw("%s","3.Hard Level\n");
	move(19,50);
	printw("%s","4.Exit\n");
	move(20,50);
	scanw("%d",&opt);
	attroff(COLOR_PAIR(1));
	return opt;
}

vector<string> Text_Read(vector<string> words, int opt){
	string line;
	if(opt==1){
		ifstream fe("normal.txt");
		while(getline(fe,line)){
			words.push_back(line);
		}
	}else if(opt==2){
		ifstream fe("medium.txt");
		while(getline(fe,line)){
			words.push_back(line);
		}
	}else if(opt==3){
		ifstream fe("hard.txt");
		while(getline(fe,line)){
			words.push_back(line);
		}
	}
	return words;
}

vector<char> Word_Selec(vector<string> words,vector<char> guess_word){
	string using_word=words[rand()%10+1];
	for(int i=0;i<using_word.length();i++){
		guess_word.push_back(using_word.at(i));
	}
	return guess_word;
}

void print_array(char abc[]){
	for(int i=0;i<26;i++){
		printw("%c",abc[i]);
	}
}

char* fillArray(int size){
	char* retVal = NULL;
	retVal = new char[size];
	for(int i=0;i<size;i++){
		retVal[i]='_';
	}	
	return retVal;
}

void print_array2(char* empty, int size){
	for(int i=0;i<size;i++){
		printw("%c",empty[i]);
	}
}

void deleteArray(char* data){
	delete[] data;
}

char** createMatrix(int size){
	char** retVal=NULL;
	retVal=new char*[size];
	for(int i=0;i<size;i++){
		retVal[i]=new char[size];
	}
	return retVal;
}

void fillMatrix(char** matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(j==0 || (j==(size/2) && (i<3) )){
				matrix[i][j]='|';
			}else if(i==0 && j<(size/2) || (i==0 && j==0)){
				matrix[i][j]='-';
			}else if(i==29){
				matrix[i][j]='_';
			}else{
				matrix[i][j]=' ';
			}
		}
	}
}

void head(char** matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(((j>=13 && j<=17) && (i==3)) || ((j>=13 && j<=17) && (i==9))){
				matrix[i][j]='-';
			}else if((j==11 || j==19) && (i==6 || i==7 || i==5)){
				matrix[i][j]='|';
			}else if((j==12 && i==4) || ((j==18 && i==8))){
				matrix[i][j]='/';
			}else if((j==12 && i==8) || ((j==18 && i==4))){
				matrix[i][j]='\\';
			}
		}
	}
}

void body(char** matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if((j==(size/2) && (i>=10 && i<=19))){
				matrix[i][j]='|';
			}
		}
	}

}

void leg1(char** matrix,int size){
	int odd=6;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if((i>=20 && i<=26) && (j>=8 && j<=14) && (i-j==odd)){
				matrix[i][j]='/';
				odd+=2;
			}
		}
	}
}

void leg2(char** matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if((i>=20 && i<=26) && (j>=16 && j<=22) && (i-j==4 || i-j==-4)){
				matrix[i][j]='\\';
			}
		}
	}
}

void arm1(char** matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if( (i>=9 && i<=15) && (j>=8 && j<=14) && (i-j==1) ){
				matrix[i][j]='\\';
			}
		}
	}
}

void arm2(char** matrix,int size){
	int even=-13;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if ( (i>=9 && i<=15) && (j>=16 && j<=22) && (i-j==even) ){
				matrix[i][j]='/';
				even+=2;
			}
		}
	}
}

void deleteMatrix(char*** matrix,int size){
	for (int i = 0; i < size; i++){
		delete[] (*matrix)[i];
	}
	delete[] *matrix;
	*matrix=NULL;
}

void printMatrix(char** matrix,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			printw("%c",matrix[i][j]);
		}
		printw("\n");
	}
}