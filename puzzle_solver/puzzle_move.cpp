#include "puzzle_move.h"

using namespace std;
// Constructor for starting Board (i.e. initial move)
PuzzleMove::PuzzleMove(Board* board)
{
	b = board;
	g = 0;
	h = 0;
	prev = NULL;
	tileMove = -1;
}
// Constructor for subsequent search boards
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
	b = board;
	prev = parent;
	g = parent->g + 1;
	h = 0;
}

PuzzleMove::~PuzzleMove()
{
	delete b;
}
