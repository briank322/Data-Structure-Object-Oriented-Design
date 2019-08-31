#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1,
                   const string* team2,
                   int len)
{
    cout << "\nCombination " << combo++ << endl;
    cout << "T1: ";
    for(int i=0; i < len; i++){
        cout << team1[i] << " ";
    }
    cout << endl;
    cout << "T2: ";
    for(int i=0; i < len; i++){
        cout << team2[i] << " ";
    }
    cout << endl;
}

// You may add additional functions here

// Create a Recursion Helper Function
// Used the same structure from the inclass-exercise: all_letters_combos.

// @param[in] cIdx current index; in order to track&add the n+1th player.
void tHelper(string* players, string* team1, int num_t1, 
    string* team2, int num_t2, int curtotal, int total, int len, int cIdx)
{
    //if the size, total, and lengths of each array is valid,
    if((num_t1>=0)&&(num_t1>=0)&&(curtotal>=0)&&(len>=0))
    {

        curtotal = num_t1+num_t2;
        len = total/2;
    //base case. if current teams are already filled up to total, then ends.
        if(curtotal==total)
        {
        printSolution(team1, team2, len);
        }
    //recursive case
    //two different cases
    //First, if team1 isn't ready = not fulled, then add a user to team 1.
        if(len>num_t1)
        {
        //nth player was just added, lets move on to n+1 player
        team1[num_t1] = players[cIdx];
        tHelper(players, team1,num_t1+1,
            team2, num_t2, curtotal,total,len, cIdx+1 );
        
        }
    //Second, if team2 should be filled up, then add a new user to team 2.
    //Same structure as team1.
        if(len>num_t2)
        {
        //nth player was just added, lets move on to n+1 player
        team2[num_t2] = players[cIdx];
        tHelper(players, team1,num_t1,
            team2, num_t2+1,curtotal, total,len, cIdx+1 );
        
        }
        else
        {
            return;
        }

    }
    else
    {
        cout<<"Invalid input"<<endl;
        return;
    }

}
//Nothing to modify from the helper function.
//Used the structure from in class exercise: all_letters_combos.
void allcombo(string* players, string* team1, string* team2, 
    int num_t1, int num_t2, int curtotal,int total,int len, int cIdx)
{
    tHelper(players, team1, num_t1, 
        team2, num_t2, curtotal,total,len, cIdx);  
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        cerr << "Please provide a file of names" << endl;
        return 1;
    }

    
    // Complete the rest of main
    ifstream infile(argv[1]);
    // if file is unvalid then print error
    if(infile.fail())
    {
        cout<<"Error"<<endl;
        return 1;
    }
    
    //read the numbers of players
    int total = 0;
    infile>>total;
    //if input file is invalid or 
    //number of player is neg-integer, then error.
    if(infile.fail()||total<0)
    {
        cout<<"Error"<<endl;
        return 1;
    }
    
    int cIdx = 0;
    int num_t1 = 0;
    int num_t2 = 0;
    int curtotal = 0;
    //len represents each team's length.
    int len = total/2;
    string* players = new string[total];
    string* team1 = new string[len];
    string* team2 = new string[len];
    
    //reading players name
    int i =0;
    
    //same structure from stream lecture notes
    // we will read players name using while until i < total.
    while (i < total)
    {
        string temp;
        infile>>temp;
        if(infile.fail())
        {
            cout<<"Error"<<endl;
            return 1;
        }
        else if (!infile.fail())
        {
        //reading players names
            players[i] = temp;
            i++;
        }

        //Now we are ready to make the team using our
        //recursive function(including helper function)
        if(i==total)
        {
            allcombo(players,team1,team2,num_t1,
        num_t2,curtotal,total,len,cIdx);
            break;
        }
    }
    
    //erase memory from the heap(deallocate)
    delete[] team1;
    delete[] team2;
    delete[] players;
    
    return 0;
}
