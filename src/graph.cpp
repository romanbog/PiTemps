#include "graph.h"
#include <iostream>
#include <fstream>

graph::graph(){
	maxval = 0;
	minval = 0;
	win = NULL;
};

//constructor with maximum temperature, minimum temperature
graph::graph(int newMax, int newMin, WINDOW * newWin){
	//input = firstIn;
	maxval = newMax;
	minval = newMin;
	win = newWin;
	innerGraph = newwin(getmaxy(win) - 4, getmaxx(win) - 10, 1, 1);

	//initialize 2d graph array to ' '
	graphArray = new char* [getmaxy(innerGraph) - 1];
	for(int row = 0; row < getmaxy(innerGraph) - 1; row++){
		graphArray[row] = new char[getmaxx(innerGraph)];
		for(int col = 0; col < getmaxx(innerGraph) - 1; col++){
			graphArray[row][col] = ' ';
		}
	}
}

//Refresh graph
int graph::refresh(){
	std::ifstream temperatureFile;
	double temperature;

	//open temperature file
	temperatureFile.open("/sys/class/thermal/thermal_zone0/temp");
	if(!temperatureFile)
	{
		std::cout << "File not opened" << std::endl;
		return -1;
	}
	temperatureFile >> temperature;
	temperatureFile.close();

	temperature /= 1000; // temperature is stored in millidegrees centigrade

	//add temperature to graph
	inputToGraph(temperature);

	box(win, '|', '-');
	mvwprintw(win, 2, getmaxx(innerGraph) + 2, "- %i", maxval);
	mvwprintw(win, getmaxy(innerGraph), getmaxx(innerGraph) + 2, "- %i", minval);
	wrefresh(win);
	wborder(innerGraph, ' ', '|', ' ', '-', ' ', ' ', ' ', '*');
	updateGraph();

	return 0;
}

//Prints the 2d char array to innerGraph
int graph::updateGraph(){
	for(int row = 0; row < getmaxy(innerGraph) - 1; row++){
		for(int col = 0; col < getmaxx(innerGraph) - 1; col++){
			mvwaddch(innerGraph, row, col, graphArray[row][col]);
		}
	}

	wrefresh(innerGraph);
	return 0;
}

//Add a new temperature value into the 2d array
int graph::inputToGraph(double temperature){
	//shift the entire graph over
	for(int row = 0; row < getmaxy(innerGraph) - 1; row++){
		for(int col = 0; col < getmaxx(innerGraph) - 2; col++){
				graphArray[row][col] = graphArray[row][col + 1];
		}
	}

	//cast ints to floats, somewhat janky but necessary
	float differenceInValues = maxval - minval;
	float sizeOfPixel = differenceInValues / getmaxy(innerGraph);


	//add a new column to the end of the graph
	for(int i = getmaxy(innerGraph) - 2; i >= 0; i--){
		if(temperature < minval + sizeOfPixel * i){
			graphArray[(getmaxy(innerGraph) - 1) - i - 1][getmaxx(innerGraph) - 2] = ' ';
		}
		else{
			graphArray[(getmaxy(innerGraph) - 1) - i - 1][getmaxx(innerGraph) - 2] = '#';
		}
	}

	return 0;
}
