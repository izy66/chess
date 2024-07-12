#include <iostream>
#include "textui.h"

TextUI::TextUI(Board* board) : chess_board{board} {
	chess_board->Attach(this);
}

void TextUI::Notify() {
	for (char r = TOP_ROW; r >= BOT_ROW; --r) {
		std::cout << r << ' ';
		for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
			std::cout << chess_board->GetPieceName(std::string() + c + r) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		std::cout << c << ' ';
	}
	std::cout << std::endl;
	std::cout << "White captured:";
	std::vector<char> captured = chess_board->CapturedBy(WHITE);
	for (const auto& cap : captured) {
		std::cout << ' ' << cap;
	}
	std::cout << std::endl;
	std::cout << "Black captured:";
	captured = chess_board->CapturedBy(BLACK);
	for (const auto& cap : captured) {
		std::cout << ' ' << cap;
	}
	std::cout << std::endl;
}