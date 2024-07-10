#ifndef TEXTUI_H
#define TEXTUI_H

#include "observer.h"
#include "board.h"

class TextUI : public Observer {
	Board *chess_board;
	public:
		TextUI(Board* chess_board);
		void Notify() override;
};

#endif