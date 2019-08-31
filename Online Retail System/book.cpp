#include "book.h"
#include "review.h"
#include <iomanip>
#include <cmath>


using namespace std;

Book::Book(const std::string category, const std::string name, 
	double price, int qty, string author, string isbn) : 
Product(category, name, price, qty),
author_(author),
isbn_(isbn)
{

}

Book::~Book()
{

}

//Returns the appropriate keywords that this product should be associated
set<std::string> Book::keywords() const 
{
	set<string> s_keywords;
	set<string> title;
	set<string> author;

	title = parseStringToWords(name_);
	author = parseStringToWords(author_);

	//Use setUnion function to add two set into one.
	s_keywords = setUnion(title, author);

	//Add isbn as the keyword
	s_keywords.insert(isbn_);

	return s_keywords;

}

//Returns a string to display the product info for hits of the search
string Book::displayString() const
{
	//string variable for the final output
	string result;

	stringstream ss_price;
	stringstream ss_qty;
	stringstream ss_rating;

	//reading in the price and quantity.
	ss_price << price_;
	ss_qty << qty_;

	//convert ss into the string.
	string price = ss_price.str();
	string qty = ss_qty.str();
	double rating = getAverageRating();
	ss_rating << std::fixed << setprecision(2) << rating;
	string rating_str = ss_rating.str();//make to string

	
	//output the information following the given format.
	result = name_ + "\n" + "Author: " + author_ + " ISBN: "
	+ isbn_ + "\n" + price + " " + qty + " left.\n"+"Rating: "+
	rating_str+"\n";
	return result;
}

//Outputs the product info in the database format
void Book::dump(std::ostream& os) const 
{
	//output the information following the given format.
	os << category_ << endl << name_ << endl
	<< price_ << endl << qty_ << endl;
	os << isbn_ << endl << author_ << endl;
}
