#pragma once
#include <iostream>
#include <string>

using namespace std;

inline string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	return str;
}