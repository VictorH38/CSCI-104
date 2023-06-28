#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "product.h"

class Book : public Product {
	public:
		Book(const std::string category, const std::string name, double price, int qty,
				std::string ISBN, std::string author);
		~Book();

		/**
     * Returns the appropriate keywords that this book should be associated with
     */
		std::set<std::string> keywords() const;

		/**
     * Allows for a more detailed search beyond simple keywords
     */
		bool isMatch(std::vector<std::string>& searchTerms) const;

		/**
     * Returns a string to display the book info for hits of the search
     */
		std::string displayString() const;

		/**
     * Outputs the book info in the database format
     */
		void dump(std::ostream& os) const;

		/**
     * Accessors
     */
		std::string getISBN() const;
    std::string getAuthor() const;

	protected:
		std::string ISBN_;
		std::string author_;
	
	private:

};
#endif
