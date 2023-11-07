#include <iostream>
#include <fstream>

#include "KS.h"
#include "get.cpp"

using namespace std;

int KS::Nextid = 1;

KS::KS()
{
	this->id = Nextid;
	Nextid += 1;
}

void KS::add() {
	cout << "Введите название станции: ";
	name = get_str();
	cout << "Введите количество цехов: ";
	num_department = get_correct_value(0, INT_MAX);
	cout << "Введите количество работающих цехов: ";
	work_department = get_correct_value(0, num_department);
	cout << "Введите его эффективность: ";
	efficiency = get_correct_value(0.0, DBL_MAX);
}

void KS::view() {
	if (!name.empty()) {
		cout << "					    Станция                                                                 " << '\n';
		cout << getid() << endl;
		cout << "Название станции - " << name << '\n';
		cout << "Количество цехов - " << num_department << '\n';
		cout << "Количество работающих цехов - " << work_department << '\n';
		cout << "Эффективность станции - " << efficiency << '\n';
	}
	else {
		cout << "						КС отсутствует\n";
	}
}

void KS::change(int id, int num_department) {
	cout << "Меняется КС с id " << id << '\n';
	cout << "Сколько цехов задействовано в работе: ";
	work_department = get_correct_value(0, num_department);
}

void KS::save(ofstream& out, int id) {
	if (out.is_open()) {
		out << "comp"<< '\n';
		out << id << '\n';
		out << name << '\n';
		out << num_department << '\n';
		out << work_department << '\n';
		out << efficiency << '\n';
		cout << "Данные КС "<< id << " загружены в файл." << '\n';
	}
	else {
		cout << "Ошибка!";
	}
}

void KS::download(ifstream& read) {
	if (read.is_open()) {
		read >> id;
		read >> name;
		read >> num_department;
		read >> work_department;
		read >> efficiency;
	}
	else {
		cout << "Ошибка!";
	}
}