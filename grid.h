#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <fstream>
#include <string>
#include "cell.h"
#include "textdisplay.h"
//#include "window.h"

class Grid {
  	Cell **theGrid;                   // The actual n x n grid. 
  	int gridSize;                     // Size of the grid (n)
  	TextDisplay *td;                  // The text display.
  	//Xwindow * theWindow;

  	void clearGrid();                 // Frees the theGrid field.

	public:
	Grid();
	~Grid();
	int getcellcomp3();
	void ReComp5();
	void ReComp4();
	int LockedCells();  
	std::string Hint(int k);
	void graphicsgrid();
	void Scramble(); 
	void init(int n, std::ifstream& f, int t); 
	void initLevel1(int n, int t);
	void initLevel2(int n, int m, int t); 
	void init(const char& comp1, const char& comp2, const int& comp3, const int& comp4, const int& r, const int& c);
  	void gridswap(int x, int y, int x1, int y1);
	bool ExistMatchNoHarm();
	bool ExistMatch4NoHarm();
	int ExistMatch(int n);
	int ExistMatchL();
	void replenishran();
	void replenishranlevel1();
	void replenish(std::ifstream& ff);
	int SSh();
	int SSv();
	int SSp();
	int SSb();
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
