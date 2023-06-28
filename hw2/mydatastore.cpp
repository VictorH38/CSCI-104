#include <sstream>
#include <iomanip>
#include "mydatastore.h"

using namespace std;

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product* p) {
	products_.insert(p);

	set<string> keywordList = p->keywords();
	set<string>::iterator it;
	for (it = keywordList.begin(); it != keywordList.end(); ++it) {
		map<string, set<Product*>>::iterator it2 = keywordMap.find(*it);

		if (it2 != keywordMap.end()) {
			it2->second.insert(p);
		}
		else {
			set<Product*> newSet;
			newSet.insert(p);
			keywordMap.insert(make_pair(*it, newSet));
		}
	}
}

void MyDataStore::addUser(User* u) {
	users_.insert(u);
	userMap.insert(make_pair(convToLower(u->getName()), u));
	vector<Product*> newSet;
	cart.insert(make_pair(u, newSet));
}

void MyDataStore::addToCart(std::string username, Product* p) {
	map<string, User*>::iterator it = userMap.find(convToLower(username));

	if (it != userMap.end()) {
		User* user = it->second;
		map<User*, vector<Product*>>::iterator it2 = cart.find(user);
		it2->second.push_back(p);
	}
	else {
		cout << "Invalid request" << endl;
	}
}

void MyDataStore::viewCart(std::string username) {
	map<string, User*>::iterator it = userMap.find(convToLower(username));

	if (it != userMap.end()) {
		User* user = it->second;
		map<User*, vector<Product*>>::iterator it2 = cart.find(user);

		vector<Product*>::iterator it3;
		int counter = 1;
		for (it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
			cout << "Item" << setw(3) << counter << endl;
        cout << (*it3)->displayString() << endl;
        cout << endl;
        counter += 1;
		}
	}
	else {
		cout << "Invalid username" << endl;
	}
}

void MyDataStore::buyCart(std::string username) {
	map<string, User*>::iterator it = userMap.find(convToLower(username));

	if (it != userMap.end()) {
		User* user = it->second;
		map<User*, vector<Product*>>::iterator it2 = cart.find(user);

		vector<int> erase;
		int counter = 0;
		vector<Product*>::iterator it3;
		for (it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
			Product* prod = *it3;
			if ((prod->getQty() > 0) && (user->getBalance() >= prod->getPrice())) {
				erase.push_back(counter);
				prod->subtractQty(1);
				user->deductAmount(prod->getPrice());
				counter += 1;
			}
		}

		for (int i = erase.size() - 1; i >= 0; --i) {
			it2->second.erase(it2->second.begin() + erase[i]);
		}
	}
	else {
		cout << "Invalid username" << endl;
	}
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	vector<Product*> result;
	map<string, set<Product*>>::iterator it;
	set<Product*> temp;
	int counter = 0;
	bool cont = true;

	while (cont) {
		it = keywordMap.find(terms[counter]);
		if (it != keywordMap.end()) {
			temp = it->second;
			cont = false;
		}
		else {
			counter += 1;
		}
	}

	if (type == 0) {
		for (unsigned int i = counter; i < terms.size(); i++) {
			map<string, set<Product*>>::iterator it2 = keywordMap.find(terms[i]);

			if (it2 != keywordMap.end()) {
				set<Product*> temp2 = it2->second;
				temp = setIntersection(temp, temp2);
			}
		}
	}
	else if (type == 1) {
		for (unsigned int i = counter; i < terms.size(); i++) {
			map<string, set<Product*>>::iterator it2 = keywordMap.find(terms[i]);

			if (it2 != keywordMap.end()) {
				set<Product*> temp2 = it2->second;
				temp = setUnion(temp, temp2);
			}
		}
	}

	set<Product*>::iterator it3;
	for (it3 = temp.begin(); it3 != temp.end(); ++it3) {
		result.push_back(*it3);
	}

	return result;
}

void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << endl;
	set<Product*>::iterator it;
	for (it = products_.begin(); it != products_.end(); ++it) {
		Product* prod = *it;
		prod->dump(ofile);
		delete prod;
	}
	ofile << "</products>" << endl;

	ofile << "<users>" << endl;
	set<User*>::iterator it2;
	for (it2 = users_.begin(); it2 != users_.end(); ++it2) {
		User* user = *it2;
		user->dump(ofile);
		delete user;
	}
	ofile << "</users>" << endl;
}
