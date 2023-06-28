#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "product.h"

class Clothing : public Product {
	public:
		Clothing(const std::string category, const std::string name, double price, int qty,
				std::string size, std::string brand);
		~Clothing();

		/**
     * Returns the appropriate keywords that this clothing should be associated with
     */
		std::set<std::string> keywords() const;

		/**
     * Allows for a more detailed search beyond simple keywords
     */
		bool isMatch(std::vector<std::string>& searchTerms) const;

		/**
     * Returns a string to display the clothing info for hits of the search
     */
		std::string displayString() const;

		/**
     * Outputs the clothing info in the database format
     */
		void dump(std::ostream& os) const;

		/**
     * Accessors
     */
		std::string getSize() const;
    std::string getBrand() const;

	protected:
		std::string size_;
		std::string brand_;
	
	private:

};
#endif
