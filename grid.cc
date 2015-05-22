#include "cell.h"
#include "textdisplay.h"
#include "grid.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

//class Grid {
//  Cell **theGrid;                   // The actual n x n grid. 
//  int gridSize;                     // Size of the grid (n)
//  TextDisplay *td;                  // The text display.
  //Xwindow * theWindow;


void Grid::clearGrid(){
		//cerr << "inside clear grid" << endl;
	delete td;	              	// Frees the theGrid field.
		//cerr << "after delete td" << endl;
	int k = 0;
       	while(k < gridSize){
                delete[] theGrid[k];
                k++;
       	}
       	delete[] theGrid;
}

Grid::Grid():theGrid(NULL),gridSize(0),td(NULL){}	//default constructor

Grid::~Grid(){
	clearGrid();
}

void Grid::graphicsgrid(){
	for(int a=0; a<gridSize; a++){
		for(int b=0; b<gridSize; b++){
			td->graphics(theGrid[a][b].getcomp1(), theGrid[a][b].getcomp2(), theGrid[a][b].getcomp3(), theGrid[a][b].getcomp4(), theGrid[a][b].getrow(), theGrid[a][b].getcol());
		}
	}
}

int Grid::getcellcomp3(){
	return theGrid[0][0].getcomp3();
}

void Grid::ReComp5(){					//MainGrid->ReComp5();
	for(int a=0; a<gridSize; a++){
		for(int b=0; b<gridSize; b++){
			theGrid[a][b].setcomp5(0);
		}
	}
}

void Grid::ReComp4(){                                   //MainGrid->ReComp5();
        for(int a=0; a<gridSize; a++){
                for(int b=0; b<gridSize; b++){
                        theGrid[a][b].setcomp4(0);
                }
        }
}

//int lockedcells = MainGrid->LockedCells();

int Grid::LockedCells(){
	int counter = 0;
	for(int a=0; a < gridSize; a++){
		for(int b=0; b < gridSize; b++){
			if(theGrid[a][b].getcomp1() == 'l'){
				counter++;
			}
		}
	}
	return counter;
}

void Grid::init(int n, ifstream& f, int text){			//initialized nxn grid
//		cerr << "step a grid init" << endl;
	if(theGrid != NULL){		//clears old grid if necessary
		//cerr << "step aa grid init" << endl;
		clearGrid();
	}                 		// Sets up an n x n grid.  Clears old grid, if necessary.
		//cerr << "step b grid init" << endl;
	gridSize = n;
	td = new TextDisplay(n, text);	//initializes text display
		//cerr << "step c grid init" << endl;
		//cerr << (*td).gridSize << "THIS IS TD SIZE" << endl;
	theGrid = new Cell* [n];
		//cerr << "step d grid init" << endl;
	int k = 0;
	while(k < n){				//initializes 2nd dimension
		theGrid[k] = new Cell[n];
		k++;
	}
		//cerr << "step e grid init" << endl;
	for(int a=0; a<n; a++){
		for(int b=0; b<n; b++){
				//cerr << "init loop 1" << endl;
			string triplet;
			f >> triplet;
			istringstream ss(triplet);
			char x;
			char y;
			int z;
			ss >> x;
			ss >> y;
			ss >> z;
				//cerr << "init loop 2" << endl;
			//init(x, y, z, 0, a, b);
				//cerr << "init loop 3" << endl;
			theGrid[a][b].setdisplay(td);
			init(x, y, z, 0, a, b);
			//td->notify(x, y, z, 0, a, b);
				//cerr << "init loop 5" << endl;
		}
	}
		//cerr << "step f grid init" << endl;		
}

