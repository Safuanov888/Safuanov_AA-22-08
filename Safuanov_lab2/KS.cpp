#include "KS.h"
#include "get.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

int KS::Nextid = 2;

KS::KS()
{
	this->id = Nextid;
	Nextid += 2;
}

void KS::add() {
	cout << "������� �������� �������: ";
	name = get_str();
	cout << "������� ���������� �����: ";
	num_department = get_int();
	cout << "������� ���������� ���������� �����: ";
	work_department = get_int();
	while (work_department > num_department) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		work_department = get_int();
	}
	cout << "������� ��� �������������: ";
	efficiency = get_double();
}

void KS::view() {
	if (!name.empty()) {
		cout << "					    �������                                                                 " << '\n';
		cout << getid() << endl;
		cout << "�������� ������� - " << name << endl;
		cout << "���������� ����� - " << num_department << endl;
		cout << "���������� ���������� ����� - " << work_department << endl;
		cout << "������������� ������� - " << efficiency << endl;
	}
	else {
		cout << "						�� �����������\n";
	}
}

void KS::change(int id, int num_department) {
	cout << "�������� �� � id " << id << endl;
	cout << "������� ����� ������������� � ������: ";
	work_department = get_int();
	while (work_department > num_department) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ ������� �������, ���������� ��� ���: ";
		work_department = get_int();
	}
}

void KS::save(ofstream& out, int id) {
	if (out.is_open()) {
		out << "comp"<< endl;
		out << id << endl;
		out << name << endl;
		out << num_department << endl;
		out << work_department << endl;
		out << efficiency << endl;
		cout << "������ �� "<< id << " ��������� � ����." << endl;
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