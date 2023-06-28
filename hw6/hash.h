#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				std::size_t converted[k.length()];
				for (unsigned int i = 0; i < k.length(); i++) {
						converted[i] = letterDigitToNumber(k[i]);
				}

				unsigned long long int sequence[5] = {0, 0, 0, 0, 0};
				int pos = k.length() - 1;
				int index = 4;
				while (pos >= 0) {
						unsigned long long int a6 = 0;
						unsigned long long int a5 = 0;
						unsigned long long int a4 = 0;
						unsigned long long int a3 = 0;
						unsigned long long int a2 = 0;
						unsigned long long int a1 = 0;

						if (pos >= 0) {
								a6 = converted[pos];
						}
						pos -= 1;

						if (pos >= 0) {
								a5 = converted[pos];
						}
						pos -= 1;

						if (pos >= 0) {
								a4 = converted[pos];
						}
						pos -= 1;

						if (pos >= 0) {
								a3 = converted[pos];
						}
						pos -= 1;

						if (pos >= 0) {
								a2 = converted[pos];
						}
						pos -= 1;

						if (pos >= 0) {
								a1 = converted[pos];
						}
						pos -= 1;

						sequence[index] = (pow(36, 5) * a1) + (pow(36, 4) * a2) + (pow(36, 3) * a3) + (pow(36, 2) * a4) + (36 * a5) + a6;
						index -= 1;
				}

				unsigned long long int hash = rValues[0] * sequence[0];
				for (int i = 1; i < 5; i++) {
						hash = hash + (rValues[i] * sequence[i]);
				}

				return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				std::size_t value;

				if (isalpha(letter)) {
						letter = tolower(letter);
						value = (size_t)(letter) - 97;
				}

				if (isdigit(letter)) {
						value = (size_t)(letter) - 22;
				}

				return value;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
