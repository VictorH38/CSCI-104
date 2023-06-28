#include <iomanip>
#include <string>
#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty,
		std::string genre, std::string rating) : Product(category, name, price, qty) {
			genre_ = genre;
			rating_ = rating;
}

Movie::~Movie() {

}

std::set<std::string> Movie::keywords() const {
	string rawWords = name_ + " " + genre_ + " ";
	rawWords = convToLower(rawWords);
	return parseStringToWords(rawWords);
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
	return false;
}

std::string Movie::displayString() const {
	stringstream ss;
	ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
	return ss.str();
}

void Movie::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getGenre() const {
	return genre_;
}

std::string Movie::getRating() const {
	return rating_;
}
