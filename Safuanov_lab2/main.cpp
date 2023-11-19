#include <iostream>
#include <fstream> // ��� ������ � �������
#include <sstream> // ��� ���������� ������ � ������� 
#include <string> // ��� �������� ���� ������
#include <format> 
#include <chrono> // ��� ������ ������� � ������ � ������ �������

#include <unordered_map>  // ��������� ������
#include <unordered_set>

#include "samples.h"
#include "pipe.h"
#include "KS.h"
#include "logging.h"


using namespace std;
using namespace chrono;

void menu() {
	cout << "					    ������� ����������� ��� �����                                               " << '\n';
	cout << "1. �������� �����" << '\n';
	cout << "2. �������� ��" << '\n';
	cout << "3. �������� ��������" << '\n';
	cout << "4. ������������� �����" << '\n';
	cout << "5. ������������� ��" << '\n';
	cout << "6. ���������" << '\n';
	cout << "7. ���������" << '\n';
	cout << "0. �����" << '\n' << '\n';
}

bool filter_by_status(const Pipe& dict, bool status) {
	return dict.maintenance == status;
}

bool filter_by_non_working(const KS& dict, int non_working) {
	return dict.num_department - dict.work_department == dict.num_department * non_working / 100;
}

int main() {
	setlocale(LC_ALL, "Rus"); // ������� ���� �������� �� ������� ����
	cout << "	����� ���������� � ���������� ����������, ����������� ������� �������� ��������������� ���������� ����!!!" << '\n';
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d-%m-%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log" + time + ".txt");
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	unordered_map<int, Pipe> data_P;
	unordered_map<int, KS> data_KS;
	while (true) {
		menu();  // �������� ����
		cout << "������: ";
		cin.clear();
		int choice = get_correct_value(0, 7);
		switch (choice) {
		case 1:
		{
			add_to_dict(data_P);
			break;
		}
		case 2:
		{
			add_to_dict(data_KS);
			break;
		}
		case 3:
		{
			cout << "1 - ���������� ��� �������, 0 - ������������� ����������: ";
			if (bool choice1 = get_correct_value(0, 1)) {
				view_data(data_P);
				view_data(data_KS);
			}
			else {
				cout << "1 - �����, 0 - ��: ";
				if (bool choice2 = get_correct_value(0, 1)) {
					cout << "1 - �� ��������, 0 - �� �������: ";
					if (bool choice3 = get_correct_value(0, 1)) {
						cout << "������� ��������: ";
						string name = get_str();
						for (int i : find_by_filter(data_P, filter_by_name, name)) {
							view_id(data_P, i);
						}
					}
					else {
						cout << "������� ������: ";
						bool maintenance = get_correct_value(0, 1);
						for (int i : find_by_filter(data_P, filter_by_status, maintenance)) {
							view_id(data_P, i);
						}
					}
				}
				else {
					cout << "1 - �� ��������, 0 - �� �������� ����������������� �����: ";
					if (bool choice4 = get_correct_value(0, 1)) {
						cout << "������� ��������: ";
						string name = get_str();
						for (int i : find_by_filter(data_KS, filter_by_name, name)) {
							view_id(data_KS, i);
						}
					}
					else {
						cout << "������� �������: ";
						int non_working = get_correct_value(0, 100);
						for (int i : find_by_filter(data_KS, filter_by_non_working, non_working)) {
							view_id(data_KS, i);
						}
					}
				}
			}
			break;
		}
		case 4:
		{
			if (!data_P.empty()) {
				cout << "1 - ��������, 0 - ��������� ����: ";
				bool choice1 = get_correct_value(0, 1);
				vector<int> ids;
				cout << "������� �������� �����: ";
				string name = get_str();
				unordered_set<int> set = find_by_filter(data_P, filter_by_name, name);
				if (set.size() == 0) {
					cout << "������ ����� ���";
				}
				else {
					if (choice1) {
						cout << "1 - ������� ��� �����, 0 - �� ��� �����: ";
						bool choice2 = get_correct_value(0, 1);
						if (!choice2) {
							cout << "������ �������� �� ������� ������ id" << '\n';
							for (const auto& id : set) {
								cout << id << '\n';
							}
							ids = get_ids(data_P);
							for (int id : ids) {
								data_P.erase(id);
							}
						}
						else {
							for (int id : set) {
								data_P.erase(id);
							}
						}
					}
					else {
						cout << "1 - �������� ��� �����, 0 - �� ��� �����: ";
						bool choice3 = get_correct_value(0, 1);
						if (!choice3) {
							cout << "������ �������� �� ������� ������ id" << '\n';
							for (const auto& id : set) {
								cout << id << '\n';
							}
							ids = get_ids(data_P);
							for (int id : ids) {
								data_P[id].change();
							}
						}
						else {
							cout << "�������� ����� ��� ���(0 - �� ��������, 1 - ��������): ";
							for (int id : set) {
								data_P[id].change();
							}
						}
					}
				}
			}
			else {
				cout << "��� ���� ��� ���������" << '\n';
			}
			break;
		}
		case 5:
		{
			if (!data_KS.empty()) {
				cout << "1 - ��������, 0 - ��������� ��: ";
				bool choice = get_correct_value(0, 1);
				cout << "������� �������� ��: ";
				string name = get_str();
				unordered_set<int> set = find_by_filter(data_KS, filter_by_name, name);
				if (set.size() == 0) {
					cout << "������ ����� ���";
				}
				else {
					for (int id : set) {
						if (choice) {
							data_KS.erase(id);
						}
						else {
							data_KS[id].change();
						}
					}
				}
			}
			else {
				cout << "��� �� ��� ���������" << '\n';
			}
			break;
		}
		case 6:
		{
			cout << "������� �������� ����� ��� ������: ";
			string in_file = get_str();
			ofstream out(in_file);
			if (data_P.empty()) {
				cout << "��� ����" << '\n';
			}
			if (data_KS.empty()) {
				cout << "��� ��" << '\n';
			}
			for (auto const& p : data_P) {
				if (!p.second.name.empty()) {
					data_P[p.first].save(out);
				}
			}
			for (auto const& k : data_KS) {
				if (!k.second.name.empty()) {
					data_KS[k.first].save(out);
				}
			}
			break;
		}
		case 7:
		{
			cout << "������� �������� ����� ��� ��������: ";
			string read_file = get_str();
			ifstream read(read_file);
			if (read.peek() == std::ifstream::traits_type::eof()) {  // ������� ������� �����
				cout << "����� �� ����������!\n";
			}
			else {
				string Name;
				while (getline(read, Name)) {
					if (Name == "pipe") {
						Pipe read_pipe;
						read_pipe.download(read);
						data_P.insert({ read_pipe.getid(), read_pipe });
						cout << "������ ����� " << read_pipe.getid() << " ��������� �� �����." << '\n';
					}
					if (Name == "comp") {
						KS read_ks;
						read_ks.download(read);
						data_KS.insert({ read_ks.getid(), read_ks });
						cout << "������ �� " << read_ks.getid() << " ��������� �� �����." << '\n';
					}
				}
			}
			break;
		}
		case 0:
		{
			cout << "����� �� ���������";
			exit(0);
		}
		default:
		{
			cout << "������� ����� �� 0 �� 7\n";
			break;
		}
		}
	}
	return 0;
}