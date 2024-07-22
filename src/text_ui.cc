#include <iostream>
#include "text_ui.h"

TextUI::TextUI(Board* board) : chess_board{board} {
	chess_board->Attach(this);
}

void TextUI::Notify() {
	for (char r = TOP_ROW; r >= BOT_ROW; --r) {
		std::cout << r << ' ';
		for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
			std::string loc = std::string() + c + r;
			std::string output = "\e[";
		 	if (chess_board->GetPiecePlayer(loc) == WHITE) output += WHITE_;
			else output += BLACK_;
			output += ";";
			if ((r + c) % 2 == 0) {
				if (chess_board->LastMoved(loc)) output += LIGHT_BLUE_;
				else output += GREEN_;
			} else {
				if (chess_board->LastMoved(loc)) output += DARK_BLUE_;
				else output += GREY_;
			}
			output += "m";
			output += chess_board->PrintPieceName(loc);
			output += "\e[0m";
			std::cout << output;
		}
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		std::cout << c;
	}
	std::cout << std::endl;
	std::cout << "White captured:";
	std::vector<char> captured = chess_board->CapturedBy(WHITE);
	for (const auto& cap : captured) {
		std::cout << ' ' << std::string() + "\e[" + BLACK_ + ";" + GREEN_ + "m" + cap + "\e[0m";
	}
	std::cout << std::endl;
	std::cout << "Black captured:";
	captured = chess_board->CapturedBy(BLACK);
	for (const auto& cap : captured) {
		std::cout << ' ' << std::string() + "\e[" + WHITE_ + ";" + GREY_ + "m" + cap + "\e[0m";
	}
	std::cout << std::endl;
}