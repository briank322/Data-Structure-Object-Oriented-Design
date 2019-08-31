#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name,
 double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category)
{

}

Product::~Product()
{
   for(unsigned int i = 0; i<reviews_.size();i++)
   {
     delete reviews_[i];
   }
}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<endl;
}

//return average rating
double Product::getAverageRating() const
{

    std::vector<Review *>::const_iterator it = reviews_.begin();
    double sum = 0.00;
    double counter = 0.00;
    double average = 0.00;
    //if no reviews yet return 0
    if(it == reviews_.end())
    {
        return 0;
    }
    else
    {
        while(it != reviews_.end())
        {
            sum += (*it)->rating;
            counter++;
            ++it;
        }      
        average = sum/counter;
        return average;

    }
    
}

//return reviews 
vector<Review*> Product::getReviews() const 
{
    return reviews_;
}

//pushback review to reviews_ data member.
void Product::reviewadd(Review* review)
{
    reviews_.push_back(review);
}
