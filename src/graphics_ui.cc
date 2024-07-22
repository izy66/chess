#include "graphics_ui.h"
#include <iostream>
#include <string>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define BOARD_SIZE 8
#define SQUARE_SIZE (WINDOW_WIDTH / BOARD_SIZE)

// Define colors for the light and dark squares
#define LIGHT_COLOR 0xeeeed2
#define DARK_COLOR 0x769656
#define WHITE_PIECE 0xFFCACA
#define BLACK_PIECE 0x4b4847
#define WHITE_CAPPED_PIECE 0xE97451
#define BLACK_CAPPED_PIECE 0x702963

#define PIECE_SIZE 6

const char *king_piece[] = {
	"K    K",
	"K   K ",
	"K K   ",
	"K  K  ",
	"K   K ",
	"K    K"
};

const char *queen_piece[] = {
	" QQQ  ",
	"Q    Q",
	"Q    Q",
	"Q    Q",
	" Q  Q ",
	"   QQQ"
};

const char *knight_piece[] = {
	"N    N",
	"NN   N",
	"N N  N",
	"N  N N",
	"N   NN",
	"N    N"
};

const char *bishop_piece[] = {
	"B BB  ",
	"B    B",
	"BBB B ",
	"B    B",
	"B   B ",
	"B BB  "
};


const char *rook_piece[] = {
	"RRRR  ",
	"R   R ",
	"R  R  ",
	"RR R  ",
	"R   R ",
	"R    R"
};

const char *pawn_piece[] = {
	"P PPP ",
	"P    P",
	"P    P",
	"P PP  ",
	"P     ",
	"P     "
};

GraphicsUI::GraphicsUI(Board* board) : chess_board{board}, display{nullptr}, window{0}, gc{0} {
  chess_board->Attach(this);
  display = XOpenDisplay(nullptr);
  if (display == nullptr) {
    std::cerr << "Cannot open display\n";
    exit(1);
  }
  screen = DefaultScreen(display);
  width = WINDOW_WIDTH;
  height = WINDOW_HEIGHT;
  cell_size = width / BOARD_SIZE;

  window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XMapWindow(display, window);
  gc = DefaultGC(display, screen);

  Notify();
}

GraphicsUI::~GraphicsUI() {
  XCloseDisplay(display);
}

void GraphicsUI::Notify() {
  XClearWindow(display, window);
  DrawBoard();
  DrawPieces();
  XFlush(display);
}

void GraphicsUI::Init() {
  Notify();
  XEvent event;
  while (true) {
    XNextEvent(display, &event);
    if (event.type == Expose) {
      Notify();
    }
    if (event.type == KeyPress) {
      break;
    }
  }
}

void GraphicsUI::DrawBoard() {
  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      int x = col * SQUARE_SIZE;
      int y = row * SQUARE_SIZE;

      // Alternate colors for the squares
      if ((row + col) % 2 == 0) {
        XSetForeground(display, gc, LIGHT_COLOR);
      } else {
        XSetForeground(display, gc, DARK_COLOR);
      }

      XFillRectangle(display, window, gc, x, y, SQUARE_SIZE, SQUARE_SIZE);
    }
  }
}

void GraphicsUI::DrawPieces() {
  for (char r = '8'; r >= '1'; --r) {
    for (char c = 'a'; c <= 'h'; ++c) {
      std::string loc = std::string() + c + r;
      char piece = chess_board->GetPieceName(loc);
      char player = chess_board->GetPiecePlayer(loc);
      if (piece != ' ') {
        DrawPiece(piece, player, c - 'a', '8' - r);
      }
    }
  }
}

void GraphicsUI::DrawPiece(char piece, char player, int x, int y) {
  // int x_pos = x * cell_size;
  // int y_pos = y * cell_size;
  // unsigned long color = (player == WHITE) ? WhitePixel(display, screen) : BlackPixel(display, screen);
  // XSetForeground(display, gc, color);
  // XDrawString(display, window, gc, x_pos + cell_size / 2, y_pos + cell_size / 2, &piece, 1);

  int piece_height = PIECE_SIZE;
  int piece_width = PIECE_SIZE;
  int x_offset = x * SQUARE_SIZE + (SQUARE_SIZE - piece_width * 10) / 2;
  int y_offset = y * SQUARE_SIZE + (SQUARE_SIZE - piece_height * 10) / 2;

  auto piece_display = king_piece;

  switch (toupper(piece)) {
    case KING:
      piece_display = king_piece;
      break;
    case QUEEN:
      piece_display = queen_piece;
      break;
    case BISHOP:
      piece_display = bishop_piece;
      break;
    case ROOK:
      piece_display = rook_piece;
      break;
    case PAWN:
      piece_display = pawn_piece;
      break;
    case KNIGHT:
      piece_display = knight_piece;
      break;
    default:
      break;
  }

  if (player == BLACK) XSetForeground(display, gc, BLACK_PIECE);
  if (player == WHITE) XSetForeground(display, gc, WHITE_PIECE);
  char c = 'a' + x;
  char r = '8' - y;
  if (chess_board->CanBeCaptured(std::string() + c + r, player)) {
    XSetForeground(display, gc, player == WHITE ? WHITE_CAPPED_PIECE : BLACK_CAPPED_PIECE);
  }

  for (int i = 0; i < piece_height; i++) {
    for (int j = 0; j < piece_width; j++) {
      if (piece_display[i][j] != ' ') {
        int x = x_offset + j * 10;
        int y = y_offset + i * 10;
        XFillRectangle(display, window, gc, x, y, 10, 10);
      }
    }
  }

}