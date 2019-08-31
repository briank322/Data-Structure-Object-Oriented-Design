#include "clothing.h"
#include "review.h"
#include <cmath>
#include <iomanip>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, 
	double price, int qty, std::string size, std::string brand) : 
Product(category, name, price, qty),
brand_(brand),
size_(size)
{

}

Clothing::~Clothing()
{

}

//Returns the appropriate keywords that this product should be associated
set<string> Clothing::keywords() const 
{
	set<string> s_keywords;
	set<string> s_name;
	set<string> s_brand;

	s_name = parseStringToWords(name_);
	
	s_brand = parseStringToWords(brand_);

	//Use setUnion function to add two set into one.
	s_keywords = setUnion(s_name, s_brand);

	return s_keywords;

}

//Returns a string to display the product info for hits of the search
string Clothing::displayString() const
{
	//stringstream for price
	stringstream ss_price;
	stringstream ss_qty;
	stringstream ss_rating;

	//reading in price and quantity.
	ss_price << price_;
	ss_qty << qty_;

	//convert ss to string.
	string price = ss_price.str();
	string qty = ss_qty.str();
	
	double rating = getAverageRating();
	ss_rating << std::fixed << setprecision(2) << rating;

	string rating_str = ss_rating.str();//make to string
	
	//output the information following the given format.
	string result = name_ + "\n" + "Size: " + size_ + " Brand: "
	+ brand_ + "\n" + price + " " + qty + " left.\n"+"Rating: "+
	rating_str +"\n";
	
	return result;
}

//Outputs the product info in the database format
void Clothing::dump(std::ostream& os) const 
{
	os << category_ << endl << name_ << endl
	<< price_ << endl << qty_ << endl;
	os << size_ << endl << brand_ << endl;
}
