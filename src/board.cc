#include "board.h"
#include "moves/move.h"
#include "pieces/blank.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "player/player.h"
#include "player/human_player.h"
#include "player/random_player.h"
#include "player/beginner_player.h"
#include <iostream>

void Board::SetPiece(const std::string& loc, char name, char player) {
	if (name == GetPieceName(loc)) return; // don't need to set again
	switch(tolower(name)) {
		case 'k':
			if (king_loc[player] != "") {
				throw _two_kings_{};
			}
			pieces[loc] = std::make_shared<King>(this, loc, player);
			king_loc[player] = loc;
			break;
		case 'q':
			pieces[loc] = std::make_shared<Queen>(this, loc, player);
			break;
		case 'b':
			pieces[loc] = std::make_shared<Bishop>(this, loc, player);
			break;
		case 'n':
			pieces[loc] = std::make_shared<Knight>(this, loc, player);
			break;
		case 'p':
			if (loc[1] == BOT_ROW || loc[1] == TOP_ROW) {
				throw _pawn_first_rank_{};
			}
			pieces[loc] = std::make_shared<Pawn>(this, loc, player);
			break;
		case 'r':
			pieces[loc] = std::make_shared<Rook>(this, loc, player);
			break;
	}
}

void Board::refresh_vision() {
	for (const auto& [team, player] : players) {
		player->RefreshVision();
	}
}

char Board::GetPieceName(const std::string& loc) { 
	if (Empty(loc)) return ' ';
	return pieces[loc]->Name();
}

char Board::GetPiecePlayer(const std::string& loc) {
	if (Empty(loc)) return ' ';
	return pieces[loc]->Player();
}

char Board::PrintPieceName(const std::string& loc) {
	if (Empty(loc)) return ' ';
	return pieces[loc]->Print();
}

void Board::RemovePiece(const std::string& loc) {
	if (pieces[loc] != BLANK && pieces[loc]->IsKing()) king_loc[GetPiecePlayer(loc)] = "";
	pieces[loc] = BLANK;
}

void Board::PlayerMovesNext(char next_player) {
	if (next_player == WHITE) { player = WHITE; opponent = BLACK; }
	if (next_player == BLACK) { player = BLACK; opponent = WHITE; }
}

void Board::Clear() {
	for (char c = LEFT_COL; c <= RIGHT_COL; ++c) {
		for (char r = BOT_ROW; r <= TOP_ROW; ++r) {
			RemovePiece(std::string() + c + r);
		}
	}
	king_loc[player] = king_loc[opponent] = "";
	for (const auto& [team, player] : players) {
		player->DiscardHand();
	}
}

void Board::Print() { 
	refresh_vision();
	NotifyObservers(); 
}

