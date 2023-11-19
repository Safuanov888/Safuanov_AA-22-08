#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "logging.h"
#include "get.h"

using namespace std;

template <typename T>
T get_correct_value(T min, T max) {
	T value;
	cin >> value;
	cerr << value << '\n';
	while (cin.fail() || cin.peek() != '\n' || value < min || value > max) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> value;
		cerr << value << '\n';
	}
	return value;
}

template <typename T>
vector<int> get_ids(const unordered_map<int, T>& dict)
{
	unordered_set<int> ids;
	cout << "Введите id; если закончили, то -1" << '\n';
	while (1) {
		int id = get_correct_value(-1, INT_MAX);
		if (id == -1) {
			break;
		}
		else if (dict.contains(id)) {
			ids.insert(id);
		}
		else {
			cout << "Нет объекта с этим id" << '\n';;
		}
		if (ids.size() == dict.size()) {
			break;
		}
	}
	return vector<int>(ids.begin(), ids.end());
}

template<typename T1, typename T2>
using filter = bool(*)(const T1& dict, T2 param);

template<typename T>
bool filter_by_name(const T& dict, string name) {
	return dict.name.find(name) != string::npos;
}

template <typename T1, typename T2>
unordered_set<int> find_by_filter(const unordered_map<int, T1>& dict, filter<T1, T2> f, T2 par) {
	unordered_set<int> ids;
	for (auto& pair : dict) {
		if (f(pair.second, par)) {
			ids.insert(pair.first);
		}
	}
	return ids;
}

template <typename M>
void view_data(unordered_map<int, M>& dict) {
	for (auto const& pair : dict) {
		M value = pair.second;
		value.view();
	}
}

template <typename F>
void view_id(unordered_map<int, F>& dict, int id) {
	for (auto const& pair : dict) {
		if (id == pair.first) {
			F value = pair.second;
			value.view();
		}
	}
}

template <typename T>
void add_to_dict(unordered_map<int, T>& dict) {
	T obj;
	obj.add();
	dict.insert({ obj.getid(), obj });
}