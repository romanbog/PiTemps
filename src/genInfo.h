#include <curses.h>

class genInfo{
	public:
		genInfo();
		genInfo(WINDOW *);
		int refresh();
	private:
		WINDOW * win;
};
