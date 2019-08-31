#include "movie.h"
#include "review.h"
#include <cmath>
#include <iomanip>
using namespace std;

Movie::Movie(const std::string category, const std::string name, 
	double price, int qty, string genre, string rating): 
Product(category, name, price, qty),
genre_(genre),
rating_(rating)
{

}

Movie::~Movie()
{

}


//Returns the appropriate keywords that this product should be associated
set<string> Movie::keywords() const
{
	set<string> s_keywords;
	set<string> s_name;
	set<string> s_genre;

	s_name = parseStringToWords(name_);
	s_genre = parseStringToWords(genre_);

	//Use setUnion function to add two set into one.
	s_keywords = setUnion(s_name, s_genre);

	return s_keywords;
}

//Returns a string to display the product info for hits of the search
string Movie::displayString() const
{
	//string variable for printing out the result.
	string result;
	//stringstream variable to read price and quantity.
	stringstream ss_price;
	stringstream ss_qty;
	stringstream ss_rating;
	//reading in
	ss_price << price_;
	ss_qty << qty_;

	//Convert ss into the string.
	string price = ss_price.str();
	string qty = ss_qty.str();
	double rating = getAverageRating();
	ss_rating << std::fixed << setprecision(2) << rating;
	//ss_rating << rating;//reading as stream

	string rating_str = ss_rating.str();//make to string

	//output the information following the given format.
	result = name_ + "\n" + "Genre: " + genre_ + " Rating: "
	+ rating_ + "\n" + price + " " + qty + " left.\n"+"Rating: "+
	rating_str+"\n";
	return result;
}

//Outputs the product info in the database format
void Movie::dump(ostream& os) const 
{
	os << category_ << endl << name_ << endl
	<< price_ << endl << qty_ << endl;
	os << genre_ << endl << rating_ << endl;
}
