#include <curses.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "graph.h"
#include "genInfo.h"

int main(){
	//std::ifstream temperatureFile;
	double temperature;
	int in;
	//void * stdscr;
	//void * stdscr = initscr();
	initscr();
	refresh();
	nodelay(stdscr, TRUE);
	curs_set(0);

	WINDOW * genInfoWin = newwin(getmaxy(stdscr), getmaxx(stdscr)/4, 0, getmaxx(stdscr) - getmaxx(stdscr)/4);
	WINDOW * tempGraphWindow = newwin(getmaxy(stdscr), getmaxx(stdscr)/4 * 3, 0, 0);

	genInfo generalInformation(genInfoWin);
	graph temperatureGraph(55, 35, tempGraphWindow);
	//box(genInfo, 0, 0);
	refresh();
	//mvwprintw(win,1,1, "%.4f *C", 45.34);

	while((in = getch()) == ERR){
		//usleep(100000);
		usleep(1000000);
		//clear();
		generalInformation.refresh();
		temperatureGraph.refresh();
	}

	endwin();
	
	return 0;
}
