#include <iostream>

#include "KS.h"
#include "utils_and_samples.h"

using namespace std;

int KS::Nextid = 1;

KS::KS()
{
	this->id = Nextid;
	Nextid += 1;
}

void KS::add() {
	cout << "������� �������� �������: ";
	name = get_str();
	cout << "������� ���������� �����: ";
	num_department = get_correct_value<int>(0, INT_MAX);
	cout << "������� ���������� ���������� �����: ";
	work_department = get_correct_value<int>(0, num_department);
	cout << "������� ��� �������������: ";
	efficiency = get_correct_value<double>(0.0, DBL_MAX);
}

void KS::view() {
	if (!name.empty()) {
		cout << "					    �������                                                                 " << '\n';
		cout << getid() << endl;
		cout << "�������� ������� - " << name << '\n';
		cout << "���������� ����� - " << num_department << '\n';
		cout << "���������� ���������� ����� - " << work_department << '\n';
		cout << "������������� ������� - " << efficiency << '\n';
	}
	else {
		cout << "						�� �����������\n";
	}
}

void KS::change() {
	cout << "�������� �� � id " << id << '\n';
	cout << "������� ����� ������������� � ������: ";
	work_department = get_correct_value(0, num_department);
}

void KS::save(ofstream& out) {
	if (out.is_open()) {
		out << "comp"<< '\n';
		out << id << '\n';
		out << name << '\n';
		out << num_department << '\n';
		out << work_department << '\n';
		out << efficiency << '\n';
		cout << "������ �� "<< id << " ��������� � ����." << '\n';
	}
	else {
		cout << "������!";
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
		cout << "������!";
	}
}