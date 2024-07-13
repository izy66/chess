#include "board.h"
#include "moves/move.h"
#include "pieces/blank.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"

bool Board::SetPiece(const std::string& loc, char name, char player) {
	if (name == GetPieceName(loc)) return 0; // don't need to set again
	switch(tolower(name)) {
		case 'k':
			pieces[loc] = std::make_unique<King>(player);
			king_loc[player] = loc;
			break;
		case 'q':
			pieces[loc] = std::make_unique<Queen>(player);
			break;
		case 'b':
			pieces[loc] = std::make_unique<Bishop>(player);
			break;
		case 'n':
			pieces[loc] = std::make_unique<Knight>(player);
			break;
		case 'p':
			pieces[loc] = std::make_unique<Pawn>(player);
			break;
		case 'r':
			pieces[loc] = std::make_unique<Rook>(player);
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
			Piece::Iterator visible_block = piece->begin(this, loc);
			++visible_block;
			for (; visible_block != piece->end(); ++visible_block) {
				++visibility_counter[piece->Player()][*visible_block];
			}
		}
	}
}

char Board::GetPieceName(const std::string& loc) { 
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
	game_over = false;
	player = WHITE;
	opponent = BLACK;
}

void Board::Capture(const std::string& loc) {
	if (pieces[loc] != BLANK) {
		if (toupper(pieces[loc]->Name() == KING)) {
			game_over = true;
			who_won = pieces[loc]->Player() == WHITE ? BLACK : WHITE;
			return;
		}
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

bool Board::ValidMove(const std::string& from, const std::string& to) {
	if (Empty(from)) {
		std::cout << "You have to move a piece!" << std::endl;
		return 0;
	}
	if (GetPiecePlayer(from) != player) {
		std::cout << "You can't move your opponent's pieces! Please make another move." << std::endl;
		return 0;
	}
	if (GetPiecePlayer(to) == player) {
		std::cout << "You can't step over your own pieces!" << std::endl;
		return 0;
	}
	if (from == to) {
		std::cout << "You can't move to the same square!" << std::endl;
		return 0;
	}
	Piece::Iterator move = pieces[from]->begin(this, from);
	++move;
	for (; move != pieces[from]->end(); ++move) {
		if (*move == to && (!IsKing(from) || !CanBeCapturedBy(opponent, to))) return 1;
	}
	return 0;
}

bool Board::IsEnPassant(const std::string& from, const std::string& to) {
	if (toupper(pieces[from]->Name()) != PAWN || from[0] == to[0] || abs(from[1] - to[1]) > 1) return 0;
	std::string en_passant_loc = std::string() + to[0] + from[1];
	return !Empty(en_passant_loc) && toupper(pieces[en_passant_loc]->Name()) == PAWN &&
			FirstMove(en_passant_loc) && LastMovedLoc() == en_passant_loc;
}

bool Board::IsCastling(const std::string& from, const std::string& to) {
	if (!IsKing(from) || Checked()) return 0; // can't castle if not king or king in check
	if (abs(to[0] - from[0]) != 2 || to[1] != from[1]) return 0;
	int castle_dir = (to[0] - from[0]) / 2;
	std::string rook_loc = to;
	std::string rook_dest = from;
	rook_dest[0] += castle_dir;
	if (!Empty(rook_dest)) return 0; // can't castle if there are pieces on the way
	while (in_bound(rook_loc)) {
		if (!Empty(rook_loc) && toupper(GetPieceName(rook_loc)) != toupper(ROOK)) return 0; // can't castle if there are pieces on the way
		if (toupper(GetPieceName(rook_loc)) == toupper(ROOK)) {
			if (!HasItMoved(from) && !HasItMoved(rook_loc)) {
				return 1;
			}
			return 0;
		}
		rook_loc[0] += castle_dir;
	}
	return 0;
}

bool Board::MakeMove(std::unique_ptr<Move>& move) {
	if (!move->MakeMoveOn(this)) return 0;

	refresh_vision();

	if (CheckMate()) {
		std::cout << "Checkmate!" << std::endl;
		game_over = true;
		who_won = player;
	} else 
	if (Check()) {
		std::cout << "Check!" << std::endl;
	} else
	if (StaleMate()) {
		std::cout << "Stalemate!" << std::endl;
		game_over = true;
		who_won = DRAW;
	}
	
	std::swap(player, opponent);

	return 1;
}

bool Board::IsCaptureMove(const std::string& from, const std::string& to) {
	return player == pieces[from]->Player() && !Empty(to) && player != pieces[to]->Player();
}

bool Board::CanPromote(const std::string& from) {
	// if (Empty(from) || toupper(pieces[from]->Name()) != PAWN) return 0;
	if (player == BLACK) return from[1] == BOT_ROW + 1;
	return from[1] == TOP_ROW - 1;
}

bool Board::MovePiece(const std::string& from, const std::string& to) {
	if (pieces[to] != BLANK) Capture(to);
	pieces[from]->JustMoved();
	pieces[to] = std::move(pieces[from]);

	if (toupper(GetPieceName(to)) == KING) {
		king_loc[player] = to;
	}
	
	last_moved = to;
	
	return 1;
}

bool Board::Check() {
	return visibility_counter[player][king_loc[opponent]] > 0;
}

bool Board::Checked() {
	return visibility_counter[opponent][king_loc[player]] > 0;
}

bool Board::CheckMate() {
	if (!Check()) return 0; // can't be a checkmate if not a check
	if (visibility_counter[opponent][last_moved] > 0) return 0; // not a checkmate if piece can be captured 
	// not a checkmate if king can escape
	for (Piece::Iterator move = pieces[king_loc[opponent]]->begin(this, king_loc[opponent]); move != pieces[king_loc[opponent]]->end(); ++move) {
		if (visibility_counter[player][*move] == 0) { // king can escape here?
			pieces[*move] = std::move(pieces[king_loc[opponent]]);
			refresh_vision();
			bool escaped = visibility_counter[player][*move] == 0;
			pieces[king_loc[opponent]] = std::move(pieces[*move]);
			refresh_vision();
			if (escaped) return 0;
		}
	}
	// not a checkmate if friendly pieces can block the attack
	char name = pieces[last_moved]->Name();
	if (toupper(name) == ROOK || toupper(name) == QUEEN || toupper(name) == BISHOP) {
		int cdir = king_loc[opponent][0] - last_moved[0];
		if (cdir != 0) cdir /= abs(cdir);
		int rdir = king_loc[opponent][1] - last_moved[1];
		if (rdir != 0) rdir /= abs(rdir);
		std::string block = last_moved;
		while (block != king_loc[opponent]) {
			if (Distance(block, king_loc[opponent]) > 1 && visibility_counter[opponent][block] > 0) return 0;
			if (Distance(block, king_loc[opponent]) == 1 && visibility_counter[opponent][block] > 1) return 0;
			block[0] += cdir;
			block[1] += rdir;
		}
	}
	return 1;
}

bool Board::StaleMate() {
	for (const auto& [loc, piece] : pieces) {
		if (piece != BLANK && piece->Player() == opponent && !IsKing(piece)) return 0;
	}
	std::string opponent_king = king_loc[opponent];
	for (Piece::Iterator move = pieces[opponent_king]->begin(this, opponent_king); move != pieces[opponent_king]->end(); ++move) {
		if (*move != opponent_king && visibility_counter[player][*move] == 0) return 0;
	}
	return 1;
}