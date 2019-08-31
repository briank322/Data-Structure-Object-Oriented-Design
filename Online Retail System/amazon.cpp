#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "datastore.h"
#include "msort.h"
#include "review.h"
#include "heap.h"


using namespace std;
//name sort comparator
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
//rating sort comparator
struct Rsort {
  bool operator()(Product* prod1, Product* prod2)
  {
    return (prod1->getAverageRating() > prod2->getAverageRating());
  }
};


//date sort comparator; format: YYYY-MM-DD
struct Dsort { 
    bool operator()(Review* r1, Review* r2) 
    {
        int month1 = stoi(r1->date.substr(5, 2));
        int date1 = stoi(r1->date.substr(8, 2));
        int year1 = stoi(r1->date.substr(0, 4));
        int month2 = stoi(r2->date.substr(5, 2));
        int date2 = stoi(r2->date.substr(8, 2));
        int year2 = stoi(r2->date.substr(0, 4)); 
        //Don't have to consider month, date, if year is larger.
        if(year1 != year2) 
        {
            return year1 > year2;
        }
        else  
        {
            if(month1 != month2 )
            {
                return month1 > month2;
            }
            else 
            {
                return date1 > date2;
            } 
        }             
    }
};

//Prototype for display functions.
void displayReviews(vector<Review*>& review);
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser = new ReviewSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
     parser.addSectionParser("reviews", reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  LOGIN username password                "<<endl;
    cout << "  LOGOUT"<<endl;
    cout << "  AND r/n term term ...                  " << endl;
    cout << "  OR r/n term term ...                   " << endl;
    cout << "  ADD search_hit_number              " << endl;
    cout << "  VIEWCART                           " << endl;
    cout << "  BUYCART                            " << endl;
    cout << "  ADDREV seach_hit_number rating YYYY-MM-DD review_text"<<endl;
    cout << "  VIEWREV seach_hit_number              "<<endl;
    cout << "  REC                                  " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    //define a flag to whether user exist(login) or not.
    vector<Product*> hits;
    bool done = false;
    bool userexist = false;

    string username;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        
        getline(cin,line);
        stringstream ss(line);
        string cmd;

        //Login the user and set all the flag properly.
        if((ss >> cmd)) {
            if(cmd == "LOGIN")
            {
                string exist;
                string password;

                if(!(ss>>exist))
                {
                    cout<<"Invalid user"<<endl;
                }
                //checkuser function checks whether user is valid.
                if(!(ss>>password))
                {
                    cout<<"Invalid password"<<endl;
                }

                if(ds.checkuser(exist,password) == true)
                {
                    userexist = true;
                    username = exist;
                    cout<<"User logged in"<<endl;
                }
                //if username is valid, then finally login.
                if(userexist==true)
                {
                    username = exist;
                }
                //if flag is still false, then it was an invalid user.
                else 
                {
                    cout<<"Invalid login credentials"<<endl;
                }

            }
            //Logout the user and change flag to false
            else if(cmd == "LOGOUT")
            {
                if(username !="")
                {
                    username ="";
                    userexist = false;
                }    
            }


            else if( cmd == "AND") {

                string term;
                string howtosort;
                vector<string> temp;
                Rsort ratingsort;
                ProdNameSorter namesort;

                while(ss>>howtosort)
                {
                    //if "r" was given, Rsort it.
                    if(howtosort == "r")
                    {
                        while(ss >> term) 
                        {
                             temp.push_back(convToLower(term));
                        }
                        //using my mergesort to sort it
                        //Rsort comperator applies msort to be sorted by date
                        
                        hits = ds.search(temp, 0);
                        mergeSort(hits,ratingsort);
                        displayProducts(hits);
                    }

                    else if(howtosort == "n")
                    {
                        while(ss >> term) 
                        {
                            temp.push_back(convToLower(term));
                        }
                    
                        hits = ds.search(temp, 0);
                        mergeSort(hits,namesort);
                        displayProducts(hits);
                    }
                    else
                    {
                        break;
                    }
                }
            }

             else if ( cmd == "OR" ) {
                string term;
                string howtosort;
                vector<string> temp;
                Rsort ratingsort;
                ProdNameSorter namesort;
                while(ss>>howtosort)
                {
                    
                    if(howtosort == "r")
                    {
                        while(ss >> term) 
                        {
                            temp.push_back(convToLower(term));
                        }
                        hits = ds.search(temp, 1);
                        mergeSort(hits,ratingsort);
                        displayProducts(hits);
                    }

                    else if(howtosort == "n")
                    {
                        while(ss >> term) 
                        {
                            temp.push_back(convToLower(term));
                        }
                        hits = ds.search(temp, 1);
                        mergeSort(hits,namesort);
                        displayProducts(hits);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */

            //Adding to the Cart
            else if( cmd == "ADD")
            {
                string itemproduct;
                if(!(ss>>itemproduct))
                {
                    cout<<"Invalid request"<<endl;
                }

                unsigned int numitem = stoi(itemproduct);
                if(numitem<=hits.size() && username !="")
                {
                    ds.addToCart(username, numitem,hits);
                }
                else if(username != "")
                {
                    cout<<"Invalid request"<<endl;
                }
                else
                {
                    cout<<"No current user"<<endl;
                }
            }

            //View cart for the selected user
            else if ( cmd == "VIEWCART")
            {
                if(!(username.empty()))
                {
                    
                     ds.viewCart(username);
                }
                else
                {
                    cout<<"No current user"<<endl;                
                }
            }
            //Buy the product inside the cart for the selected user.
            else if (cmd == "BUYCART")
            {
                if(username=="")
                {
                    cout<<"No current user"<<endl;
                }
                else if(username != "")
                {
                    ds.buyCart(username);
                }
                

            }

            else if ( cmd == "ADDREV") 
            {   
                unsigned int hitnum;
                unsigned int rating;
                string date;
                string review_text;
    
                if(userexist)
                {
                    if((ss >> hitnum >> rating >> date))   
                    {
                        if(ds.checkdate(date))
                        {
                            getline(ss, review_text); 
                            ds.addReview((hits[hitnum-1]->getName()), 
                            rating,username, date, trim(review_text));
                        }
                       
                    
                    } 
                }
                
                else 
                {
                    cout << "No current user" << endl;
                }
            }

            else if ( cmd == "VIEWREV") {
                unsigned int hitnum;
                if(ss >> hitnum) 
                {
                    if(hitnum <= hits.size()) 
                    {
                        Dsort datesort;
                        vector<Review*> review = hits[hitnum-1]->getReviews();
                        mergeSort(review, datesort);
                        displayReviews(review);
                    }
                }
            }
            else if(cmd == "REC")
            {
                if(userexist)
                {
                    ds.makeSuggestion(username);
                }
                else
                {
                    cout << "No current user" << endl;
                }
            }

            else 
            {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}
//commented out the given "std::sort" line as I used my implementation.
void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it)
    {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

//Include new functino that displays reviews.
void displayReviews(vector<Review*>& review)
{
    vector<Review*>::iterator it = review.begin();
    while( it != review.end()) 
    {
        cout << (*it)->date << " " << (*it)->rating << " " 
        << (*it)->username << " " << (*it)->reviewText << endl;
        
        it++;
    }
}
