#include "puzzle_solver.h"

using namespace std;

// Constructor (makes a copy of the Board and stores it in b_)
// Also takes a PuzzleHeuristic which will score boards
PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph):
b_(b)
{
	ph_ = ph;
	expansions_ = 0;
	PuzzleMoveScoreComp scorecomp;
	open_list = new Heap <PuzzleMove*, PuzzleMoveScoreComp> (2,scorecomp);
	PuzzleMoveBoardComp boardcomp;
	closed_list = new PuzzleMoveSet(boardcomp);

}

// Destructor
PuzzleSolver::~PuzzleSolver()
{
	delete open_list;
	delete closed_list;
}

// Run the A* search and builds the solution and tracks
// the number of expansions
// Referenced the lecture slide "Graph Algorithm" pg.58
void PuzzleSolver::run()
{
	expansions_ = 0;
	solution_.clear();
	closed_list->clear();
	Board* tem = new Board(b_);
	PuzzleMove* puz_move = new PuzzleMove(tem);
	puz_move-> h = ph_->compute(*puz_move-> b);
	

	open_list->push(puz_move);
	closed_list->insert(puz_move);

	while(!open_list->empty())
	{
		//if s = goal node then trace path back to start; STOP!
		PuzzleMove* current = open_list->top();
		bool flag = current->b->solved();
		Board* tempboard = current->b;
		open_list->pop();

		//if solved, then add.
		if(flag)
		{	
			//if parent is not null, then add.
			while(current->prev != NULL)
			{
				solution_.push_front(current->tileMove);
				current = current->prev;
				flag = false;
			}
			//clean up the closed_list
			for(set<PuzzleMove*>::iterator pt = closed_list->begin();
				pt!=closed_list->end(); ++pt)
			{
				delete *pt;
			}
			return;
		}
		
		//iterate through all the potential moves.
		map<int, Board*> pot_move = (tempboard)->potentialMoves();
		for(map<int, Board*>::iterator it = pot_move.begin();
		 it!=pot_move.end(); ++it)
		{
			PuzzleMove* temp = new PuzzleMove(it->first, it->second, current);
			temp->h = ph_->compute(*(temp->b));
			//add them to open_list and closed_list if they are not in the closed_list
			if(closed_list->find(temp) == closed_list->end())
			{
				if(!flag)
				{
					open_list->push(temp);
					expansions_++;
					closed_list->insert(temp);
				}
			}
			//if not, delete temp.
			else if(closed_list->find(temp) != closed_list->end())
			{
				delete temp;
			}
		}
	}

	//clean up the closed_list
	for(set<PuzzleMove*>::iterator pt = closed_list->begin();
		pt!=closed_list->end(); ++pt)
	{
		delete *pt;
	}

}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution()
{
	return solution_;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}
