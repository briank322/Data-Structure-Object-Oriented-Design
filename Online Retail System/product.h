#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include"review.h"

class Product {
public:
    Product(const std::string category, const std::string name,
     double price, int qty);
    virtual ~Product();

    /**
     * Returns the appropriate keywords that 
     this product should be associated with
     */
    virtual std::set<std::string> keywords() const = 0;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    virtual std::string displayString() const = 0;

    /**
     * Outputs the product info in the database format
     */
    virtual void dump(std::ostream& os) const;

    //read all the ratings and average them out.
    double getAverageRating() const; 

    /*void addReview(const std::string& prodName, int rating,
        const std::string& username, const std::string& date,
        const std::string& review_text);*/
    /**
     * Accessors and mutators
     */
    double getPrice() const;
    std::string getName() const;
    int getQty() const;
    void subtractQty(int num);

    //Simply returns reviews_
    std::vector<Review*> getReviews() const;

    //add reviews
    void reviewadd(Review* review);
    
protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
    std::vector<Review*> reviews_;

};
#endif
