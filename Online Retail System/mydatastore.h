#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <string>
#include "util.h"
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "review.h"
#include "msort.h"



class MyDataStore : public DataStore {
public:
    MyDataStore();

    ~MyDataStore();

    //Adds a product to the data store
    void addProduct(Product* p);

    //Adds a user to the data store
    void addUser(User* u);

    //Performs a search of products whose keywords match the given "terms"
    //type 0 = AND search (intersection of results for each term) while
    //type 1 = OR search (union of results for each term)
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    //Reproduce the database file from the current Products and User values
    void dump(std::ostream& ofile);

    //Add product to cart
    void addToCart(std::string username,  
        unsigned int hit_index, std::vector<Product*> hits);

    //Print the products in username's cart at the current time.
    void viewCart(std::string username);
    //Buy all the product that are in the cart.
    void buyCart(std::string username);

    //Creates and adds a review with the given information.
    void addReview(const std::string& prodName, int rating,
        const std::string& username, const std::string& date,
        const std::string& review_text);
    bool checkuser(std::string username, std::string password);
    bool checkdate(std::string strdate);
    void makeSuggestion(std::string currentUser);


private:
    std::map<std::string, std::set<Product*> > product_keyword;
    std::map<std::string, std::vector<Product*> > carts;
    std::vector<Product*> products;
    std::vector<User*> users;
    std::string password;

};
#endif
