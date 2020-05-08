#include <curses.h>

class graph{
	public:
		graph();
		~graph();
		graph(int, int, WINDOW *);
		int refresh();
	protected:
		WINDOW * win; //main ncurses window object
		WINDOW * innerGraph; //secondary graph ncurses window object
		int maxval;
		int minval;
		char **graphArray; //2d char array to store graphical output
	private:
		int updateGraph();
		int inputToGraph(double);
};
