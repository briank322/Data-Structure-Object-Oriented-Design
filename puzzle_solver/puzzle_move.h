#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include "board.h"

using namespace std;

struct PuzzleMove
{
  // Data members can be public
  int tileMove;  // tile moved to reach the Board b
  Board *b;      // Pointer to a board representing the updated state
  int g;         // distance from the start board
  int h;         // heuristic distance to the goal
  PuzzleMove *prev;  // Pointer to parent PuzzleMove


  // Constructor for starting Board (i.e. initial move)
  PuzzleMove(Board* board);

  // Constructor for subsequent search boards 
  // (i.e. those returned by Board::potentialMoves() )
  PuzzleMove(int tile, Board* board, PuzzleMove *parent);

  // Destructor
  ~PuzzleMove();

};


struct PuzzleMoveScoreComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    // Add code to check if m1's f-score is less than m2's
    // If both have the same f-score, break ties by 
    // checking if m1's h-score is less than m2's.
    // If both have the same f and same h score, break ties
    // by returning true when m1's tileMove is less than m2's.
    int m1F = m1->g + m1->h;
    int m2F = m2->g + m2->h;
    int m1H = m1->h;
    int m2H = m2->h;
    int m1T = m1->tileMove;
    int m2T = m2->tileMove;

    if((m1F)<(m2F))
    {
      return true;
    }
    if((m1F)>(m2F))
    {
      return false;
    }
    else 
    {
      if(m1H < m2H)
      {
        return true;
      }
      else if(m1H > m2H)
      {
        return false;
      }
      else
      {
        return(m1T<m2T);
      }
    }
   
  }
};

struct PuzzleMoveBoardComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    // Add code to check if m1's board is "less-than" m2's board by 
    // using the Board class' operator<()
    Board* board1 = m1->b;
    Board* board2 = m2->b;
    if(*board1<*board2)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

#endif