void Grid::initLevel1(int n, int text){                  	//initialized nxn grid
        	//cerr << "Inside init level 1" << endl;
	if(theGrid != NULL){            	//clears old grid if necessary
                //cerr << "Inside check null iff" << endl;
		clearGrid();
        }
		//cerr << "After checkint if NULL" << endl;                               	// Sets up an n x n grid.  Clears old grid, if necessary.
        gridSize = n;
		//cerr << "Just before td init" << endl;
        td = new TextDisplay(n, text);        	//initializes text display
        	//cerr << "Just after td init" << endl;
	theGrid = new Cell* [n];
        int k = 0;
        while(k < n){                           //initializes 2nd dimension
                theGrid[k] = new Cell[n];
                k++;
        }
	int step = 1;
	//int random = 1;
	//srand (time(NULL));
		//cerr << "start of for loops " << endl;
        for(int a=0; a<n; a++){
                for(int b=0; b<n; b++){
			
			int comp3;			//v1 = rand() % 100;         // v1 in the range 0 to 99
                        char comp2;
			while(true){
				int v1 = rand() % 6;
				if(v1 == 0 || v1 == 1){
					comp3 = 0;
				}
				else if(v1 == 2 || v1 == 3){
					comp3 = 1;
				}
				else if(v1 == 4){
					comp3 = 2;
				}
				else if(v1 == 5){
					comp3 = 3;
				}
				if(a == 0){
					if(b == 0){
						break;
					}
					else if(comp3 != theGrid[a][b-1].getcomp3()){
						break;
					}
				}
				else if(b == 0){
					if(comp3 != theGrid[a-1][b].getcomp3()){
						break;
					}
				}
				else{
					if(comp3 != theGrid[a-1][b].getcomp3() && comp3 != theGrid[a][b-1].getcomp3()){
						break;
					}
				}
			}
			if(step == 5){
				int v2 = rand() % 4;
				if(v2 == 0){
					comp2 = 'h';
				}
				else if(v2 == 1){
					comp2 = 'v';
				}
				else if(v2 == 2){
					comp2 = 'b';
				}
				else if(v2 == 3){
					comp2 = 'p';
				}
				step = 1;
			}
			else{
				comp2 = '_';
				step ++;
			}
                        theGrid[a][b].setdisplay(td);
                        init('_', comp2, comp3, 0, a, b);
                }
        }
                //cerr << "step f grid init" << endl;           
}

void Grid::initLevel2(int n, int m, int text){                   //initialized nxn grid
        if(theGrid != NULL){                    //clears old grid if necessary
                clearGrid();
        }                                       // Sets up an n x n grid.  Clears old grid, if necessary.
        gridSize = n;
        td = new TextDisplay(n, text);                //initializes text display
        theGrid = new Cell* [n];
        int k = 0;
        while(k < n){                           //initializes 2nd dimension
                theGrid[k] = new Cell[n];
                k++;
        }
	//srand (time(NULL));
        int totallocked = 0;
        for(int a=0; a<n; a++){
                for(int b=0; b<n; b++){
			int comp3;
			while(true){
                        	comp3 = rand() % 4;
				if(a == 0){
					if(b == 0){
						break;
					}
					else if(comp3 != theGrid[a][b-1].getcomp3()){
						break;
					}
				}
				else if(b == 0){
					if(comp3 != theGrid[a-1][b].getcomp3()){
                                                break;
                                        }
				}
				else{
					if(comp3 != theGrid[a-1][b].getcomp3() && comp3 != theGrid[a][b-1].getcomp3()){
                                                break;
                                        }
				}
			}
			//cerr << "Here is comp1 " << comp1;
                        theGrid[a][b].setdisplay(td);
                        init('_', '_', comp3, 0, a, b);
                }
        }
	while(totallocked < m){
		for(int a=0; a<n; a++){
			for(int b=0; b<n; b++){
				int test = rand() % 5;
				if(totallocked < 20 && test == 0 && theGrid[a][b].getcomp1() != 'l'){
					theGrid[a][b].setcomp1('l');
					totallocked ++;
				}
			}
		}
	}
}

void Grid::Scramble(){
	for(int a=0; a<gridSize; a++){
		for(int b=0; b<(gridSize - 2); b++){
			gridswap(a, b, a, b+2);
		}
	}
	for(int a=0; a<(gridSize - 2); a++){
                for(int b=0; b<gridSize; b++){
                        gridswap(a, b, a+2, b);
                }
        }
	if(gridSize == 5){
		gridswap(2, 3, 4, 4);
		gridswap(0, 1, 3, 2);
		gridswap(1, 1, 3, 1);
		gridswap(3, 2, 0, 0);
	}
	else{
		gridswap(2, 3, 4, 6);
		gridswap(9, 8, 1, 1);
		gridswap(0, 8, 2, 4);
		gridswap(9, 9, 0, 9);
		gridswap(3, 3, 3, 4);
	}
}



