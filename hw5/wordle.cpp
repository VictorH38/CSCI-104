#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string> wordleHelper(std::string in, std::string floating, int pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		set<string> words = wordleHelper(in, floating, 0);
		/*
		cout << "Words:" << endl;
		for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
				cout << *it << endl;
		}
		*/

		set<string> result;
		for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
				if (dict.find(*it) != dict.end()) {
						result.insert(*it);
				}
		}

		return result;
}

// Define any helper functions here
std::set<std::string> wordleHelper(std::string in, std::string floating, int pos) {
		set<string> words = {};

		if (in.length() == 0) {
				return words;
		}

		unsigned int counter = 0;
		for (unsigned int i = 0; i < in.length(); i++) {
				if (in[i] == '-') {
						counter += 1;
				}
		}

		if (counter == 0) {
				words.insert(in);
				return words;
		}
		
		if (in[pos] == '-') {
				for (unsigned int i = 0; i < floating.length(); i++) {
						in[pos] = floating[i];
						string floating2 = floating.substr(0, i) + floating.substr(i + 1);
						set<string> words_temp = wordleHelper(in, floating2, pos + 1);

						/*
						cout << "Words temp 1:" << endl;
						int count = 1;
						for (set<string>::iterator it = words_temp.begin(); it != words_temp.end(); ++it) {
								cout << count << ": " << *it << endl;
								count += 1;
						}
						cout << endl;
						*/

						words.insert(words_temp.begin(), words_temp.end());
						in[pos] = '-';
				}

				if (floating.length() < counter) {
						for (int i = 97; i < 123; i++) {
								in[pos] = (char)(i);
								set<string> words_temp = wordleHelper(in, floating, pos + 1);

								/*
								cout << "Words temp 2:" << endl;
								int count = 1;
								for (set<string>::iterator it = words_temp.begin(); it != words_temp.end(); ++it) {
										cout << count << ": " << *it << endl;
										count += 1;
								}
								cout << endl;
								*/

								words.insert(words_temp.begin(), words_temp.end());
								in[pos] = '-';
						}
				}
		}
		else {
				set<string> words_temp = wordleHelper(in, floating, pos + 1);
				words.insert(words_temp.begin(), words_temp.end());
		}

		return words;
}