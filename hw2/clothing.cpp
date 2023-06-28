#include <iomanip>
#include <string>
#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
		std::string size, std::string brand) : Product(category, name, price, qty) {
			size_ = size;
			brand_ = brand;
}

Clothing::~Clothing() {

}

std::set<std::string> Clothing::keywords() const {
	string rawWords = name_ + " " + brand_ + " ";
	rawWords = convToLower(rawWords);
	return parseStringToWords(rawWords);
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
	return false;
}

std::string Clothing::displayString() const {
	stringstream ss;
	ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
	return ss.str();
}

void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

std::string Clothing::getSize() const {
	return size_;
}

std::string Clothing::getBrand() const {
	return brand_;
}
