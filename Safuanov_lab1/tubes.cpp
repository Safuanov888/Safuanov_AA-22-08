#include <iostream>
#include <fstream>
#include <sstream>

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
	cin.ignore(1000, '\n');
	getline(cin, obj_pipe.name);
	cout << "������� ����� �����: ";
	cin >> obj_pipe.length;
	cout << "������� ������� �����: ";
	cin >> obj_pipe.diameter;
	cout << "�������� �� ��� �������?: ";
	cin >> obj_pipe.maintenance;
}

void add_comp_station(comp_station& obj_comp_station) {
	cout << "������� �������� �������: ";
	cin.ignore(1000, '\n');
	getline(cin, obj_comp_station.name);
	cout << "������� ���������� �����: ";
	cin >> obj_comp_station.num_department;
	cout << "������� ���������� ���������� �����: ";
	cin >> obj_comp_station.work_department;
	cout << "������� ��� �������������: ";
	cin >> obj_comp_station.efficiency;
}

void rewiew(pipe& obj_pipe, comp_station& obj_comp_station) {
	cout << "					    �����                                                                 " << '\n';
	cout << "�������� ����� - " << obj_pipe.name << '\n';
	cout << "����� ����� - " << obj_pipe.length << '\n';
	cout << "������� ����� - " << obj_pipe.diameter << '\n';
	cout << "������ ����� - " << obj_pipe.maintenance << '\n';
	cout << "					    �������                                                                 " << '\n';
	cout << "�������� ������� - " << obj_comp_station.name << '\n';
	cout << "���������� ����� - " << obj_comp_station.num_department << '\n';
	cout << "���������� ���������� ����� - " << obj_comp_station.work_department << '\n';
	cout << "������������� ������� - " << obj_comp_station.efficiency << '\n';
}

void change_pipe(pipe& obj_pipe) {
	cout << "������� �������� �����: ";
	cin.ignore(1000, '\n');
	getline(cin, obj_pipe.name);
	cout << "������� ����� �����: ";
	cin >> obj_pipe.length;
	cout << "������� ������� �����: ";
	cin >> obj_pipe.diameter;
	cout << "�������� �� ��� �������?: ";
	cin >> obj_pipe.maintenance;
}

void change_comp_station(comp_station& obj_comp_station) {
	cout << "������� �������� �������: ";
	cin.ignore(1000, '\n');
	getline(cin, obj_comp_station.name);
	cout << "������� ���������� �����: ";
	cin >> obj_comp_station.num_department;
	cout << "������� ���������� ���������� �����: ";
	cin >> obj_comp_station.work_department;
	cout << "������� ��� �������������: ";
	cin >> obj_comp_station.efficiency;
}

void save_info(pipe& obj_pipe, comp_station& obj_comp_station) {
	ofstream inputFile("file.txt");
	if (inputFile.is_open()) {      // ���� ���� �����������
		inputFile << obj_pipe.name << endl;
		inputFile << obj_pipe.length << endl;
		inputFile << obj_pipe.diameter << endl;
		inputFile << obj_pipe.maintenance << endl;
		inputFile << obj_comp_station.name << endl;
		inputFile << obj_comp_station.num_department << endl;
		inputFile << obj_comp_station.work_department << endl;
		inputFile << obj_comp_station.efficiency << endl;
	}
	else {
		cout << "������!";
	}
	inputFile.close();
	cout << "������ ������� �������� � ����." << endl;
}

void download_info(pipe& obj_pipe, comp_station& obj_comp_station) {
	ifstream outputFile("file.txt");
	if (outputFile.is_open()) {
		outputFile >> obj_pipe.name;
		outputFile >> obj_pipe.length;
		outputFile >> obj_pipe.diameter;
		outputFile >> obj_pipe.maintenance;
		outputFile >> obj_comp_station.num_department;
		outputFile >> obj_comp_station.name;
		outputFile >> obj_comp_station.work_department;
		outputFile >> obj_comp_station.efficiency;
	}
	else {
		cout << "������!";
	}
	outputFile.close();
	cout << "������ ������� ��������� �� �����." << endl;
}

int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	pipe obj_pipe;
	comp_station obj_comp_station;
	while (true) {
		int choice;
		cout << "					    ������� ����������� ��� �����                                               " << '\n';
		cout << "1. �������� �����" << '\n';
		cout << "2. �������� ��" << '\n';
		cout << "3. �������� ���� ��������" << '\n';
		cout << "4. ������������� �����" << '\n';
		cout << "5. ������������� ��" << '\n';
		cout << "6. ���������" << '\n';
		cout << "7. ���������" << '\n';
		cout << "0. �����" << '\n' << '\n';
		cin >> choice;
		switch (choice) {
		case 1:
			add_pipe(obj_pipe);
			break;
		case 2:
			add_comp_station(obj_comp_station);
			break;
		case 3:
			rewiew(obj_pipe, obj_comp_station);
			break;
		case 4:
			change_pipe(obj_pipe);
			break;
		case 5:
			change_comp_station(obj_comp_station);
			break;
		case 6:
			save_info(obj_pipe, obj_comp_station);
			break;
		case 7:
			download_info(obj_pipe, obj_comp_station);
			break;
		case 0:
			cout << "����� �� ���������";
			exit(0);
		}
	}
	return 0;
}