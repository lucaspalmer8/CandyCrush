#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include <string>
#include "window.h"

class TextDisplay {
  	std::string **theDisplay;          		//the n x n display 
  	const int gridSize;
	int textbox; 
	Xwindow * win;        		//size of the grid (n)
 	public:
  	TextDisplay(int n, int t); 			//one arg constructor where the parameter is the gridSize
	~TextDisplay(); 			//dtor
	void notify(char c1, char c2, int c3, int c4, int r1, int r2);	
	void graphics(char c1, char c2, int c3, int c4, int r1, int r2);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
