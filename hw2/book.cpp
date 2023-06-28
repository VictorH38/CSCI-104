#include <iomanip>
#include <string>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
		std::string ISBN, std::string author) : Product(category, name, price, qty) {
			ISBN_ = ISBN;
			author_ = author;
}

Book::~Book() {

}

std::set<std::string> Book::keywords() const {
	string rawWords = name_ + " " + author_ + " " + ISBN_ + " ";
	rawWords = convToLower(rawWords);
	return parseStringToWords(rawWords);
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Book::isMatch(std::vector<std::string>& searchTerms) const {
	return false;
}

std::string Book::displayString() const {
	stringstream ss;
	ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << ISBN_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
	return ss.str();
}

void Book::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}

std::string Book::getISBN() const {
	return ISBN_;
}

std::string Book::getAuthor() const {
	return author_;
}