void Board::SetUpDone() { 
	if (king_loc[WHITE] == "") {
		throw _missing_white_king_{};
	}
	if (king_loc[BLACK] == "") {
		throw _missing_black_king_{};
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
	captured = false;
	draw = false;
	player = WHITE;
	opponent = BLACK;
}

void Board::AddHumanPlayer(char player) { 
	players[player] = std::make_shared<HumanPlayer>(this, player); 
	for (const auto& [loc, piece] : pieces) {
		if (piece != BLANK && piece->Player() == player) players[player]->AddPiece(piece);
	}
}

void Board::AddComputerPlayer(char player, int level) {
	players[player] = std::make_shared<RandomPlayer>(this, player);
	if (level >= 2) players[player] = std::make_shared<BeginnerPlayer>(players[player], this, player);

	for (const auto& [loc, piece] : pieces) {
		if (piece != BLANK && piece->Player() == player) players[player]->AddPiece(piece);
	}
}

void Board::PlayerMakeMove() {
	if (player == WHITE) {
		std::cout << "White to move." << std::endl;
	} else {
		std::cout << "Black to move." << std::endl;
	}
	try {
		players[player]->TakeAction();
	} catch (...) {
		throw;
	}
	std::swap(player, opponent);
}

void Board::DisplayScores() {
	std::cout << "White score: " << scores[WHITE] << std::endl;
	std::cout << "Black score: " << scores[BLACK] << std::endl;
}

void Board::Capture(const std::string& loc) {
	if (pieces[loc] != BLANK) {
		if (pieces[loc]->Name() == KING) {
			game_over = true;
			++scores[player];
			return;
		}
		captured_by[player].emplace_back(PrintPieceName(loc));
		pieces[loc]->Captured();
		captured_pieces.push(std::move(pieces[loc]));
		pieces[loc] = BLANK;
	}
}

void Board::Promote(const std::string& loc, char promotion) {
	pieces[loc]->Promoted();
	promoted.emplace(std::move(pieces[loc]));
	SetPiece(loc, promotion, player);
	players[player]->AddPiece(pieces[loc]);
}

void Board::Recapture(const std::string& loc) {
	pieces[loc] = std::move(captured_pieces.top());
	if (pieces[loc]->Player() == BLACK) captured_by[WHITE].pop_back();
	else captured_by[BLACK].pop_back();
	captured_pieces.pop();
}

bool Board::CanBeCaptured(const std::string& loc) {
	return players[opponent]->CanSee(loc);
}

std::string Board::BestCaptureMove(const std::shared_ptr<Piece>& piece) {
	int highest_rank = -1;
	std::string best_move = "";
	Piece::Iterator move = piece->begin();
	for (; move != piece->end(); ++move) {
		int captured_rank = get_rank(toupper(GetPieceName(*move)));
		if (!Empty(*move) && GetPiecePlayer(*move) != piece->Player() && captured_rank > highest_rank) {
			highest_rank = captured_rank;
			best_move = *move;
		}
	}
	return best_move;
}

std::vector<char> Board::CapturedBy(char player) {
	return captured_by[player];
}

bool Board::ValidMove(const std::string& from, const std::string& to) noexcept {
	return pieces[from]->ValidMove(to);
}

bool Board::IsEnPassant(const std::string& from, const std::string& to) {
	if (!pieces[from]->IsPawn() || from[0] == to[0] || abs(from[1] - to[1]) > 1) return 0;
	std::string en_passant_loc = std::string() + to[0] + from[1];
	return !Empty(en_passant_loc) && pieces[en_passant_loc]->IsPawn() &&
			pieces[en_passant_loc]->FirstMove() && last_moved == en_passant_loc;
}

bool Board::IsCastling(const std::string& from, const std::string& to) {
	if (!pieces[from]->IsKing() || Checked()) return 0; // can't castle if not king or king in check
	if (HasItMoved(from)) return 0; // can't castle if king has moved
	if (abs(to[0] - from[0]) != 2 || to[1] != from[1]) return 0;
	int castle_dir = (to[0] - from[0]) / 2;
	std::string rook_loc = to;
	std::string rook_dest = from;
	rook_dest[0] += castle_dir;
	if (!Empty(rook_dest)) return 0; // can't castle if there are pieces on the way
	while (InBound(rook_loc)) {
		if (!Empty(rook_loc) && toupper(GetPieceName(rook_loc)) != toupper(ROOK)) return 0; // can't castle if there are pieces on the way
		if (toupper(GetPieceName(rook_loc)) == toupper(ROOK)) {
			if (!HasItMoved(rook_loc)) {
				return 1;
			}
			return 0;
		}
		rook_loc[0] += castle_dir;
	}
	return 0;
}

void Board::MakeMove(std::unique_ptr<Move> move) {
	
	try {
		move->MakeMoveOn(this);
	} catch (...) {
		throw;
	}

	moves.emplace(std::move(move));
	Print();

	if (game_over) return;
	
	if (CheckMate()) {
		std::cout << "Checkmate!" << std::endl;
		++scores[player];
		game_over = true;
	} else 
	if (Check()) {
		std::cout << "Check!" << std::endl;
	} else
	if (StaleMate()) {
		std::cout << "Stalemate!" << std::endl;
		scores[player] += 0.5;
		scores[opponent] += 0.5;
		game_over = true;
	}
}

bool Board::IsCaptureMove(const std::string& from, const std::string& to) {
	return player == pieces[from]->Player() && !Empty(to) && player != pieces[to]->Player();
}

bool Board::CanPromote(const std::string& from) {
	if (Empty(from) || !pieces[from]->IsPawn()) return 0;
	if (player == BLACK) return from[1] == BOT_ROW + 1;
	return from[1] == TOP_ROW - 1;
}

bool Board::CanMove(const std::string& loc) {
	Piece::Iterator move = pieces[loc]->begin(loc);
	++move;
	while (move != pieces[loc]->end() && GetPiecePlayer(*move) == GetPiecePlayer(loc)) ++move;
	return move != pieces[loc]->end();
}

std::string Board::MakeRandomMove(const std::shared_ptr<Piece>& piece) {
	int count_moves = 0;
	Piece::Iterator move = piece->begin();
	while (move != piece->end()) {
		++move;
		if (piece->ValidMove(*move)) ++count_moves;
	}
	// srand(time(NULL));
	int rand_move = rand() % count_moves + 1;
	move = piece->begin();
	while (rand_move) {
		++move;
		if (piece->ValidMove(*move)) --rand_move;
	}
	return *move;
}

bool Board::IsProtectingKing(const std::string& loc) {
	auto temp = std::move(pieces[loc]);
	players[opponent]->RefreshVision();
	bool king_under_attack = players[opponent]->CanSee(king_loc[player]);
	pieces[loc] = std::move(temp);
	return king_under_attack;
}

void Board::Undo() {
	moves.pop();
}

bool Board::IsCheckMove(const std::shared_ptr<Piece>& piece, const std::string& to) {
	if (piece->Player() == GetPiecePlayer(to) || !piece->ValidMove(to)) return 0;
	auto tmp = pieces[to];
	auto loc_mem = piece->Location();
	piece->TakeMove(to);
	pieces[to] = piece;
	refresh_vision();
	auto check = Check();
	piece->TakeMove(loc_mem);
	refresh_vision();
	return check;
}

std::string Board::TryCheckMove(const std::shared_ptr<Piece>& piece) {
	Piece::Iterator move = piece->begin();
	while (move != piece->end()) {
		++move;
		if (IsCheckMove(piece, *move)) return *move;
	}
	return "";
}

bool Board::IsCheckMate(const std::shared_ptr<Piece>& piece, const std::string& to) {
	auto tmp = std::move(pieces[to]);
	auto loc_mem = piece->Location();
	piece->TakeMove(to);
	pieces[to] = piece;
	refresh_vision();
	bool check_mate = CheckMate();
	piece->TakeMove(loc_mem);
	pieces[to] = tmp;
	refresh_vision();
	return check_mate;
}

std::string Board::TryCheckMate(const std::shared_ptr<Piece>& piece) {
	Piece::Iterator move = piece->begin();
	while (move != piece->end()) {
		if (IsCheckMate(piece, *move)) return *move;
		++move;
	}
	return "";
}

void Board::MovePiece(const std::string& from, const std::string& to) noexcept {
	if (pieces[to] != BLANK) Capture(to);

	pieces[from]->TakeMove(to);
	pieces[to] = std::move(pieces[from]);

	if (pieces[to]->IsKing()) {
		king_loc[player] = to;
	}
	
	last_moved = to;
}

bool Board::Check() {
	return players[player]->CanSee(king_loc[opponent]);
}

bool Board::Checked() {
	return players[opponent]->CanSee(king_loc[player]);
}

bool Board::CheckMate() {
	// can't be a checkmate if not a check
	if (!Check()) return 0; 
	// not a checkmate if piece can be captured 
	if (players[opponent]->CanSee(last_moved)) return 0;
	// not a checkmate if king can escape
	auto opponent_king = pieces[king_loc[opponent]];
	for (Piece::Iterator move = opponent_king->begin(); move != opponent_king->end(); ++move) {
		if (!players[player]->CanSee(*move)) { // king can escape here?
			bool escaped = false;
			pieces[*move] = std::move(pieces[king_loc[opponent]]);
			pieces[*move]->TakeMove(*move);
			players[player]->RefreshVision();
			escaped = players[player]->CanSee(*move) == 0;
			pieces[king_loc[opponent]] = std::move(pieces[*move]);
			pieces[king_loc[opponent]]->TakeMove(king_loc[opponent]);
			pieces[king_loc[opponent]]->UndoMoved();
			players[player]->RefreshVision();
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
			if (Distance(block, king_loc[opponent]) > 1 && players[opponent]->CanSee(block) > 0) return 0;
			if (Distance(block, king_loc[opponent]) == 1 && players[opponent]->CanSee(block) > 1) return 0;
			block[0] += cdir;
			block[1] += rdir;
		}
	}
	return 1;
}

bool Board::StaleMate() {
	for (const auto& [loc, piece] : pieces) {
		if (piece != BLANK && piece->Player() == opponent && !pieces[loc]->IsKing()) return 0;
	}
	auto opponent_king = pieces[king_loc[opponent]];
	for (Piece::Iterator move = opponent_king->begin(); move != opponent_king->end(); ++move) {
		if (*move != king_loc[opponent] && !players[player]->CanSee(*move)) return 0;
	}
	return 1;
}