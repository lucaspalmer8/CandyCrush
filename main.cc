#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "cell.h"
#include "grid.h"
#include "textdisplay.h"
#include <cmath>
#include <cstdlib>
#include <time.h>
using namespace std;

//cerr << "begin" << endl;	
//cerr << "Step 1" << endl;

Grid * MainGrid = new Grid();	//initializes theGrid

//cerr << "first initialization" << endl;
int hasinput = -1;
int fileinit = 0;
int MAX = 4;
int size = 0;			//keeps track of size of current grid
int moves = 0;			//keeps track of moves left once game is started
int CurrentScore = 0;
int CurrentLevelScore = 0;
int LevelNumber = 0;
int text = 0;
int seed = time(NULL);
string scriptfile = "nothing";

//cerr << "before main" << endl;

int main(int argc, char *argv[]){
   int a = 1;
   while(a < argc){
	string str(argv[a]);
	if(str == "-text"){
		text = 1;
		a++;
	}
	else if(str == "-seed"){
		string str2(argv[a+1]);
		istringstream ss(str2);
		int n;
		ss >> n;
		seed = n;
		a += 2;
	}
	else if(str == "-scriptfile"){
		string str3(argv[a+1]);
		scriptfile = str3;
		a += 2;
	}
	else if(str == "-startlevel"){
		string str4(argv[a+1]);
		istringstream ss(str4);
		int n;
		ss >> n;
		LevelNumber = n;
		a += 2;
	}
   }
   srand(seed);		
   ifstream *ff;
   while(true){
	int bubbles = 0;
	if(scriptfile != "nothing"){
		ifstream f(scriptfile.c_str());
		string line;
		while(getline(f, line)){
			bubbles++;
		}
		if(bubbles == 10){
			hasinput = 0;
		}
		if(bubbles != 10){
			hasinput = 1;
		}
	}
	//cerr << "Made it to top of main while loop" << endl;
	if(LevelNumber == 0){
		if(scriptfile == "nothing"){
			ff = new ifstream("sequence.txt");
			MainGrid->init(10, *ff, text);
			fileinit = 1;
			hasinput = 1;
		}
		else{
			ff = new ifstream(scriptfile.c_str());
			MainGrid->init(10, *ff, text);
			fileinit = 1;
//			string test1;
//			*ff >> test1;
//			cout <<"istream: " <<  test1;
		}
	}
	if(LevelNumber == 1){
		//cerr << "level #" << " " << LevelNumber << endl;
		//cerr << "scriptfile " << scriptfile;
		if(scriptfile == "nothing"){
			MainGrid->initLevel1(10, text);
		}
		else{
			ff = new ifstream(scriptfile.c_str());
                        MainGrid->init(10, *ff, text);
			fileinit = 1;
		}
		//cerr << "end of level number 1 if" << endl;
	}
	if(LevelNumber == 2){
		if(scriptfile == "nothing"){
			MainGrid->initLevel2(10, 20, text);
		//cerr << "Here is scriptfile " << scriptfile <<  endl;
		}
		else{
			ff = new ifstream(scriptfile.c_str());
                        MainGrid->init(10, *ff, text);
			fileinit = 1;
			//cerr << "initializing by file " << endl;
		}
	}
	if(LevelNumber == 3){
		MainGrid->initLevel2(5, 0, text);
	}
	if(LevelNumber == 4){
		MainGrid->initLevel2(25, 0, text);
	}
	cout << "Level: " << LevelNumber << endl;
	cout << "Total Score: " << CurrentScore << endl;
	cout << "Current Level Score: " << CurrentLevelScore << endl;
	int goal;
	if(LevelNumber == 0){
		goal = 200;
	}
	if(LevelNumber == 1){
		goal = 300;
	}
	if(LevelNumber == 2){
		goal = 500;
	}
	//cerr << "Here is level number: " << LevelNumber << endl;
	if(LevelNumber == 3){
		goal = 55;
	}
	if(LevelNumber > 3){
		goal = 100000000;
	}
	cout << "Level Goal: " << goal << endl;
	if(LevelNumber == 2){
		cout << "MUST clear all locked cells!" << endl;
	}
	if(LevelNumber == 4){
		cout << "REMEMBER, no 3 matches allowed, no L matches allowed!"  << endl;
	}
	cout << *MainGrid << endl;
	MainGrid->graphicsgrid();
	string s;
	while(cin >> s){					//reads in commands from standard in to play game
		if(s == "swap"){				//enter initialization mode
				//cerr << "Step 4" << endl;
			int x, y, z;
			cin >> x >> y >> z;
			int x1 = x;
			int y1 = y;
			if(z == 0){
				x1 += -1;
			}
			if(z == 1){
				x1++;
			}
			if(z == 2){
				y1 += -1;
			}
			if(z == 3){
				y1++;
			}
				//cerr << "Before gridswap1 in main" << endl;
				//cerr << "Here is the 0 0 coordinate " << MainGrid->getcellcomp3() << endl;
			MainGrid->gridswap(x, y, x1, y1);
				//cerr << "Past gridswap1 in main" << endl;
			int Score = 0;
			int ChainNum = 0;
					//cerr << "Just before main while loop" << endl;
			while(true){
					//cerr << "Inside main while loop" << endl;
				int i5 = MainGrid->ExistMatch(5);
					//cerr << "past 5 match" << endl;
					//cerr << i5 << endl;
				int i4 = MainGrid->ExistMatch(4);
					//cerr << "past 4 match" << endl;
					//cerr << i4 << endl;
					//int iL = MainGrid->ExistMatchL();
					//cerr << "past L match" << endl;
					//cerr << iL << endl;
				int iL;
				int i3;
				if(LevelNumber == 4){
					i3 = 0;
					iL = 0;
				}
				else{
					i3 = MainGrid->ExistMatch(3);
					iL = MainGrid->ExistMatchL();
				}
					//cerr << "past 3 match" << endl;
					//cerr << i3 << endl;
				int allspecs = 0;
				while(true){
					//cerr << "inside special while loop" << endl;
					int ih = MainGrid->SSh();
					int iv = MainGrid->SSv();
					int ip = MainGrid->SSp();
					int ib = MainGrid->SSb();
					int spec = ih + iv + ip + ib;
						//cerr << "Special points: " << ih << " " << iv << " " << ip << " " << ib << endl;
					allspecs += spec;
						//cerr << "Temp special points: " << allspecs << endl;
					if(spec == 0){
						break;
					}
				}
					//cerr << "before recomp5" << endl;
				MainGrid->ReComp5();
					//cerr << "after recomp5" << endl;
				int totalmatches = i5+i4+i3+iL;
					//cerr << "total matches found " << totalmatches << endl;
					//cerr << "before total matches if" << endl;
				if(totalmatches == 0){
					break;
				}
				else{
						//cerr << "Inside total matches else" << endl;
						//cerr << "Number of 3 matches: " << i3 << endl;
						//cerr << "Number of 4 matches: " << i4 << endl;
						//cerr << "Number of 5 matches: " << i5 << endl;
						//cerr << "Number of L matches: " << iL << endl;
						//cerr << "Special points: " << allspecs << endl;
					int scoretemp = 15*i5 + 8*i4 + 15*iL + 3*i3 + allspecs;
						//cerr << "score temp: " << scoretemp << endl;
						//cerr << "chain num: " << ChainNum << endl;
					int addition = scoretemp * pow(2, ChainNum);
						//cerr << "addition : " << addition;
					Score += addition;
					ChainNum ++;
					//cerr << "made it to replenish" << endl;
					//cout << *MainGrid << endl << endl;
					//if(LevelNumber == 0 || scriptfile != "nothing"){
					//string garbage;
					//*ff >> garbage;
					//cout << "Garbage: " << garbage << endl;
					//cout << ff->eof() << endl;
					//bool abba = false;
					if(fileinit == 1 && hasinput == 1){
						MainGrid->replenish(*ff);
					}
					else{
						if(LevelNumber == 1){
							MainGrid->replenishranlevel1();
						}
						else{
							MainGrid->replenishran();
						}
					}
					//cout << *MainGrid << endl;
					//cerr << "past replenish" << endl;
				}
			}
			CurrentLevelScore += Score;
			CurrentScore += Score;
				//cerr << "Grid before reswap (if no match) " << endl;
				//cout << *MainGrid << endl;
				//cerr << "Here is Score: " << Score << endl;
				//cerr << "Here is Total Score: " << CurrentScore << endl;
			if(Score == 0){
				MainGrid->gridswap(x, y, x1, y1);
			}
			cout << "Level: " << LevelNumber << endl;
        		cout << "Total Score: " << CurrentScore << endl;
        		cout << "Current Level Score: " << CurrentLevelScore << endl;
        		cout << "Level Goal: " << goal << endl;
			cout << *MainGrid << endl;
			MainGrid->graphicsgrid();
		}
		if(s == "hint"){
			string hints = MainGrid->Hint(LevelNumber);
			if(hints != "NO"){
				istringstream ss(hints);
				int x, y, z;
				ss >> x >> y >> z;
				cout << x << " " << y << " " << z << endl;
			}
			//cerr << *MainGrid << endl;
		}
		if(s == "scramble"){
			string hints = MainGrid->Hint(LevelNumber);
			if(hints == "NO"){
				MainGrid->Scramble();
				cout << *MainGrid << endl;
			}
		}
		if(s == "levelup"){
			//cerr << "Inside levelup" << endl;
			if(LevelNumber != MAX){
				CurrentLevelScore = 0;
				LevelNumber++;
				//cerr << "Leaving levelup about to break " << endl;
				if(fileinit == 1){
					delete ff;
				}
				fileinit = 0;
				scriptfile = "nothing";
				//cerr << "after delete" << endl;
				break;
			}
			//cerr << "end of levelup" << endl;
		}
		if(s == "leveldown"){
			if(LevelNumber != 0){
				LevelNumber += -1;
				CurrentLevelScore = 0;
				if(fileinit == 1){
                                        delete ff;
                                }
                                fileinit = 0;
                                scriptfile = "nothing";
				break;
			}
		}
		if(s == "restart"){
			CurrentLevelScore = 0;
			if(fileinit == 1){
                              	delete ff;
                       	}
                       	fileinit = 0;
                      	scriptfile = "nothing";
			break;
		}
		if(LevelNumber == 0 && CurrentLevelScore >= 200){
			CurrentLevelScore = 0;
			LevelNumber ++;
			if(fileinit == 1){
                            	delete ff;
                        }
                        fileinit = 0;
                        scriptfile = "nothing";
			break;
		}
		if(LevelNumber == 1 && CurrentLevelScore >= 300){
			CurrentLevelScore = 0;
			LevelNumber ++;
			if(fileinit == 1){
                             	delete ff;
                        }
                       	fileinit = 0;
                        scriptfile = "nothing";
			break;
		}
		int lockedcells = MainGrid->LockedCells();
		if(LevelNumber == 2 && CurrentLevelScore >= 900 && lockedcells == 0){
			CurrentLevelScore = 0;
			LevelNumber ++;
			if(fileinit == 1){
				delete ff;
			}
			fileinit = 0;
			scriptfile = "nothing";
			break;
		}
		if(LevelNumber == 3 && CurrentLevelScore >= 55){
			CurrentLevelScore = 0;
			LevelNumber ++;
			if(fileinit == 1){
			 	delete ff;
			}
			fileinit = 0;
			scriptfile = "nothing";
			break;
		}
	}
   }
   delete MainGrid;
}
				
