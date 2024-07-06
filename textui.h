#ifndef TEXTUI_H
#define TEXTUI_H

#include "observer.h"
#include "chessboard.h"

class TextUI : public Observer {
	ChessBoard *chess_board;
	public:
		TextUI(ChessBoard* chess_board);
		void Notify() override;
};

#endif