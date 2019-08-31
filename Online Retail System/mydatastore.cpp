#include "mydatastore.h"
#include "hash.h"
#include "heap.h"
#include <iostream>
#include <fstream>

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{

    //delete products
    vector<Product*>::iterator i = products.begin();
    while( i != products.end())
    {
        delete *i;
        ++i;
    }
    //delete users and carts
    vector<User*>::iterator j = users.begin();
    while(j != users.end())
    {
        delete *j;
        ++j;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products.push_back(p);
    
    // Initializes set of strings
    // Keys becomes p's keywords
    set<string> keys= p->keywords();
    set<string>::iterator key_it= keys.begin();
    
    // Iterates through p's keywords
    while(key_it != keys.end())
    {
        // If key doesn't already exist, makes pair
        if (product_keyword.find(*key_it) == product_keyword.end())
        {
            set<Product*> keyhits;
            keyhits.insert(p);
            product_keyword.insert(make_pair(*key_it, keyhits));
        }
        // If key exists, updates set
        else
        {
            (product_keyword.find(*key_it)->second).insert(p);
        }
        ++key_it;
    }    
}

void MyDataStore::addUser(User* u)
{
    //add user to users container
    users.push_back(u);
    
}
/**
Performs a search of products whose keywords match the given "terms"
type 0 = AND search (intersection of results for each term) while
type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& 
    terms, int type)
{
    //temporary soultion vector that will be the output of each search.
    set<Product*> set_sol;

    //output vector that will return the results of Both AND, OR search
    vector<Product*> results;

    // If terms is empty return empty results.
    if (terms.empty())
    {
        return results;
    } 
    
    // AND search 
    if (type == 0)
    {
        set<Product*> set_and;
        // Instead of iterating all products, use setIntersection(O(nlogn))
        for (unsigned int i = 0; i < terms.size(); i++)
        {

            if(set_and.empty())
            {
                set_and = product_keyword[terms[i]];
            }
            
            set_and = setIntersection(product_keyword[terms[i]],set_and);   
        }
        set_sol = set_and;
    }
    // OR search (union)
    else if (type == 1)
    {
        set<Product*> set_or;
        // Instead of iterating all products, use setUnion(O(nlogn))
        for (unsigned int i = 0; i < terms.size(); i++)
        {
            set_or = setUnion(product_keyword[terms[i]],set_or);
        }
        set_sol = set_or;
    }
    //Finalize the return value
    //set_sol is our output set for both AND & OR.
    //vector<Product*> result;
    set<Product*>::iterator it = set_sol.begin();
    while(it != set_sol.end())
    {
        results.push_back(*it);
        ++it;
    }
    return results;
}
//Reproduce the database file from the curren Products and User values.
void MyDataStore::dump(std::ostream& ofile)
{
    //make a review vector for review dump
    vector<Product*>::iterator pt = products.begin();
    vector<User*>::iterator st = users.begin();
    vector<Review*> reviews;

    ofile << "<products>"<<endl;

    //dump out products 
    while(pt != products.end())
    {
         (*pt)->dump(ofile);
         ++pt;
    }

    ofile << "</products>"<<endl;

    ofile << "<users>"<<endl;

    //dump out user's information
    while(st != users.end())
    {
        (*st)->dump(ofile);
        ++st;
    }

    ofile << "</users>"<<endl;

    vector<Product*>::iterator rt = products.begin();
    
    ofile << "<reviews>"<<endl;
    //dump out reviews 
    while(rt != products.end()) 
    {
        reviews = (*rt)->getReviews();
        unsigned int l = 0;
        while(l < reviews.size()) 
        {
            ofile << (*rt)->getName() << endl;
            reviews[l]->dump(ofile);
            l++;
        }
        ++rt;
        
    }
    ofile << "</reviews>"<<endl;
}

void MyDataStore::addToCart(std::string username, 
    unsigned int n_hit,std::vector<Product*> hits)
{
    //value of carts(key, value)
    vector<Product*> prod_new;
    
    //username is not on the carts 
    if(carts.find(username) != carts.end()) 
    {
        carts.find(username)->second.push_back(hits[n_hit-1]);
    }
    //if username is on the carts then make it pair.
    else 
    {
        if(n_hit <= hits.size()) 
        { //within range of correct index
            prod_new.push_back(hits[n_hit-1]);
            carts.insert(make_pair(username, prod_new));
        }
    }

       
}
//Print the products in username's cart at the current time.
void MyDataStore::viewCart(std::string username)
{
    //if username and carts are valid, then display. 
    if(carts.find(username) != carts.end()) 
    { 
        vector<Product*> items = carts.find(username)->second;
        for(unsigned int i = 0; i < items.size(); i++) 
        {
            cout << "Item " << i+1 << endl<<
            items[i]->displayString() << endl<<endl;
        }
    }
}

//Buy all the product that are in the cart.
void MyDataStore::buyCart(std::string username)
{
   
    map<string, vector<Product*> >::iterator it = carts.find(username);
    User* user; 

    if(carts[username].size() <= 0) 
    {
        return;
    }   
    //update the user to users[i]
    for(unsigned int i = 0; i < users.size(); i++) 
    {
        if(users[i]->getName() == username)
        {
            user = users[i];
        }
    }

    //use pass by reference to modify useritems
    vector<Product*> &useritems = it->second; 
    vector<Product*>::iterator item = useritems.begin();
    //index traverser
    unsigned int i = 0;

    while( i < useritems.size() ) 
    {
        double price = useritems[i]->getPrice();
        // Do not increase the counter because item has been removed.
        if(user->getBalance() >= price && (useritems[i]->getQty() != 0)) 
        { 
            ///if user has enough balance and if item has enough qty.
            //Then buy (take out from the cart)
            useritems[i]->subtractQty(1);
            user->deductAmount(price);
            for(unsigned int k =0;k<i;k++)
            {
                item++;
            }
            useritems.erase(item); 
             
        } 
        //if no removal, then increase the counter
        else
        {
            i++;
        }
    }
    
    
}

//ADDreview by iterating through the product vector
void  MyDataStore::addReview(const std::string& prodName,
    int rating,const std::string& username,
    const std::string& date,const std::string& review_text)
{
     bool prodfind = false;
     vector<Product*>::iterator it = products.begin();

     while(it!=products.end())
    {
        //if found the valid user then change bool 
        //so we can print Invalid at the end.
        if ((*it)->getName()==prodName)
        {
            prodfind = true;
            break;
        }
        ++it;
    }
    if(prodfind == false )
    {
        return;
    }
    else
    {
        Review* newreview = new Review(rating, username, date, review_text);
        for(unsigned int i = 0; i < products.size(); i++) 
        {
            if(products[i]->getName() == prodName) 
            {
                products[i]->reviewadd(newreview);
            }
        }
    }
}

//check whether the user is valid or not
bool MyDataStore::checkuser(std::string username,std::string password)
{
    std::vector<User*>::iterator it = users.begin();
    unsigned long long temp = hashfunction(password);
    while( it != users.end())
    {
        //unsigned long long match = hash(password);
        //compare stored username and input(username)
        if(!((*it)->getName()).compare(username))
        {
            if((((*it)->getHashcode())==temp))
            {
                return true;
            }
        }
        
        ++it;
        
    }
    return false;
        
}
//CHECk whether date is this format: YYYY-MM-DD
bool MyDataStore::checkdate(string strdate)
{
    
        int month = stoi(strdate.substr(5, 2));
        int date = stoi(strdate.substr(8, 2)); 
        int year = stoi(strdate.substr(0, 4));

        if(strdate.size() != 10 || year > 9999 || year < 1000 || month <1 || month > 12)
        {
            
            return false;
        } 
        else 
        {
            if(month == 2)
            {
                if(date <= 28 || date >=1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {

                if(date <= 31 || date >=1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    
}

void MyDataStore::makeSuggestion(string currentUser) {

    ofstream myfile;
    myfile.open("rec.txt");
    myfile << "No recommendations available" << endl;
    myfile.close();
    
}