int Grid::SSh(){
	int counter = 0;
	for(int a=0; a<gridSize; a++){
		for(int b=0; b<gridSize; b++){
			if(theGrid[a][b].getcomp4() == 1 && theGrid[a][b].getcomp2() == 'h' && theGrid[a][b].getcomp5() == 0){
				for(int c=0; c<gridSize; c++){
					theGrid[a][c].setcomp4(1);
				counter++;
				}
			theGrid[a][b].setcomp5(1);
			}
		}
	}
	return 4*counter;
}

int Grid::SSv(){
        int counter = 0;
        for(int a=0; a<gridSize; a++){
                for(int b=0; b<gridSize; b++){                          
                        if(theGrid[a][b].getcomp4() == 1 && theGrid[a][b].getcomp2() == 'v' && theGrid[a][b].getcomp5() == 0){
                                for(int c=0; c<gridSize; c++){
                                        theGrid[c][b].setcomp4(1);       
                                counter++;
				}
			theGrid[a][b].setcomp5(1);
                        }       
                }       
        }
        return 4*counter;
}

int Grid::SSp(){
        int counter = 0;
        for(int a=0; a<gridSize; a++){
                for(int b=0; b<gridSize; b++){                          
                        if(theGrid[a][b].getcomp4() == 1 && theGrid[a][b].getcomp2() == 'p' && theGrid[a][b].getcomp5() == 0){
				int bigguy = theGrid[a][b].getcomp3();
                                for(int c=0; c<gridSize; c++){
					for(int d=0; d<gridSize; d++){
						if(theGrid[c][d].getcomp3() == bigguy){
							theGrid[c][d].setcomp4(1);
                                			counter++;
						}
					}
				}
                        theGrid[a][b].setcomp5(1);
			}       
                }       
        }
        return 4*counter;
}

int Grid::SSb(){
	int counter = 0;
	for(int a=0; a<gridSize; a++){
		for(int b=0; b<gridSize; b++){
			if(theGrid[a][b].getcomp4() == 1 && theGrid[a][b].getcomp2() == 'b' && theGrid[a][b].getcomp5() == 0){
				if(a==0 && b==0){
					theGrid[a+1][b].setcomp4(1);
					theGrid[a][b+1].setcomp4(1);
					theGrid[a+1][b+1].setcomp4(1);
					counter += 4;
				}
				else if(a==0 && b==(gridSize - 1)){
					theGrid[a+1][b].setcomp4(1);
                                        theGrid[a][b-1].setcomp4(1);
                                        theGrid[a+1][b-1].setcomp4(1);
                                        counter += 4;
				}
				else if(a==(gridSize - 1) && b==0){
					theGrid[a-1][b].setcomp4(1);
                                        theGrid[a][b+1].setcomp4(1);
                                        theGrid[a-1][b+1].setcomp4(1);
                                        counter += 4;
				}
				else if(a==(gridSize - 1) && b==(gridSize - 1)){
					theGrid[a-1][b].setcomp4(1);
                                        theGrid[a][b-1].setcomp4(1);
                                        theGrid[a-1][b-1].setcomp4(1);
                                        counter += 4;
				}
				else if(a == 0){
					theGrid[a][b+1].setcomp4(1);
                                        theGrid[a][b-1].setcomp4(1);
                                        theGrid[a+1][b+1].setcomp4(1);
                                        theGrid[a+1][b-1].setcomp4(1);
					theGrid[a+1][b].setcomp4(1);
					counter += 6;
				}
				else if(a == (gridSize - 1)){
                                        theGrid[a][b+1].setcomp4(1);
                                        theGrid[a][b-1].setcomp4(1);
                                        theGrid[a-1][b+1].setcomp4(1);
                                        theGrid[a-1][b-1].setcomp4(1);
                                        theGrid[a-1][b].setcomp4(1);
                                        counter += 6;
                                }
				else if(b == 0){
                                        theGrid[a-1][b].setcomp4(1);
                                        theGrid[a+1][b].setcomp4(1);
                                        theGrid[a-1][b+1].setcomp4(1);
                                        theGrid[a+1][b+1].setcomp4(1);
                                        theGrid[a][b+1].setcomp4(1);
                                        counter += 6;
                                }
				else if(b == (gridSize - 1)){
                                        theGrid[a-1][b].setcomp4(1);
                                        theGrid[a+1][b].setcomp4(1);
                                        theGrid[a-1][b-1].setcomp4(1);
                                        theGrid[a+1][b-1].setcomp4(1);
                                        theGrid[a][b-1].setcomp4(1);
                                        counter += 6;
                                }
				else{
					theGrid[a-1][b].setcomp4(1);
                                        theGrid[a+1][b].setcomp4(1);
                                        theGrid[a-1][b-1].setcomp4(1);
                                        theGrid[a+1][b-1].setcomp4(1);
                                        theGrid[a][b-1].setcomp4(1);
					theGrid[a-1][b+1].setcomp4(1);
                                        theGrid[a+1][b+1].setcomp4(1);
                                        theGrid[a][b+1].setcomp4(1);
                                        counter += 9;
				}
			theGrid[a][b].setcomp5(1);
			}
		}
	}
	return 4*counter;
}

