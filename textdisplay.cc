#include "cell.h"
#include "textdisplay.h"
#include "grid.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//class TextDisplay {
//  string **theDisplay;          //the n x n display 
//  const int gridSize;         //size of the grid (n)

TextDisplay::TextDisplay(int n, int text): gridSize(n){
		//cerr << "init the td!" << endl;
	theDisplay = new string* [n];
		//cerr << "init the td! 2" << endl;
	for(int k=0; k<n; k++){
		theDisplay[k] = new string[n];
	}
	textbox = text;
	if(text == 0){
		win = new Xwindow;
	}
		//cerr << "init the td! 3" << endl;
		//cerr << theDisplay[0][0] << "this is it!" << endl;
}
	 							//one arg constructor where the parameter is the gridSize

void TextDisplay::notify(char c1, char c2, int c3, int c4, int r1, int r2){	//td->notify(comp1, comp2, comp3, comp4, r, c);
		//cerr << "td notify a" << endl;
	ostringstream o;		//string str = o.str();
		//cerr << "td notify b" << endl;
	o << c1 << c2 << c3;// << c4;
		//cerr << "td notify c" << endl;
	string str1 = o.str();
		//cerr << "td notify d" << endl;
		//cerr << r1 << " " << r2 << endl;
		//cerr << gridSize << endl;
		//cerr << theDisplay[r1][r2] << endl;
		//cerr << "We got here" << endl;
	theDisplay[r1][r2] = str1;
		//cerr << "td notify e" << endl;
		//cerr << theDisplay[r1][r2] << endl;
}

void TextDisplay::graphics(char c1, char c2, int c3, int c4, int r1, int r2){ 
   if(textbox == 0){
	int j = 500 / gridSize;
	if(c3 == 0){
		win->fillRectangle(j*r2, j*r1, j, j, 0);
	}
	else if(c3 == 1){
		win->fillRectangle(j*r2, j*r1, j, j, 2);
	}
	else if(c3 == 2){
		win->fillRectangle(j*r2, j*r1, j, j, 3);
	}
	else if(c3 == 3){
		win->fillRectangle(j*r2, j*r1, j, j, 4);
	}
	if(c1 == 'l'){
		win->fillRectangle(j*r2, j*r1, j/10, j, 1);
		win->fillRectangle(j*r2, j*r1, j, j/10, 1);
		win->fillRectangle(j*r2 + (9*j/10), j*r1, j/10, j, 1);
		win->fillRectangle(j*r2, 50*r1 + (9*j/10), j, j/10, 1);
		win->fillRectangle(j*r2 + (9*j/20), j*r1, j/10, j, 1);
		win->fillRectangle(j*r2, j*r1 + (9*j/20), j, j/10, 1);
	}
	if(c2 == 'v'){
		win->fillRectangle(j*r2, j*r1, j/5, j, 1);
                win->fillRectangle(j*r2 + (j*13.3/50), j*r1, j/5, j, 1);
		win->fillRectangle(j*r2 + (j*26.6/50), j*r1, j/5, j, 1);
		win->fillRectangle(j*r2 + (4*j/5), j*r1, j/5, j, 1);		
	}
	if(c2 == 'h'){
		win->fillRectangle(j*r2, j*r1, j, j/5, 1);
                win->fillRectangle(j*r2, j*r1 + (13.3*j/50), j, j/5, 1);
                win->fillRectangle(j*r2, j*r1 + (26.6*j/50), j, j/5, 1);
                win->fillRectangle(j*r2, j*r1 + (4*j/5), j, j/5, 1);
	}
	if(c2 == 'b'){
		win->fillRectangle(r2*j, j*r1, j/10, j, 1);
                win->fillRectangle(r2*j, j*r1, j, j/10, 1);
                win->fillRectangle(r2*j + (9*j/10), j*r1, j/10, j, 1);
                win->fillRectangle(r2*j, j*r1 + (9*j/10), j, j/10, 1);
		win->fillRectangle(r2*j + (j/5), j*r1 + (j/5), (3*j/5), j/10, 1);
		win->fillRectangle(r2*j + (j/5), j*r1 + (j/5), j/10, 3*j/5, 1);
		win->fillRectangle(r2*j + (7*j/10), j*r1 + (j/5), j/10, 3*j/5, 1);
		win->fillRectangle(r2*j + (j/5), j*r1 + (7*j/10), 3*j/5, j/10, 1);
		win->fillRectangle(r2*j + (22.5*j/50), j*r1 + (22.5*j/50), (4*j/25), 8*j/50, 1);
	}
	if(c2 == 'p'){
		win->fillRectangle(j*r2 + (j/5), j*r1, j/5, j/5, 1);
		win->fillRectangle(j*r2 + (3*j/5), j*r1, j/5, j/5, 1);
		win->fillRectangle(j*r2, j*r1 + (j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (2*j/5), j*r1 + (j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (4*j/5), j*r1 + (j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (j/5), j*r1 + (2*j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (3*j/5), j*r1 + (2*j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2, j*r1 + (3*j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (2*j/5), j*r1 + (3*j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (4*j/5), j*r1 + (3*j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (j/5), j*r1 + (4*j/5), j/5, j/5, 1);
		win->fillRectangle(j*r2 + (3*j/5), j*r1 + (4*j/5), j/5, j/5, 1);
	}
    }
}
// enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  // Draws a rectangle
//  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
//  void drawString(int x, int y, std::string msg, int colour=Black);

  // Draws a string
//  void drawBigString(int x, int y, std::string msg, int colour=Black);

TextDisplay::~TextDisplay(){
	for(int k=0; k<gridSize; k++){	
		delete[] theDisplay[k];
	}
	delete[] theDisplay;
		//cerr << "After deleting the display" << endl;
	if(textbox == 0){
    		delete win;
	}
		//cerr << "after deleting the window" << endl;
}

ostream &operator<<(ostream &out, const TextDisplay &td){
	int j = td.gridSize;
	for(int k = 0; k < j; k++){
		for(int i = 0; i < j; i++){
			out << td.theDisplay[k][i] << " ";
		}
		out << endl;
	}
	return out;
}
