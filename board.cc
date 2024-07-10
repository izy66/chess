#include "board.h"
#include "move.h"
#include "pieces/blank.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"

bool Board::SetPiece(const std::string& loc, char name, char col) {
	if (name == GetPieceName(loc)) return 0; // don't need to set again
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

char Board::GetPieceName(const std::string& loc) { 
	// if (visibility_counter[player][loc] == 0 && (empty(loc) || pieces[loc]->Player() != player)) return FOG;
	if (Empty(loc)) return blank.Print(loc);
	return pieces[loc]->Name();
}

char Board::GetPiecePlayer(const std::string& loc) {
	if (Empty(loc)) return blank.Print(loc);
	return pieces[loc]->Player();
}

bool Board::RemovePiece(const std::string& loc) {
	if (pieces[loc] == BLANK) return 0; // nothing to remove
	pieces[loc] = BLANK;
	refresh_vision();
	return 1;
}

void Board::Clear() {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			RemovePiece(std::string() + c + r);
		}
	}
}

void Board::Reset() {
	Clear();
	SetPiece("a1", 'R', WHITE);
	SetPiece("b1", 'N', WHITE);
	SetPiece("c1", 'B', WHITE);
	SetPiece("d1", 'Q', WHITE);
	SetPiece("e1", 'K', WHITE);
	SetPiece("f1", 'B', WHITE);
	SetPiece("g1", 'N', WHITE);
	SetPiece("h1", 'R', WHITE);
	for (char c = 'a'; c <= 'h'; ++c) {
		SetPiece(std::string() + c + '2', 'P', WHITE);
	}
	SetPiece("a8", 'r', BLACK);
	SetPiece("b8", 'n', BLACK);
	SetPiece("c8", 'b', BLACK);
	SetPiece("d8", 'q', BLACK);
	SetPiece("e8", 'k', BLACK);
	SetPiece("f8", 'b', BLACK);
	SetPiece("g8", 'n', BLACK);
	SetPiece("h8", 'r', BLACK);
	for (char c = 'a'; c <= 'h'; ++c) {
		SetPiece(std::string() + c + '7', 'p', BLACK);
	}
	king_loc[WHITE] = "e1";
	king_loc[BLACK] = "e8";
	captured_by[WHITE].clear();
	captured_by[BLACK].clear();
}

void Board::Capture(const std::string& loc) {
	if (pieces[loc] != BLANK) {
		if (pieces[loc]->Player() == BLACK) {
			captured_by[WHITE].emplace_back(pieces[loc]->Name());
		} else {
			captured_by[BLACK].emplace_back(pieces[loc]->Name());
		}
		captured_pieces.push(std::move(pieces[loc]));
		pieces[loc] = BLANK;
	}
}

void Board::Recapture(const std::string& loc) {
	pieces[loc] = std::move(captured_pieces.top());
	if (pieces[loc]->Player() == BLACK) captured_by[WHITE].pop_back();
	else captured_by[BLACK].pop_back();
	captured_pieces.pop();
}

std::vector<char> Board::CapturedBy(char player) {
	return captured_by[player];
}

bool Board::MakeMove(std::unique_ptr<Move>& move) {
	return move->MakeMoveOn(this);
}

bool Board::MovePiece(const std::string& from, const std::string& to) {
	if (GetPiecePlayer(from) != player) {
		std::cout << "You can't move your opponent's pieces! Please make another move." << std::endl;
		return 0;
	}
	if (empty(from)) {
		std::cout << "You have to move a piece!" << std::endl;
		return 0;
	}
	if (GetPiecePlayer(to) == player) {
		std::cout << "You can't step over your own pieces!" << std::endl;
		return 0;
	}
	if (pieces[to] != BLANK) Capture(to);
	pieces[from]->JustMoved();
	pieces[to] = std::move(pieces[from]);

	if (tolower(GetPieceName(to)) == 'k') {
		king_loc[player] = to;
	}

	last_moved = to;

	refresh_vision();

	if (check_mated()) {
		std::cout << "Check Mate!" << std::endl;
		game_over = true;
	} else 
	if (checked()) {
		std::cout << "Check!" << std::endl;
	}
	
	std::swap(player, opponent);

	return 1;
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