void Grid::init(const char& comp1, const char& comp2, const int& comp3, const int& comp4, const int& r, const int& c){
        	//cerr << "long init 1" << endl;
	(theGrid[r][c]).setcoords(r, c);
	(theGrid[r][c]).setcomp1(comp1);
		//cerr << "long init 2" << endl;
        (theGrid[r][c]).setcomp2(comp2);
		//cerr << "long init 3" << endl;
        (theGrid[r][c]).setcomp3(comp3);
		//cerr << "long init 4" << endl;
        (theGrid[r][c]).setcomp4(comp4);
		//cerr << "long init 5" << endl;
		//cerr << "long init 6" << endl;
}

void Grid::gridswap(int x, int y, int x1, int y1){
		//cerr << "swapping " << x << " " << y << " and " << x1 << " " << y1 << endl;
		//cerr << "swapping " << theGrid[x][y].getcomp3() << " and " << theGrid[x1][y1].getcomp3() << endl;
	//char c1 = theGrid[x][y].getcomp1();
        char c2 = theGrid[x][y].getcomp2();
        int c3 = theGrid[x][y].getcomp3();
        int c4 = theGrid[x][y].getcomp4();
        //int r1 = theGrid[x][y].getrow();
        //int r2 = theGrid[x][y].getcol();
        //theGrid[x][y].setcomp1(theGrid[x1][y1].getcomp1());
        theGrid[x][y].setcomp2(theGrid[x1][y1].getcomp2());
        theGrid[x][y].setcomp3(theGrid[x1][y1].getcomp3());
        theGrid[x][y].setcomp4(theGrid[x1][y1].getcomp4());
        //theGrid[x][y].setcoords(theGrid[x1][y1].getrow(), theGrid[x1][y1].getcol());
        //theGrid[x1][y1].setcomp1(c1);
        theGrid[x1][y1].setcomp2(c2);
        theGrid[x1][y1].setcomp3(c3);
        theGrid[x1][y1].setcomp4(c4);
        //theGrid[x1][y1].setcoords(r1, r2);
		//cerr << "now " << theGrid[x][y].getcomp3() << " and " << theGrid[x1][y1].getcomp3() << endl;
}

void Grid::replenish(ifstream& ff){		//ff = MainGrid->replenish(ff)
	for(int a = (gridSize - 1); a >= 0; a += -1){
		for(int b = 0; b < gridSize; b++){
			if(theGrid[a][b].getcomp4() == 1){
				int check = 0;
				for(int c = 1; c < a+1; c++){
					if(theGrid[a-c][b].getcomp4() == 0){
						//theGrid[a][b].setcomp1(theGrid[a-c][b].getcomp1());
						theGrid[a][b].setcomp2(theGrid[a-c][b].getcomp2());
						theGrid[a][b].setcomp3(theGrid[a-c][b].getcomp3());
						theGrid[a][b].setcomp4(0);
						theGrid[a-c][b].setcomp4(1);
						check++;
						break;
					}
				}
				if(check == 0){
					//theGrid[a][b].setcomp1('_');
					theGrid[a][b].setcomp2('_');
					char hold;
					ff >> hold;
					int holdnum = hold - '0';
					theGrid[a][b].setcomp3(holdnum);
					theGrid[a][b].setcomp4(0);
				}
			}
		}
	}
}

