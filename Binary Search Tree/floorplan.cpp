#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
//removed map std (now using avltree)

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef AVLTree<int, Rectangle> InputMapType;
typedef AVLTree<int, std::pair<int, int> > OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << p.first << "," << p.second;
    return os;
}



void printSolution(std::ostream& os,InputMapType& input,OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it!= output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}



// TODO: Write your backtracking search function here
int rotate(Rectangle& r)
{
    int tem = r.height;
    r.height = r.length;
    r.length = tem;
    return 0;
}

//This helper function checks whether the position is empty or not. 
bool validplace(const Rectangle& r, int x1, int y1, vector<vector<bool>>& grid)
{
    //if the puzzle is longer then grid's length
    if (n < r.length + x1)
    {
        return false;
    }
    //if the puzzle is longer then grid's height
    if(m < r.height + y1 )
    {
        return false;
    }   
    //traverse through all the grid from puzzle's starting coordinate
    for (int i = x1; i < x1+r.length; i++)
    {
        for (int j = y1; j < y1+ r.height; j++)
        {
            if (grid[i][j])
            {
                return false;
            }
        }
    }
    return true;
}


bool btsearch(const Rectangle& r, InputMapType::iterator it, InputMapType& input, 
    OutputMapType& output, vector<vector<bool> >& grid)
{
    //BASE CASE: if all puzzles were set then solved (true)
    if(it == input.end())
    {
        return true;
    }
    //If not, recurse
    else
    {  //explore all the grid

        for(unsigned int i = 0; i < (unsigned)n; i++)
        {
            for(unsigned int j = 0; j < (unsigned)m; j++)
            {  
                //set a copy iterator or input iterator
                InputMapType::iterator temp = it;
                //At first visit, luckily, if it is empty spot
                //update the grid vector bool, and call backtrack
                if(validplace(it->second, i, j, grid)) 
                {
                    //update the bool vector
                    flip(i, j, it->second, grid);
                    output.insert(make_pair(it->first,
                         pair<int, int>(i, j)));
                    
                    if (btsearch(it->second, ++temp,input,output, grid))
                    {
                        return true;
                    } 
                    //unable to set the tile, then restore flip bits and erase.
                    //flip back to backtrack ((clean up)
                     flip(i, j, it->second, grid);
                     output.remove(it->first);             
                    
                }
            }
        }

        rotate(it->second);
        // try the rotate rectangle 

        for(unsigned int i = 0; i < (unsigned)n; i++)
        {
            for(unsigned int j = 0; j < (unsigned)m; j++)
            {  
                //set a copy iterator or input iterator
                InputMapType::iterator temp = it;
                //At first visit, luckily, if it is empty spot
                //update the grid vector bool, and call backtrack
                if(validplace(it->second, i, j, grid)) 
                {
                    //update the bool vector
                    flip(i, j, it->second, grid);
                    output.insert(make_pair(it->first,
                         pair<int, int>(i, j)));
                    
                    if (btsearch(it->second,++temp,input,output, grid))
                    {
                        return true;
                    } 
                    //unable to set the tile,then restore flip bits and erase.
                    //flip back to backtrack
                     flip(i, j, it->second, grid);
                     output.remove(it->first);             
                    
                }
            }
        }
    
    }    
    return false;    
}
    


int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

// TODO:  Call your backtracking search function here

    solution_exists = btsearch(it->second, it, input, output, grid);


    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}
