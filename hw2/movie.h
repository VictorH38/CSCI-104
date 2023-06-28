#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "product.h"

class Movie : public Product {
	public:
		Movie(const std::string category, const std::string name, double price, int qty,
				std::string genre, std::string rating);
		~Movie();

		/**
     * Returns the appropriate keywords that this movie should be associated with
     */
		std::set<std::string> keywords() const;

		/**
     * Allows for a more detailed search beyond simple keywords
     */
		bool isMatch(std::vector<std::string>& searchTerms) const;

		/**
     * Returns a string to display the movie info for hits of the search
     */
		std::string displayString() const;

		/**
     * Outputs the movie info in the database format
     */
		void dump(std::ostream& os) const;

		/**
     * Accessors
     */
		std::string getGenre() const;
    std::string getRating() const;

	protected:
		std::string genre_;
		std::string rating_;
	
	private:

};
#endif
