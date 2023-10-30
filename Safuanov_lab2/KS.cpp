#include "KS.h"
#include "get.h"
#include <fstream>
#include <iostream>

using namespace std;

int KS::Nextid = 2;

KS::KS()
{
	this->id = Nextid;
	Nextid += 2;
}

void KS::add() {
	cout << "Введите название станции: ";
	name = get_str();
	cout << "Введите количество цехов: ";
	cin >> num_department;
	while (cin.fail() || cin.peek() != '\n' || num_department < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> num_department;
	}
	cout << "Введите количество работающих цехов: ";
	cin >> work_department;
	while (cin.fail() || cin.peek() != '\n' ||
		work_department < 0 || work_department > num_department) { // проверка рабочих станций, должно быть меньше
		cin.clear();																								
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> work_department;
	}
	cout << "Введите его эффективность: ";
	cin >> efficiency;
	while (cin.fail() || cin.peek() != '\n' || efficiency < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные введены неверно, попробуйте ещё раз: ";
		cin >> efficiency;
	}
}

void KS::view() {
	if (!name.empty()) {
		cout << "					    Станция                                                                 " << '\n';
		cout << getid() << endl;
		cout << "Название станции - " << name << endl;
		cout << "Количество цехов - " << num_department << endl;
		cout << "Количество работающих цехов - " << work_department << endl;
		cout << "Эффективность станции - " << efficiency << endl;
	}
	else {
		cout << "						КС отсутствует\n";
	}
}

void KS::change() {
	if (name.empty()) {	// проверка на наличие КС
		cout << "Вы не ввели КС\n";
	}
	else {
		cout << "Сколько цехов задействовано в работе: ";
		cin >> efficiency;
		while (cin.fail() || cin.peek() != '\n' || efficiency < 0 || work_department > num_department) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Данные введены неверно, попробуйте ещё раз: ";
			cin >> efficiency;
		}
	}
}

void KS::save() {
	ofstream out;
	if (out.is_open()) {
		out << name << endl;
		out << num_department << endl;
		out << work_department << endl;
		out << efficiency << endl;
		cout << "Данные КС загружены в файл." << endl;
	}
	else {
		cout << "Ошибка!";
	}
}

void KS::download() {
	ifstream read;
	if (read.is_open()) {
		read >> name;
		read >> num_department;
		read >> work_department;
		read >> efficiency;
		cout << "Данные КС выгружены из файла." << endl;
	}
	else {
		cout << "Ошибка!";
	}
}