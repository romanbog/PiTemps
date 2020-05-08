#include <curses.h>

//Temperature graph
class graph{
	public:
		graph();
		graph(int, int, WINDOW *);
		int refresh();
	protected:
		WINDOW * win; //main ncurses window object
		WINDOW * innerGraph; //secondary graph ncurses window object
		int maxval;
		int minval;
		char **graphArray; //2d char array to store graphical output
	private:
		int updateGraph(); //Prints values of graphArray() to innerGraph
		int inputToGraph(double); //adds a new temperature value to graphArray
};