void Grid::replenishran(){             //ff = MainGrid->replenish(ff)
        //srand (time(NULL));
	for(int a = (gridSize - 1); a >= 0; a += -1){
                for(int b = 0; b < gridSize; b++){
                        if(theGrid[a][b].getcomp4() == 1){
                                int check = 0;
                                for(int c = 1; c < a+1; c++){
                                        if(theGrid[a-c][b].getcomp4() == 0){
                                                //theGrid[a][b].setcomp1(theGrid[a-c][b].getcomp1());
                                                theGrid[a][b].setcomp2(theGrid[a-c][b].getcomp2());
                                                theGrid[a][b].setcomp3(theGrid[a-c][b].getcomp3());
                                                theGrid[a][b].setcomp4(0);
                                                theGrid[a-c][b].setcomp4(1);
                                                check++;
                                                break;
                                        }
                                }
                                if(check == 0){
					int comp3 = rand() % 4;
                                        //theGrid[a][b].setcomp1('_');
                                        theGrid[a][b].setcomp2('_');
                                        theGrid[a][b].setcomp3(comp3);
                                        theGrid[a][b].setcomp4(0);
                                }
                        }
                }
        }
}

void Grid::replenishranlevel1(){             //ff = MainGrid->replenish(ff)
        //srand (time(NULL));
        for(int a = (gridSize - 1); a >= 0; a += -1){
                for(int b = 0; b < gridSize; b++){
                        if(theGrid[a][b].getcomp4() == 1){
                                int check = 0;
                                for(int c = 1; c < a+1; c++){
                                        if(theGrid[a-c][b].getcomp4() == 0){
                                                //theGrid[a][b].setcomp1(theGrid[a-c][b].getcomp1());
                                                theGrid[a][b].setcomp2(theGrid[a-c][b].getcomp2());
                                                theGrid[a][b].setcomp3(theGrid[a-c][b].getcomp3());
                                                theGrid[a][b].setcomp4(0);
                                                theGrid[a-c][b].setcomp4(1);
                                                check++;
                                                break;
                                        }
                                }
                                if(check == 0){
					int comp3;
                                        int v1 = rand() % 6;
					if(v1 == 0 || v1 == 1){
	                                        comp3 = 0;
        	                        }
                	                else if(v1 == 2 || v1 == 3){
                        	                comp3 = 1;
                                	}
	                                else if(v1 == 4){
        	                                comp3 = 2;
                	                }
                        	        else if(v1 == 5){
                                	        comp3 = 3;
                                	}
                                        //theGrid[a][b].setcomp1('_');
                                        theGrid[a][b].setcomp2('_');
                                        theGrid[a][b].setcomp3(comp3);
                                        theGrid[a][b].setcomp4(0);
                                }
                        }
                }
        }
}
		
string Grid::Hint(int k){
	for(int a=0; a<(gridSize - 1); a++){
		for(int b=0; b<gridSize; b++){
			gridswap(a, b, a+1, b);
			bool j;
			if(k == 4){
				j = ExistMatch4NoHarm();
			}
			else{
				j = ExistMatchNoHarm();   
			}
			if(j){
				ostringstream o;
				o << a << " " << b << " " << 1 << " ";
				string str = o.str();
				gridswap(a, b, a+1, b);
                		return str;
			}
			gridswap(a, b, a+1, b);
		}
	}
	for(int c=0; c<gridSize; c++){
		for(int d=0; d<(gridSize - 1); d++){
			gridswap(c, d, c, d+1);
			//bool j = ExistMatchNoHarm();
                        bool j;
			if(k == 4){
                                j = ExistMatch4NoHarm();
                        }
                        else{
                                j = ExistMatchNoHarm();
                        }
			if(j){
                                ostringstream o;
                                o << c << " " << d << " " << 3 << " ";
                                string str = o.str();
                                gridswap(c, d, c, d+1);
                                return str;
                        }
                        gridswap(c, d, c, d+1);
                }
        }
	return "NO";
}

