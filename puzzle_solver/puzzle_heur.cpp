#include "puzzle_heur.h"
#include <iostream>
#include <cmath>

using namespace std;

// counts Manhattan distance of each tile
int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int ManDist = 0;
	int side_dim = b.dim();
	for (int i = 0; i<side_dim * side_dim; i++)
	{
		//exclude blank!
		if(b[i] != 0)
		{   
			//add delta row and delta column
			ManDist += abs(i/side_dim - b[i]/side_dim)
				+abs(i%side_dim - b[i]%side_dim);
		}
	}
	return ManDist;
}

// Counts the number of tiles out of place
// Exclude the blank!
int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int inplace = 0;
	int side_dim = b.dim();
	for(int i = 0; i < side_dim * side_dim; i++)
	{
		if(b[i] == i || b[i] == 0)
		{
			inplace++;
		}
	}
	return (side_dim*side_dim-inplace);
}

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}
