#include <curses.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "graph.h"
#include "genInfo.h"

int main(){
	double temperature;
	int in;
	//ncurses initialization
	initscr();
	refresh();
	nodelay(stdscr, TRUE);
	curs_set(0);

	//two new windows, whos size depends on terminal size
	WINDOW * genInfoWin = newwin(getmaxy(stdscr), getmaxx(stdscr)/4, 0, getmaxx(stdscr) - getmaxx(stdscr)/4);
	WINDOW * tempGraphWindow = newwin(getmaxy(stdscr), getmaxx(stdscr)/4 * 3, 0, 0);

	//feed the new windows into genInfo and graph constructors
	genInfo generalInformation(genInfoWin);
	graph temperatureGraph(55, 35, tempGraphWindow);
	refresh();

	//sleep, refresh both windows
	while((in = getch()) == ERR){
		usleep(1000000);
		generalInformation.refresh();
		temperatureGraph.refresh();
	}

	endwin();
	
	return 0;
}
