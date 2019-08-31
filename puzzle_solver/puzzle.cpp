#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }
  //convert argv to int
 int size = atoi(argv[1]);
 int initMoves = atoi(argv[2]);
 int seed = atoi(argv[3]);
 int heur = atoi(argv[4]);

 // heur 0 = BFS, heur 1 = OutofPlace, heur 2 =Manhattan
 Board puzzleboard(size, initMoves, seed);
 PuzzleHeuristic *puzzleheur = NULL;

 if(heur == 0 || heur == 1 || heur == 2)
 {
 	
 	if(heur == 0){
 		puzzleheur = new PuzzleBFSHeuristic();
 		cout << puzzleboard<<endl;
 	}
 	if(heur == 1){
 		puzzleheur = new PuzzleOutOfPlaceHeuristic();
 		cout << puzzleboard<<endl;
 	}
 	if(heur == 2){
 		puzzleheur = new PuzzleManhattanHeuristic();
 		cout << puzzleboard<<endl;
 	}
 }
 //Invalid heur, print out the error message.
 else
 {
 	cerr << "Usage: ./puzzle size initMoves seed heur! check heur!" << endl;
 	return 1;
 }

 int option;
 while(!puzzleboard.solved())
 {
 	cout<<"Enter tile number to move or -1 for a cheat: ";
 	cin>> option;
 	//If input is not out of the range
 	if(option > 0 && option < size*size)
 	{
 		try{
 			puzzleboard.move(option);
 		}catch(BoardMoveError bme)
 		{
 			cout  << bme.what();
 		}
 		cout <<endl<< puzzleboard<<endl;
 		if(puzzleboard.solved())
 		{
 			delete puzzleheur;
 			return 0;
 		}

 	}
 	//if user wants to cheat
 	if(option == -1)
 	{
 		PuzzleSolver solution(puzzleboard, puzzleheur);
 		solution.run();
 		cout<<"Try this sequence: "<<endl;
 		for(unsigned int i = 0; i<solution.getSolution().size(); i++)
 		{
 			cout<< solution.getSolution()[i]<<" ";
 		}
 		cout<<endl<<"(Expansions = "<<solution.getNumExpansions()<<")"<<endl;
 		cout<<endl<<puzzleboard<<endl;
 	}
 	//if user want to quit, then clean.
 	if(option == 0)
 	{
 		delete puzzleheur;
 		return 0;
 	}
 	
 }
 
 delete puzzleheur;



  return 0;
}
