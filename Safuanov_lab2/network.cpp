#include <iostream>
#include <unordered_map>
#include "network.h"
#include "utils_and_samples.h"

using namespace std;

bool filter_by_status(const Pipe& dict, bool status) {
	return dict.maintenance == status;
}

bool filter_by_non_working(const KS& dict, int non_working) {
	return dict.num_department - dict.work_department == dict.num_department * non_working / 100;
}

void Network::ConnectionPipes() {
	if (data_P.size() != 0 && data_KS.size() != 0) {
		int entrance_id, exit_id, diameter;
		cout << "������� �������� id ��� �����: ";
		entrance_id = get_correct_value<int>(1, INT_MAX);
		cout << "������� �������� id ��� ������: ";
		exit_id = get_correct_value<int>(1, INT_MAX);
		diameter = get_diameter();

		while (true) {
			if (FindConnection(data_P, diameter)) {
				for (auto& pair : data_P) {
					if (pair.second.diameter == diameter && pair.second.take_id_of_entrance() == 0 && pair.second.take_id_of_exit() == 0) {
						pair.second.connection(entrance_id, exit_id);
						break;
					}
				}
				break;
			}
			cout << "����� � ����� ��������� �� �������, �������� �����" << '\n';
			Pipe p;
			p.add();
			data_P.insert({ p.getid(), p });
		}
		cout << "����� � ��������� " << diameter << " ������� ��������� � ��" << '\n';
	}
	else {
		cout << "���������� ������� ����� � ��" << '\n';
	}
}

void Network::AddPipe(Pipe p) {
	p.add();
	data_P.insert({p.getid(), p});
}

void Network::AddKS(KS ks) {
	ks.add();
	data_KS.insert({ ks.getid(), ks });
}

void Network::ViewData() {
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
}

void Network::change_and_delete_pipe() {
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
						cout << "����� � id " << id << " �������";
					}
				}
				else {
					for (int id : set) {
						data_P.erase(id);
						cout << "����� � id " << id << " �������";
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
						cout << "����� � id " << id << " ����������";
					}
				}
				else {
					cout << "�������� ����� ��� ���(0 - �� ��������, 1 - ��������): ";
					for (int id : set) {
						data_P[id].change();
						cout << "����� � id " << id << " ����������";
					}
				}
			}
		}
	}
	else {
		cout << "��� ���� ��� ���������" << '\n';
	}
}

void Network::change_and_delete_ks() {
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
			for (int id_ks : set) {
				if (choice) {
					data_KS.erase(id_ks);
					cout << "KC � id " << id_ks << " �������";
					for (auto& [id_p, pipe] : data_P) {
						if (pipe.take_id_of_entrance() == id_ks || pipe.take_id_of_exit() == id_ks) {
							pipe.connection(0, 0);
						}
					}
				}
				else {
					data_KS[id_ks].change();
					cout << "����� � id " << id_ks << " ����������";
				}
			}
		}
	}
	else {
		cout << "��� �� ��� ���������" << '\n';
	}
}

void Network::save() {
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
}

void Network::download() {
	cout << "������� �������� ����� ��� ��������: ";
	string read_file = get_str();
	ifstream read(read_file);
	if (read.peek() == std::ifstream::traits_type::eof()) {  // ������� ������� �����
		cout << "����� �� ����������!\n";
	}
	else {
		data_P.clear();
		Pipe::reset_next_id();
		data_KS.clear();
		KS::reset_next_id();
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
}