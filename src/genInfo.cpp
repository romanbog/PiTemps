#include "genInfo.h"
#include <iostream>
#include <fstream>

genInfo::genInfo(){
	win = NULL;
}

genInfo::genInfo(WINDOW * newWin){
	win = newWin;
}

//Refreshes the window of genInfo.
int genInfo::refresh(){
	std::ifstream temperatureFile;
	double temperature;

	//open inputfile
	temperatureFile.open("/sys/class/thermal/thermal_zone0/temp");
	if(!temperatureFile)
	{
		std::cout << "File not opened" << std::endl;
		return -1;
	}
	temperatureFile >> temperature;
	temperature /= 1000; // temperature is stored in millidegrees centigrade
	box(win, '|', '-');
	mvwprintw(win, 1, 1, "%.4f *C", temperature);
	wrefresh(win);
	temperatureFile.close();
	return 0;
}
