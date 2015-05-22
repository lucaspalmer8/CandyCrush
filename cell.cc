#include "cell.h"
#include "textdisplay.h"
#include "grid.h"
#include <iostream>
#include <string>
using namespace std;

//the Cell class
//class Cell {
//  char comp1;   //first component
//  char comp2;   //second component:  type of cell
//  int comp3;    //third component:  colour of cell
//  int comp4;    //0 or 1, 0 is unused in another  match
//  int r;  	  //row number of cell
//  int c;        //column number of cell
//  TextDisplay * td;        //pointer to the text display

void Cell::notifyDisplay(){
	//cerr << "notify the td in notifyDisplay ";
 	td->notify(comp1, comp2, comp3, comp4, r, c);
}                          					//notify the TextDisplay of the change

Cell::Cell():comp1('_'),comp2('_'),comp3('_'),comp4(0),comp5(0){} // Default constructor

char Cell::getcomp1(){
	return comp1;
}

char Cell::getcomp2(){
        return comp2;
}               					        //getter for private state

int Cell::getcomp3(){
        return comp3;
}                                                               //getter for private state

int Cell::getcomp4(){
        return comp4;
}                                                               //getter for private state

int Cell::getcomp5(){
	return comp5;
}

int Cell::getrow(){
	return r;
}

int Cell::getcol(){
	return c;
}

void Cell::setcomp1(const char& change){			//(theGrid[r][c]).setcomp1(comp1);
		//cerr << "setcomp1 a" << endl;
	comp1 = change;
		//cerr << "setcomp1 b" << endl;
		//cerr << "notify the td in setcomp1 ";
	td->notify(comp1, comp2, comp3, comp4, r, c);
		//cerr << "setcomp1 c" << endl;
}

void Cell::setcomp2(const char& change){
        comp2 = change;
		//cerr << "notify the td in setcomp2 ";
        td->notify(comp1, comp2, comp3, comp4, r, c);
}

void Cell::setcomp3(const int& change){
        comp3 = change;
		//cerr << "notify the td in setcomp3 ";
        td->notify(comp1, comp2, comp3, comp4, r, c);
}

void Cell::setcomp4(const int& change){
        comp4 = change;
		//cerr << "notify the td in setcomp4 ";
        td->notify(comp1, comp2, comp3, comp4, r, c);
}

void Cell::setcomp5(const int& change){
	comp5 = change;
}

void Cell::setcoords(const int& r1, const int& c1){
	r = r1;
	c = c1;
		//cerr << "notify the td in setcoords ";
	td->notify(comp1, comp2, comp3, comp4, r, c);
}		                             			//setter for private co-ordinates of cell

void Cell::setdisplay(TextDisplay* t){		         	//setter for private TextDisplay
	td = t;
}
