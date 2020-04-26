#include "graph.h"
#include <iostream>
#include <fstream>

graph::graph(){
	maxval = 0;
	minval = 0;
	win = NULL;
};

graph::graph(int newMax, int newMin, WINDOW * newWin){
	//input = firstIn;
	maxval = newMax;
	minval = newMin;
	win = newWin;
	innerGraph = newwin(getmaxy(win) - 4, getmaxx(win) - 10, 1, 1);

	graphArray = new char* [getmaxy(innerGraph) - 1];
	for(int row = 0; row < getmaxy(innerGraph) - 1; row++){
		graphArray[row] = new char[getmaxx(innerGraph)];
		for(int col = 0; col < getmaxx(innerGraph) - 1; col++){
			graphArray[row][col] = ' ';
		}
	}
}

graph::~graph(){
	if(graphArray != NULL){
		//free graphArray memory
	}
}


int graph::refresh(){
	std::ifstream temperatureFile;
	double temperature;

	temperatureFile.open("/sys/class/thermal/thermal_zone0/temp");
	if(!temperatureFile)
	{
		std::cout << "File not opened" << std::endl;
		return -1;
	}
	temperatureFile >> temperature;
	temperatureFile.close();

	temperature /= 1000; // temperature is stored in millidegrees centigrade

	inputToGraph(temperature);

	box(win, '|', '-');
	mvwprintw(win, 2, getmaxx(innerGraph) + 2, "- %i", maxval);
	mvwprintw(win, getmaxy(innerGraph), getmaxx(innerGraph) + 2, "- %i", minval);
	wrefresh(win);
	//box(graph, '|', '-');
	wborder(innerGraph, ' ', '|', ' ', '-', ' ', ' ', ' ', '*');
	/*
	mvwprintw(graph,getmaxy(graph) - 20, getmaxx(graph), "&");
	
	float differenceInValues = maxval - minval;
	float sizeOfPixel = differenceInValues / getmaxy(graph);

	for(int j = 0; j < getmaxy(graph); j++){
		if(temperature < minval + sizeOfPixel * j){
			mvwaddch(graph, getmaxy(graph) -  j, getmaxx(graph) - 2, ' ');
		}
		else{
			mvwaddch(graph, getmaxy(graph) - j, getmaxx(graph) - 2, '#');
		}
	}
*/
	updateGraph();

	return 0;
}

int graph::updateGraph(){
	for(int row = 0; row < getmaxy(innerGraph) - 1; row++){
		for(int col = 0; col < getmaxx(innerGraph) - 1; col++){
		//for(int col = getmaxx(innerGraph) - 1; col > 0; col--){
			mvwaddch(innerGraph, row, col, graphArray[row][col]);
		}
	}

	wrefresh(innerGraph);
	return 0;
}


int graph::inputToGraph(double temperature){
	//converts ints to floats, somewhat janky
	float differenceInValues = maxval - minval;
	float sizeOfPixel = differenceInValues / getmaxy(innerGraph);


	//add a new column to the end of the graph
	for(int i = getmaxy(innerGraph) - 2; i >= 0; i--){
	//for(int i = 0; i > getmaxy(innerGraph) - 2; i++){
		if(temperature < minval + sizeOfPixel * i){
			graphArray[i][getmaxx(innerGraph) - 2] = ' ';
		}
		//else if(i == 1){
			//graphArray[i][getmaxx(innerGraph) - 2] = '#';
		//}
		else{
			graphArray[i][getmaxx(innerGraph) - 2] = '#';
		}
	}


	//maximum jank. Reverse the added column so that the bottom is at the top, and the top is at the bottom. This is because
	//ncurses is stupid and wont read things normally >:C
	for(int j = getmaxy(innerGraph) - 2, i = 0, temp; i <= j; i++, j--){
		temp = graphArray[i][getmaxx(innerGraph) - 2];
		graphArray[i][getmaxx(innerGraph) - 2] = graphArray[j][getmaxx(innerGraph) - 2];
		graphArray[j][getmaxx(innerGraph) - 2] = temp;
	}


	//shift the entire graph over
	for(int row = 0; row < getmaxy(innerGraph) - 1; row++){
		for(int col = 0; col < getmaxx(innerGraph) - 2; col++){
			//if(graphArray[row+1] != nullptr){
				graphArray[row][col] = graphArray[row][col + 1];
			//}
		}
	}
/*
	//converts ints to floats, somewhat janky
	float differenceInValues = maxval - minval;
	float sizeOfPixel = differenceInValues / getmaxy(innerGraph);


	//add a new column to the end of the graph
	for(int i = getmaxy(innerGraph) - 2; i >= 0; i--){
	//for(int i = 0; i > getmaxy(innerGraph) - 2; i++){
		if(temperature < minval + sizeOfPixel * i){
			graphArray[i][getmaxx(innerGraph) - 2] = ' ';
		}
		//else if(i == 1){
			//graphArray[i][getmaxx(innerGraph) - 2] = '#';
		//}
		else{
			graphArray[i][getmaxx(innerGraph) - 2] = '#';
		}
	}



	//maximum jank. Reverse the added column so that the bottom is at the top, and the top is at the bottom. This is because
	//ncurses is stupid and wont read things normally >:C
	for(int j = getmaxy(innerGraph) - 2, i = 0, temp; i <= j; i++, j--){
		temp = graphArray[i][getmaxx(innerGraph) - 2];
		graphArray[i][getmaxx(innerGraph) - 2] = graphArray[j][getmaxx(innerGraph) - 2];
		graphArray[j][getmaxx(innerGraph) - 2] = temp;
	}

*/
	return 0;
}
