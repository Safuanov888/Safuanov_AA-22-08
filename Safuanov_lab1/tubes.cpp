#include <iostream>
#include <fstream>

using namespace std;

struct pipe {
	string name;
	double length;
	double diameter;
	string maintenance;
};

struct comp_station {
	string name;
	int num_department;
	int work_department;
	double efficiency;
};

void add_pipe(pipe& obj_pipe) {
	cout << "������� �������� �����: ";
	cin >> obj_pipe.name;
	cout << "������� ����� �����: ";
	cin >> obj_pipe.length;
	cin.ignore(1000, '\n');
	cout << "������� ������� �����: ";
	cin >> obj_pipe.diameter;
	cin.ignore(1000, '\n');
	cout << "�������� �� ��� �������?: ";
	cin >> obj_pipe.maintenance;
}

void add_comp_station(comp_station& obj_comp_station) {
	cout << "������� �������� �������: ";
	cin >> obj_comp_station.name;
	cout << "������� ���������� �����: ";
	cin >> obj_comp_station.num_department;
	cin.ignore(1000, '\n');
	cout << "������� ���������� ���������� �����: ";
	cin >> obj_comp_station.work_department;
	cin.ignore(1000, '\n');
	cout << "������� ��� �������������: ";
	cin >> obj_comp_station.efficiency;
	cin.ignore(1000, '\n');
}



int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	cout << "                                          � ����� ������������ ���� ����                                           " << '\n';
	pipe obj_pipe;
	comp_station obj_comp_station;
	while (true) {
		int choice;
		cout << "1. �������� �����" << '\n';
		cout << "2. �������� ��" << '\n';
		cout << "3. �������� ���� ��������" << '\n';
		cout << "4. ������������� �����" << '\n';
		cout << "5. ������������� ��" << '\n';
		cout << "6. ���������" << '\n';
		cout << "7. ���������" << '\n';
		cout << "0. �����" << '\n';
		cout << "					   ������� ����������� ��� �����                                               " << '\n';
		cin >> choice;
		switch (choice) {
		case 1:
			add_pipe(obj_pipe);
			break;
		case 2:
			add_comp_station(obj_comp_station);
			break;
		}
		return 0;
	}
}