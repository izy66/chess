#include "board.h"
#include "pieces/blank.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"

bool Board::set(const std::string& loc, char name, char col) {
	if (name == get_name(loc)) return 0; // don't need to set again
	switch(tolower(name)) {
		case 'k':
			pieces[loc] = std::make_unique<King>(col);
			break;
		case 'q':
			pieces[loc] = std::make_unique<Queen>(col);
			break;
		case 'b':
			pieces[loc] = std::make_unique<Bishop>(col);
			break;
		case 'n':
			pieces[loc] = std::make_unique<Knight>(col);
			break;
		case 'p':
			pieces[loc] = std::make_unique<Pawn>(col);
			break;
		case 'r':
			pieces[loc] = std::make_unique<Rook>(col);
			break;
	}
	refresh_vision();
 	return 1;
}

void Board::refresh_vision() {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			std::string loc = std::string() + c + r;
			visibility_counter[player][loc] = 0;
			visibility_counter[opponent][loc] = 0;
		}
	}
	for (const auto& [loc, piece] : pieces) {
		if (piece != BLANK) {
			for (Piece::Iterator visible_block = piece->begin(this, loc); visible_block != piece->end(); ++visible_block) {
				if (visible_block != piece->begin(this, loc)) {
					++visibility_counter[piece->Player()][*visible_block];
				}
			}
		}
	}
}

char Board::get_name(const std::string& loc) { 
	// if (visibility_counter[player][loc] == 0 && (empty(loc) || pieces[loc]->Player() != player)) return FOG;
	if (empty(loc)) return blank.Print(loc);
	return pieces[loc]->Name();
}

char Board::get_player(const std::string& loc) {
	if (empty(loc)) return blank.Print(loc);
	return pieces[loc]->Player();
}

bool Board::remove(const std::string& loc) {
	if (pieces[loc] == BLANK) return 0; // nothing to remove
	pieces[loc] = BLANK;
	refresh_vision();
	return 1;
}

void Board::clear() {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			remove(std::string() + c + r);
		}
	}
}

void Board::reset() {
	clear();
	set("a1", 'R', WHITE);
	set("b1", 'N', WHITE);
	set("c1", 'B', WHITE);
	set("d1", 'Q', WHITE);
	set("e1", 'K', WHITE);
	set("f1", 'B', WHITE);
	set("g1", 'N', WHITE);
	set("h1", 'R', WHITE);
	for (char c = 'a'; c <= 'h'; ++c) {
		set(std::string() + c + '2', 'P', WHITE);
	}
	set("a8", 'r', BLACK);
	set("b8", 'n', BLACK);
	set("c8", 'b', BLACK);
	set("d8", 'q', BLACK);
	set("e8", 'k', BLACK);
	set("f8", 'b', BLACK);
	set("g8", 'n', BLACK);
	set("h8", 'r', BLACK);
	for (char c = 'a'; c <= 'h'; ++c) {
		set(std::string() + c + '7', 'p', BLACK);
	}
	captured_white.clear();
	captured_black.clear();
	king_loc[WHITE] = "e1";
	king_loc[BLACK] = "e8";
}

void Board::capture(const std::string& loc) {
	if (pieces[loc] != BLANK) {
		if (pieces[loc]->Player() == BLACK) {
			captured_white.emplace_back(pieces[loc]->Name());
		} else {
			captured_black.emplace_back(pieces[loc]->Name());
		}
		captured_pieces.push(std::move(pieces[loc]));
		pieces[loc] = BLANK;
	}
}

void Board::recapture(const std::string& loc) {
	pieces[loc] = std::move(captured_pieces.top());
	if (pieces[loc]->Player() == BLACK) captured_white.pop_back();
	else captured_black.pop_back();
	captured_pieces.pop();
}

std::vector<char> Board::captured_color(char color) {
	if (color == WHITE) {
		return captured_white;
	} else {
		return captured_black;
	}
}

bool Board::move_piece(const std::string& from, const std::string& to) {
	if (get_player(from) != player) {
		std::cout << "You can't move your opponent's pieces! Please make another move." << std::endl;
		return 0;
	}
	if (empty(from)) {
		std::cout << "You have to move a piece!" << std::endl;
		return 0;
	}
	if (get_player(to) == player) {
		std::cout << "You can't step over your own pieces!" << std::endl;
		return 0;
	}
	if (pieces[to] != BLANK) capture(to);
	pieces[from]->JustMoved();
	pieces[to] = std::move(pieces[from]);

	if (tolower(get_name(to)) == 'k') {
		king_loc[player] = to;
	}

	refresh_vision();

	if (check_mated()) {
		std::cout << "Check Mate!" << std::endl;
	} else 
	if (checked()) {
		std::cout << "Check!" << std::endl;
	}
	
	std::swap(player, opponent);
}

bool Board::checked() {
	return visibility_counter[player][king_loc[opponent]] > 0;
}

bool Board::check_mated() {
	for (Piece::Iterator move = pieces[king_loc[opponent]]->begin(this, king_loc[opponent]); move != pieces[king_loc[opponent]]->end(); ++move) {
		if (visibility_counter[player][*move] == 0) return 0;
	}
	return 1;
}