#include <iostream>
#include <fstream>

using namespace std;

struct pipe {
	string name;
	int length;
	int diameter;
	string maintenance;

};

struct KS {
	string name;
	int num_department;
	int work_department;
	int efficiency;
};

int menu() {
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	cout << "                                          � ����� ������������ ���� ����                                           " << '\n';
	while (true) {
		cout << "1. �������� �����" << '\n';
		cout << "2. �������� ��" << '\n';
		cout << "3. �������� ���� ��������" << '\n';
		cout << "4. ������������� �����" << '\n';
		cout << "5. ������������� ��" << '\n';
		cout << "6. ���������" << '\n';
		cout << "7. ���������" << '\n';
		cout << "0. �����" << '\n';
	}
	return 0;
}



int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����














	return 0;
}