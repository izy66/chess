#ifndef GRAPHICS_UI_H
#define GRAPHICS_UI_H

#include "observer.h"
#include "board.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <memory>

class GraphicsUI : public Observer {
	Board* chess_board;
	Display* display;
	Window window;
	GC gc;
	int screen;
	unsigned int width;
	unsigned int height;
	unsigned int cell_size;

	void DrawBoard();
	void DrawPieces();
	void DrawPiece(char piece, char player, int x, int y);
	
	public:
  
	  GraphicsUI(Board* chess_board);
    ~GraphicsUI();
    void Notify() override;
    void Init();
};

#endif