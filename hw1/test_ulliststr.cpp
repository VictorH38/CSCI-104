#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"
using namespace std;

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
  ULListStr dat;
  for (int i = 0; i < ARRSIZE + 1; i++) {
    dat.push_back(to_string(i));
  }
  dat.pop_back();

  dat.push_front(to_string(-1));
  dat.pop_front();

  dat.clear();
  dat.push_back("World");
  dat.push_front("Hello");
  dat.push_back("!");
  
  //Print "Hello World!"
  cout << dat.get(0) << " " << dat.get(1) << dat.get(2) << endl;
  //Size = 3
  cout << dat.size() << endl;

  dat.pop_back();
  dat.pop_front();

  //Print "World"
  cout << dat.get(0) << endl;
  //Size = 1
  cout << dat.size() << endl;

  //Both print "World"
  cout << dat.back() << endl;
  cout << dat.front() << endl;

  dat.pop_back();
  cout << dat.size() << endl;
}