bool Grid::ExistMatchNoHarm(){
        //int counter = 0;
        int iterate = gridSize - 2;
        for(int a=0; a<gridSize; a++){
                for(int b=0; b<gridSize; b++){	
			if(a < iterate){
                                int arr[3];           
                                for(int c=0; c<3; c++){
                                        arr[c] = theGrid[a+c][b].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<3; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(isequal == 1){
                                        return true;
                                }
                        }
			if(b < iterate){
                                int arr[3];           
                                for(int c=0; c<3; c++){
                                        arr[c] = theGrid[a][b+c].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<3; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(isequal == 1){
                                      	return true;
                                }
                                                                //cerr << "b check 3" << endl;
                        }
		}
	}
	return false;
}

bool Grid::ExistMatch4NoHarm(){
        //int counter = 0;
        int iterate = gridSize - 3;
        for(int a=0; a<gridSize; a++){
                for(int b=0; b<gridSize; b++){
                        if(a < iterate){
                                int arr[4];
                                for(int c=0; c<4; c++){
                                        arr[c] = theGrid[a+c][b].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<4; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(isequal == 1){
                                        return true;
                                }
                        }
                        if(b < iterate){
                                int arr[4];
                                for(int c=0; c<4; c++){
                                        arr[c] = theGrid[a][b+c].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<4; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(isequal == 1){
                                        return true;
                                }
                                                                //cerr << "b check 3" << endl;
                        }
                }
        }
        return false;
}
					

int Grid::ExistMatch(int n){
	int counter = 0;
	int speccounter = 0;
	ostringstream o;
	ostringstream spec;
	int iterate = gridSize - n + 1;
		//cerr << "Here is iterate: " << iterate << endl;
		//cerr << "exist match 1" << endl;
		//cerr << "Searching for: " << n << " length matches" << endl;
	for(int a=0; a<gridSize; a++){
		for(int b=0; b<gridSize; b++){
			if(a < iterate){
								//cerr << "a < iterate" << " Here is a " << a << endl;
				int arr[n];			//Expression* exparr[10];
				for(int c=0; c<n; c++){
					arr[c] = theGrid[a+c][b].getcomp3();
				}
				int isequal = 1;
				for(int d=0; d<n; d++){
					if(arr[d] != arr[0]){
						isequal = 0;
						break;
					}
					if(theGrid[a+d][b].getcomp4() == 1){
						isequal = 0;
						break;
					}
				}
								//cerr << "Isequal test a" << endl;
				if(isequal == 1){
					for(int e=0; e<n; e++){
						o << a+e << " " << b << " ";
					}
					if(n == 4){
						int v1 = rand() % n;         // v1 in the range 0 to 99
						spec << a+v1 << " " << b << " " << 'v' << " ";
						speccounter++;
					}
					if(n == 5){
						spec << a+2 << " " << b << " " << 'p' << " ";
						speccounter++;
					}
					counter++;
				}
			}
			if(b < iterate){
								//cerr << "b < iterate" << " Here is b " << b << endl;
                                int arr[n];                     //Expression* exparr[10];
                                for(int c=0; c<n; c++){
                                        arr[c] = theGrid[a][b+c].getcomp3();
                                }
								//cerr << "b check 1" << endl;
                                int isequal = 1;
                                for(int d=0; d<n; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
					if(theGrid[a][b+d].getcomp4() == 1){
						isequal = 0;
						break;
					}
                                }
								//cerr << "b check 2" << endl;
                                if(isequal == 1){
								//cerr << "we have a match! isequal is 1" << endl;
                                        for(int e=0; e<n; e++){
                                                o << a << " " << b+e << " ";
                                        }
					if(n == 4){
                                                int v1 = rand() % n;         // v1 in the range 0 to 99
                                                spec << a << " " << b+v1 << " " << 'h' << " ";
                                                speccounter++;
                                        }
                                        if(n == 5){
                                                spec << a << " " <<  b+2 << " " << 'p' << " ";
                                                speccounter++;
                                        }
                                        counter++;
                                }
								//cerr << "b check 3" << endl;
                        }
		}
	}
	if(counter == 0){
								//cerr << "counter check if" << endl;
		return 0;
	}
	else{
								//cerr << "counter check else" << endl;
		string str = o.str();
		istringstream ss(str);
		int coor1num;
								//cerr << "made it to final while" << endl;
		while(ss >> coor1num){
			int coor2num;
			ss >> coor2num;
								//cerr << "about to set comp4 to 1" << endl;
								//cerr << "coordinate pair " << coor1num << " " << coor2num << endl;
								//char c = '1';
								//int i = c - '0’;
			//int coor1num = coor1 - '0';
			//int coor2num = coor2 - '0';
				//cerr << "Coords: " << coor1 << coor2 << endl;	
				//cerr << "Comp1: " << theGrid[coor1num][coor2num].getcomp1() << endl;
                                //cerr << "Comp4: " << theGrid[coor1num][coor2num].getcomp4() << endl;
			if(theGrid[coor1num][coor2num].getcomp1() == '_'){
								//cerr << "made it past number conversion" << endl;
				theGrid[coor1num][coor2num].setcomp4(1);
			}
			else{
				theGrid[coor1num][coor2num].setcomp1('_');
			}
				//cerr << "Comp1: " << theGrid[coor1num][coor2num].getcomp1() << endl;
				//cerr << "Comp4: " << theGrid[coor1num][coor2num].getcomp4() << endl;
								//cerr << "made it past setting comp4 to be 1 for a cell" << endl;
		}
								//cerr << "not checking for specialy square deletions"  << endl;
		if(speccounter != 0){
			string strspec = spec.str();
								//cerr << "Speccounter a" << endl;
			istringstream sss(strspec);
								//cerr << "Speccounter b" << endl;
			int check1num;
								//cerr << "Speccounter c" << endl;
			while(sss >> check1num){
				int check2num;
				char check3;
				sss >> check2num >> check3;
								//cerr << check1num << " " << check2num << " " << check3 << endl;
				//int check1num = check1 - '0';
				//int check2num = check2 - '0';
								//cerr << "about to set comp4 to 0"  << endl;
				//theGrid[check1num][check2num].setcomp1('_');
				theGrid[check1num][check2num].setcomp4(0);
								//cerr << "about to set special character (comp2)" << endl;
				theGrid[check1num][check2num].setcomp2(check3);
								//cerr << "Made it to the end!" << endl;
			}
		}
								//cerr << "about to return counter" << endl;
		return counter;
	}			
}
				
			

int Grid::ExistMatchL(){
					//cerr << "Into Exist Match L" << endl;
        int counter = 0;
	ostringstream o;
	ostringstream spec;
        int iterate = gridSize - 2;
					//cerr << "Just before L loop" << endl;
        for(int a=0; a<gridSize; a++){
                for(int b=0; b<gridSize; b++){
					//cerr << "inside L loop " << endl;
					//cerr << "a and b less than" << endl;
                        if(a<iterate && b<iterate){
                                int arr[5];                     //Expression* exparr[10];
                                for(int c=0; c<3; c++){
                                        arr[c] = theGrid[a+c][b].getcomp3();
                                }
				for(int c1=1; c1<3; c1++){
					arr[c1+2] = theGrid[a][b+c1].getcomp3();
				} 
                                int isequal = 1;
                                for(int d=0; d<5; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
				}
				if(theGrid[a][b].getcomp4()==1 || theGrid[a][b+1].getcomp4()==1 || theGrid[a][b+2].getcomp4()==1){
                      	               	isequal = 0;
                                }
				if(theGrid[a+1][b].getcomp4()==1 || theGrid[a+2][b].getcomp4()==1){
					isequal = 0;
				}
                                if(isequal){
                                       	o << a << " " << b << " " << a+1 << " " << b << " " << a+2 << " " << b << " " << a << " " << b+1 << " " << a << " " << b+2 << " ";
                                        spec << a << " " << b << " ";
					counter++;
                                }
                        }
					//cerr << "a less than" << endl;
			if(a<iterate && b>1){
                                int arr[5];                     //Expression* exparr[10];
                                for(int c=0; c<3; c++){
                                        arr[c] = theGrid[a+c][b].getcomp3();
                                }
                                for(int c1=1; c1<3; c1++){
                                        arr[c1+2] = theGrid[a][b-c1].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<5; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(theGrid[a][b].getcomp4()==1 || theGrid[a][b-1].getcomp4()==1 || theGrid[a][b-2].getcomp4()==1){
                                        isequal = 0;
                                }
                                if(theGrid[a+1][b].getcomp4()==1 || theGrid[a+2][b].getcomp4()==1){
                                        isequal = 0;
                                }
                                if(isequal){
                                        o << a << " " << b << " " << a+1 << " " << b << " " << a+2 << " " << b << " " << a << " " << b-1 << " " << a << " " << b-2 << " ";
                                        spec << a << " " << b << " ";
					counter++;
                                }
                        }
					//cerr << "neither less than" << endl;
			if(a>1 && b>1){
                                int arr[5];                     //Expression* exparr[10];
                                for(int c=0; c<3; c++){
                                        arr[c] = theGrid[a-c][b].getcomp3();
                                }
                                for(int c1=1; c1<3; c1++){
                                        arr[c1+2] = theGrid[a][b-c1].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<5; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(theGrid[a][b].getcomp4()==1 || theGrid[a][b-1].getcomp4()==1 || theGrid[a][b-2].getcomp4()==1){
                                        isequal = 0;
                                }
                                if(theGrid[a-1][b].getcomp4()==1 || theGrid[a-2][b].getcomp4()==1){
                                        isequal = 0;
                                }
                                if(isequal){
                                        o << a << " " << b << " " << a-1 << " " << b << " " << a-2 << " " << b << " " << a << " " << b-1 << " " << a << " " << b-2 << " ";
                                        spec << a << " " << b << " ";
					counter++;
                                }
                        }
					//cerr << "b less than" << endl;
			if(a>1 && b<iterate){
                                int arr[5];                     //Expression* exparr[10];
                                for(int c=0; c<3; c++){
                                        arr[c] = theGrid[a-c][b].getcomp3();
                                }
                                for(int c1=1; c1<3; c1++){
                                        arr[c1+2] = theGrid[a][b+c1].getcomp3();
                                }
                                int isequal = 1;
                                for(int d=0; d<5; d++){
                                        if(arr[d] != arr[0]){
                                                isequal = 0;
                                                break;
                                        }
                                }
                                if(theGrid[a][b].getcomp4()==1 || theGrid[a][b+1].getcomp4()==1 || theGrid[a][b+2].getcomp4()==1){
                                        isequal = 0;
                                }
                                if(theGrid[a-1][b].getcomp4()==1 || theGrid[a-2][b].getcomp4()==1){
                                        isequal = 0;
                                }
                                if(isequal){
                                        o << a << " " << b << " " <<  a-1 << " " << b << " " << a-2 << " "  << b << " " << a << " " << b+1 << " " << a << " " << b+2 << " ";
                                        spec << a << " " << b << " ";
					counter++;
                                }
                        }
                        
                }
        }
					//cerr << "counter L if" << endl;
        if(counter == 0){
                return 0;
        }
        else{
					//cerr << "counter L else" << endl;
                string str = o.str();
                istringstream ss(str);
                int coor1num;
                while(ss >> coor1num){
                        int coor2num;
                        ss >> coor2num;
							//cerr << "coords: " << coor1num << " " << coor2num << endl;
							//cerr << "about to set comp4 to 1" << endl;
                                                      	//cerr << "coordinate pair " << coor1num << " " << coor2num << endl;
			//int coor1num = coor1 - '0';
			//int coor2num = coor2 - '0';
			if(theGrid[coor1num][coor2num].getcomp1() == '_'){
                                                                //cerr << "made it past number conversion" << endl;
                                theGrid[coor1num][coor2num].setcomp4(1);
                        }
                        else{
                                theGrid[coor1num][coor2num].setcomp1('_');
                        }
                        //(theGrid[coor1num][coor2num]).setcomp4(1);
                }
		//cerr << "now onto special squares" << endl;
		string strspec = spec.str();
		istringstream sss(strspec);
		int check1num;
		//cerr << "special square shile loop" << endl;
		while(sss >> check1num){
			int check2num;
			sss >> check2num;
			//int check1num = check1 - '0';
			//int check2num = check2 - '0';
			theGrid[check1num][check2num].setcomp4(0);
			theGrid[check1num][check2num].setcomp2('b');
			//theGrid[check1num][check2num].setcomp1('_');
		}
                return counter;
        }

}
	
								//string str = o.str();	 

ostream &operator<<(ostream &out, const Grid &g){
        out << *(g.td);
	return out;
}
