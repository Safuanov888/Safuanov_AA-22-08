#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

inline string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	return str;
} 

inline int get_int() {
	int value;
	cin >> value;
	while (cin.fail() || cin.peek() != '\n' || value < -1) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> value;
	}
	return value;
}

inline bool get_bool() {
	bool value;
	cin >> value;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> value;
	}
	return value;
}

inline double get_double() {
	double value;
	cin >> value;
	while (cin.fail() || cin.peek() != '\n' || value < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> value;
	}
	return value;
}
