#include <curses.h>

//Displays temperature in numerical form
class genInfo{
	public:
		genInfo();
		genInfo(WINDOW *);
		int refresh();
	private:
		WINDOW * win;
};
