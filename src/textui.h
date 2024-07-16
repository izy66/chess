#ifndef TEXTUI_H
#define TEXTUI_H

#include "observer.h"
#include "board.h"

#define GREEN_ "42"
#define GREY_ "100"
#define BLACK_ "30"
#define WHITE_ "97"

class TextUI : public Observer {
	Board *chess_board;
	public:
		TextUI(Board* chess_board);
		void Notify() override;
};

#endif