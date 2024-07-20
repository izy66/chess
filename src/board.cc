#include "board.h"
#include "moves/move.h"
#include "player/player.h"
#include "player/human_player.h"
#include "player/computer_player.h"
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
		if (player != nullptr) player->RefreshVision();
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
	draw = false;
	player = WHITE;
	opponent = BLACK;
}

void Board::AddHumanPlayer(char player) { 
	players[player] = std::make_shared<HumanPlayer>(this, player); 
}

void Board::AddComputerPlayer(char player, int level) {
	players[player] = std::make_shared<ComputerPlayer>(this, player, level);
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

void Board::MovePiece(const std::string& from, const std::string& to) noexcept {
	pieces[to] = std::move(pieces[from]);
	move_path.push(to);
}

void Board::UndoMove(const std::string& from, const std::string& to) noexcept {
	pieces[from] = std::move(pieces[to]);
	move_path.pop();
}

void Board::KingIsHere(const std::string& loc) {
	if (pieces[loc] != nullptr) king_loc[pieces[loc]->Player()] = loc;
}

std::shared_ptr<Piece> Board::Capture(const std::string& loc) {
	if (pieces[loc] != BLANK) {
		if (pieces[loc]->Name() == KING) {
			game_over = true;
			++scores[player];
			return nullptr;
		}
		captured_by[player].emplace_back(pieces[loc]->Print());
		auto capture = std::move(pieces[loc]);
		pieces[loc] = BLANK;
		return capture;
	}
	return nullptr;
}

void Board::Release(std::shared_ptr<Piece> piece) {
	if (piece != nullptr) {
		pieces[piece->Location()] = piece;
		if (piece->Player() == WHITE) captured_by[BLACK].pop_back();
		if (piece->Player() == BLACK) captured_by[WHITE].pop_back();
	}
}

bool Board::CanBeCaptured(const std::string& loc, char player) {
	if (player == WHITE) return players[BLACK]->CanCapture(loc);
	if (player == BLACK) return players[WHITE]->CanCapture(loc);
}

bool Board::CanBeSeen(const std::string& loc, char player) {
	if (player == WHITE) return players[BLACK]->CanSee(loc);
	if (player == BLACK) return players[WHITE]->CanSee(loc);
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

void Board::MakeMove(std::unique_ptr<AbstractMove> move) {

	try {
		move->MakeMoveOn(this);
		moves.emplace(std::move(move));
	} catch (...) {
		throw;
	}

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

void Board::Undo() {
	if (moves.empty()) {
		throw _invalid_move_{"Can't undo anymore!"};
	}
	moves.top()->Undo();
	moves.pop();
	Print();
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

bool Board::IsRevealingKing(Piece* piece, const std::string& to) {
	auto tmp = piece->Location();
	auto capture = pieces[to];
	piece->TakeMove(to);
	players[opponent]->RefreshVision();
	bool king_under_attack = players[opponent]->CanSee(king_loc[player]);
	piece->UndoMove(tmp);
	pieces[to] = capture;
	players[opponent]->RefreshVision();
	return king_under_attack;
}

bool Board::IsCheckMove(const std::shared_ptr<Piece>& piece, const std::string& to) {
	if (piece->Player() == GetPiecePlayer(to) || !piece->CanCover(to)) return 0;
	auto from = piece->Location();
	piece->TakeMove(to);
	players[player]->RefreshVision();
	bool check = Check();
	piece->UndoMove(from);
	players[player]->RefreshVision();
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
	if (piece->Player() == GetPiecePlayer(to) || !piece->CanCover(to)) return 0;
	auto from = piece->Location();
	piece->TakeMove(to);
	refresh_vision();
	bool check_mate = CheckMate();
	piece->UndoMove(from);
	refresh_vision();
	return check_mate;
}

std::string Board::TryCheckMate(const std::shared_ptr<Piece>& piece) {
	Piece::Iterator move = piece->begin();
	++move;
	while (move != piece->end()) {
		if (IsCheckMate(piece, *move)) return *move;
		++move;
	}
	return "";
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
	auto last_moved = move_path.top();
	if (CanBeCaptured(last_moved, player)) return 0;
	
	// not a checkmate if king can escape
	std::string opponent_king_loc = king_loc[opponent];
	auto opponent_king = pieces[opponent_king_loc];

	for (Piece::Iterator move = opponent_king->begin(); move != opponent_king->end(); ++move) {
		if (!players[player]->CanSee(*move)) { // king can escape here?
			
			bool escaped = false;
			
			opponent_king->TakeMove(*move);
			players[player]->RefreshVision();
			
			escaped = !players[player]->CanSee(*move);
			
			opponent_king->UndoMove(opponent_king_loc);
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