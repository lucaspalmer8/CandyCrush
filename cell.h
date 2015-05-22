#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "textdisplay.h"

class Cell {
  	char comp1;
	char comp2;
	int comp3;
	int comp4;
	int comp5;
	int r, c;                   //co-ordinates of the cell
  	TextDisplay * td;        //pointer to the text display

  // Add private members, if necessary (access to Xwindow, location in the window etc)
  //int x, y, width, height;
  //Xwindow * window;

  	void notifyDisplay();					    //notify the TextDisplay of the change

	public:
  	Cell();                                   // Default constructor
	char getcomp1();
	char getcomp2();
	int getcomp3();
	int getcomp4();
	int getcomp5();
	int getrow();
	int getcol();
	void setcomp1(const char& c1);
	void setcomp2(const char& c2);
	void setcomp3(const int& c3);
	void setcomp4(const int& c4);
	void setcomp5(const int& c5);
	void setcoords(const int& r, const int& c);
	void setdisplay(TextDisplay* t);                          //setter for private TextDisplay

};
#endif
