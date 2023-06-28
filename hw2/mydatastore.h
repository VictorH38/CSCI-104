#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include "datastore.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "user.h"
#include "util.h"

class MyDataStore : public DataStore {
	public:
		~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

		/**
     * Adds a product to a user's cart
     */
    void addToCart(std::string, Product* p);

		/**
     * Displays a user's cart
     */
    void viewCart(std::string);

		/**
     * Checks out a user's cart
     */
    void buyCart(std::string);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

	private:
		std::set<Product*> products_;
		std::set<User*> users_;
		std::map<std::string, User*> userMap;
		std::map<User*, std::vector<Product*>> cart;
		std::map<std::string, std::set<Product*>> keywordMap;
};
#endif
