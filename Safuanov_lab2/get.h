#include <iostream>
#include <string>

#include "logging.h"


inline string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	cerr << str << '\n';
	return str;
}