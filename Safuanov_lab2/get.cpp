#include <iostream>
#include <string>

using namespace std;

inline string get_str() {
	string str;
	cin >> ws;
	getline(std::cin, str);
	return str;
} 

template <typename T> 
T get_correct_value(T min, T max) {
	T value;
	while ((cin >> value).fail() || cin.peek() != '\n' || value < min || value > max) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
	}
	return value;
}