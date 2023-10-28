#pragma once
#include <iostream>
#include <string> // для проверки типа данны

using namespace std;

inline string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	return str;
}