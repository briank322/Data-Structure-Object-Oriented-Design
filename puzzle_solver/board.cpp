#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;

// Init a board of given dimension (size = dim^2)
Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

//Destructor
Board::~Board()
{
  if(tiles_)
  {
    delete[] tiles_;
  }
  tiles_ = NULL;
}
// Copy constructor
Board::Board(const Board& b)
{
  size_ = b.size();
  tiles_ = new int [size_];
  for (int i = 0; i<size_; i++)
  {
    tiles_[i] = b.tiles_[i];
  }

}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    stringstream ss;
    ss << "Invalid move of tile " << tile << " at ";
    ss << tr << "," << tc << " and blank spot at ";
    ss << br << "," << bc << endl;
    throw BoardMoveError(ss.str());
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> board;

  int side_dim = dim();
  int br, bc;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;
  //check left 
  if(bc >= 1)
  {
    Board* left = new Board(*this);
    left->move(tiles_[j-1]);
    //make pair
    board[tiles_[j-1]]=left;
  }
  //check up 
  if(br >= 1)
  {
    Board* up = new Board(*this);
    up->move(tiles_[j-side_dim]);
    //make pair
    board[tiles_[j-side_dim]] = up;
  }
  //check right 
  if(bc <= side_dim-2)
  {
    Board* right = new Board(*this);
    right->move(tiles_[j+1]);
    //make pair
    board[tiles_[j+1]] = right;
  }
  //check down
  if(br <= side_dim-2)
  {
    Board* down = new Board(*this);
    down->move(tiles_[j+side_dim]);
    //make pair
    board[tiles_[j+side_dim]] = down;
  }
  return board;
}

// Complete this function
bool Board::solved() const
{
  bool solved = true;
  for(int i = 0; i< size_; i++)
  {
    if(tiles_[i] != i)
    {
      return false;
    }
  }
  return solved;

}

// Checks if this board is less-than another.  
bool Board::operator<(const Board& rhs) const
{
  for(int i = 0; i<this->size_; i++)
  {
    if( (*this)[i]< rhs[i])
    {
      return true;
    }
    else if( (*this)[i]> rhs[i])
    {
      return false;
    }
  }
  return false;
}

// Prints the board in the desired 2D format
ostream& operator<<(std::ostream &os, const Board &b)
{
  int side_dim = b.dim();
  b.printRowBanner(os);

  if(side_dim==0)
  {
    return os;
  }
  else
  {
      for(int i = 0; i<side_dim; i++)
      {
        os<<"|";
        for(int j = 0; j<side_dim; j++)
        {
          if(b[j+side_dim*i] != 0)
          {
            os<<setw(2)<<b[j+side_dim*i]<<"|";
          }
          else if(b[j+side_dim*i] == 0)
          {
            os << "  |";
          }
        }
        os<<endl;
        b.printRowBanner(os);
      }
  }
  
  return os;
}

// Returns the tile value at location, loc
const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
